#include <stinkee_diffuser.h>
#include <stinkee_signal.h>

#include <portaudio.h>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <future>
#include <iostream>

namespace {

static const int            NUM_CHANNELS = 1;
static const PaSampleFormat SAMPLE_TYPE  = paFloat32;

struct CbUserData
{
    std::promise<bool>     done;
    std::size_t            processed;
    const stinkee::Signal& signal;
};

class AutoClose
{
  private:
    PaStream *m_audioStream;

  public:
    AutoClose(PaStream *audioStream);
    AutoClose(const AutoClose&) = delete;
    AutoClose& operator=(const AutoClose&) = delete;
    ~AutoClose();
};

int paCallback(const void                     *input,
               void                           *output,
               unsigned long                   frameCount,
               const PaStreamCallbackTimeInfo *timeInfo,
               PaStreamCallbackFlags           statusFlags,
               void                           *userData);

void paFinishedCallback(void *userData);

}  // anonymous namespace

namespace stinkee {

Diffuser::Diffuser()
: m_initialized(false)
{
}

Diffuser::~Diffuser()
{
    if (m_initialized) {
        Pa_Terminate();
    }
}

int Diffuser::init()
{
    PaError rc = Pa_Initialize();
    if (rc != paNoError) {
        std::cerr << "Failed to initialize portaudio: "
                  << Pa_GetErrorText(rc)
                  << std::endl;
    } else {
        m_initialized = true;
    }

    return rc;
}

int Diffuser::process(const Signal& signal) const
{
    assert(m_initialized);

    PaError rc;
    CbUserData userData = { std::promise<bool>(), 0, signal };

    PaStreamParameters outputParams;
    outputParams.device = Pa_GetDefaultOutputDevice();
    if (outputParams.device == paNoDevice) {
        std::cerr << "No audio output device available" << std::endl;
        return paNoDevice;                                            // RETURN
    }

    const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(outputParams.device);
    outputParams.channelCount = NUM_CHANNELS;
    outputParams.sampleFormat = SAMPLE_TYPE;
    outputParams.suggestedLatency = deviceInfo->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = NULL;

    PaStream *audioStream;
    rc = Pa_OpenStream(
            &audioStream,
            NULL,
            &outputParams,
            Signal::SAMPLING_RATE,
            paFramesPerBufferUnspecified,
            paClipOff | paDitherOff,
            paCallback,
            &userData);

    if (rc != paNoError) {
        std::cerr << "Failed to open output stream: "
                  << Pa_GetErrorText(rc)
                  << std::endl;
        return rc;                                                    // RETURN
    }

    // Will close the stream no matter what happens next...
    AutoClose scopeGuard(audioStream);

    rc = Pa_SetStreamFinishedCallback(audioStream, paFinishedCallback);
    if (rc != paNoError) {
        std::cerr << "Failed to set finished callback: "
                  << Pa_GetErrorText(rc)
                  << std::endl;
        return rc;                                                    // RETURN
    }

    rc = Pa_StartStream(audioStream);
    if (rc != paNoError) {
        std::cerr << "Failed to start stream: "
                  << Pa_GetErrorText(rc)
                  << std::endl;
        return rc;                                                    // RETURN
    }

    // Wait for the signal to be completely played
    bool finished = userData.done.get_future().get();
    assert(finished);

    return userData.processed == signal.frames().size() ? 0 : 1;
}

}  // library namespace

namespace {

AutoClose::AutoClose(PaStream *audioStream)
: m_audioStream(audioStream)
{
}

AutoClose::~AutoClose()
{
    PaError rc = Pa_CloseStream(m_audioStream);
    if (rc != paNoError) {
        std::cerr << "Failed to close stream: "
                  << Pa_GetErrorText(rc)
                  << std::endl;
    }
}

int paCallback(const void                     *input,
               void                           *output,
               unsigned long                   frameCount,
               const PaStreamCallbackTimeInfo *timeInfo,
               PaStreamCallbackFlags           statusFlags,
               void                           *userData)
{
    CbUserData *data = (CbUserData *)userData;
    const std::vector<float>& frames = data->signal.frames();
    float *out = (float *)output;

    // Caller may request more frames than there is left in the signal buffer
    // once the end is reached
    std::size_t framesCopied = std::min((std::size_t)frameCount,
                                        frames.size() - data->processed);

    std::memcpy(out,
                &frames[data->processed],
                framesCopied * sizeof (float));

    // At the end of the signal, fill the rest of the buffer with silence
    std::memset(out + framesCopied,
                0,
                (frameCount - framesCopied) * sizeof (float));

    data->processed += framesCopied;
    return data->processed < frames.size() ? paContinue : paComplete;
}

void paFinishedCallback(void *userData)
{
    ((CbUserData *)userData)->done.set_value(true);
}

}  // anonymous namespace
