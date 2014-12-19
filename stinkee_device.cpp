#include <stinkee_device.h>
#include <stinkee_signal.h>

#include <portaudio.h>

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

    void *audioStream;
    rc = Pa_OpenDefaultStream(
            &audioStream,
            0,
            NUM_CHANNELS,
            SAMPLE_TYPE,
            Signal::SAMPLING_RATE,
            paFramesPerBufferUnspecified,
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
    }

    return rc;
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
    CbUserData& data = *((CbUserData *)userData);
    const std::vector<float> frames = data.signal.frames();
    float *out = (float *)output;

    for (std::size_t i = 0; i < frameCount; ++i) {
        if (data.processed < frames.size()) {
            *out = frames[data.processed];
        }
        else {
            *out = 0.0;
        }
        ++out;
        ++data.processed;
    }

    return data.processed < frames.size() ? paContinue : paComplete;
}

}  // anonymous namespace
