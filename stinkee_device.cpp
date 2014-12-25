#include <stinkee_device.h>
#include <stinkee_signal.h>

#include <portaudio.h>

#include <cassert>
#include <cstring>
#include <iostream>

namespace {

static const int            NUM_CHANNELS = 1;
static const PaSampleFormat SAMPLE_TYPE  = paFloat32;

struct CbUserData
{
    std::size_t            processed;
    const stinkee::Signal& signal;
};

int paCallback(const void                     *input,
               void                           *output,
               unsigned long                   frameCount,
               const PaStreamCallbackTimeInfo *timeInfo,
               PaStreamCallbackFlags           statusFlags,
               void                           *userData);

}  // anonymous namespace

namespace stinkee {

Device::~Device()
{
    Pa_Terminate();
}

int Device::init() const
{
    PaError rc = Pa_Initialize();
    if (rc != paNoError) {
        std::cerr << "Failed to initialize portaudio: "
                  << Pa_GetErrorText(rc)
                  << std::endl;
    }

    return rc;
}

int Device::process(const Signal& signal) const
{
    PaError rc;
    CbUserData userData = { 0, signal };

    PaStreamParameters outputParams;
    outputParams.device = Pa_GetDefaultOutputDevice();
    if (outputParams.device == paNoDevice) {
        std::cerr << "No audio output device available" << std::endl;
        return paNoDevice;
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
        return rc;
    }

    rc = Pa_StartStream(audioStream);
    if (rc != paNoError) {
        std::cerr << "Failed to start stream: "
                  << Pa_GetErrorText(rc)
                  << std::endl;
        return rc;
    }

    Pa_Sleep(1000);

    rc = Pa_StopStream(audioStream);
    if (rc != paNoError) {
        std::cerr << "Failed to stop stream: "
                  << Pa_GetErrorText(rc)
                  << std::endl;
        return rc;
    }

    rc = Pa_CloseStream(audioStream);
    if (rc != paNoError) {
        std::cerr << "Failed to close stream: "
                  << Pa_GetErrorText(rc)
                  << std::endl;
        return rc;
    }

    assert(userData.processed == signal.frames().size());

    return 0;
}

}  // library namespace

namespace {

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
    std::size_t framesCopied = std::min(frameCount,
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

}  // anonymous namespace
