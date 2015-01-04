#include <stinkee_signal.h>
#include <stinkee_squarewaveutil.h>

#include <cassert>

namespace {

static const unsigned char HEADER      = 0x05;
static const unsigned char UNDEFINED_1 = 0x00;
static const unsigned char UNDEFINED_2 = 0x01;
static const unsigned char FOOTER      = 0xF4;

static const std::size_t NUM_STARTING_FRAMES        = 220;
static const std::size_t NUM_STARTING_SILENT_FRAMES = 440;
static const std::size_t NUM_TERMINATING_FRAMES     =   5;

static const int BIT_0_FREQUENCY = 2200; // wavelength to encode binary 0 (Hz)
static const int BIT_1_FREQUENCY = 1100; // wavelength to encode binary 1 (Hz)

}  // anonymous namespace

namespace stinkee {

const int Signal::SAMPLING_RATE = 44100; // audio samples per second (Hz)

void Signal::encode(const bool red, const bool green, const bool blue)
{
    m_frames.insert(m_frames.end(),
                    NUM_STARTING_FRAMES,
                    SquareWaveUtil::LOW_LEVEL_AMPLITUDE);
    m_frames.insert(m_frames.end(),
                    NUM_STARTING_SILENT_FRAMES,
                    SquareWaveUtil::SILENCE_AMPLITUDE);

    std::vector<unsigned char> bytes = {
        HEADER,
        (unsigned char)(red   ? 0xFF : 0x00),
        (unsigned char)(green ? 0xFF : 0x00),
        (unsigned char)(blue  ? 0xFF : 0x00),
        UNDEFINED_1,
        UNDEFINED_2,
        FOOTER
    };

    for (std::size_t i = 0; i < bytes.size(); ++i) {
        SquareWaveUtil::encodeByte(bytes[i],
                                   SAMPLING_RATE,
                                   BIT_0_FREQUENCY,
                                   BIT_1_FREQUENCY,
                                   &m_frames);
    }

    SquareWaveUtil::encodeBits({ false },
                               SAMPLING_RATE,
                               BIT_0_FREQUENCY,
                               BIT_1_FREQUENCY,
                               &m_frames);

    m_frames.insert(m_frames.end(),
                    NUM_TERMINATING_FRAMES,
                    SquareWaveUtil::LOW_LEVEL_AMPLITUDE);

    // Gap to separate consecutive signals
    m_frames.insert(m_frames.end(),
                    SAMPLING_RATE,
                    SquareWaveUtil::SILENCE_AMPLITUDE);
}

const std::vector<float>& Signal::frames() const
{
    return m_frames;
}

}  // library namespace
