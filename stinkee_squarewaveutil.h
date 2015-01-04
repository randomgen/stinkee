#ifndef STINKEE_SQUAREWAVEUTIL
#define STINKEE_SQUAREWAVEUTIL

#include <vector>

namespace stinkee {

struct SquareWaveUtil {
    static const float SILENCE_AMPLITUDE;
    static const float LOW_LEVEL_AMPLITUDE;
    static const float HIGH_LEVEL_AMPLITUDE;

    static void encodeByte(const unsigned char  byte,
                           const int            samplingRate,
                           const int            bit0Frequency,
                           const int            bit1Frequency,
                           std::vector<float>  *frames);

    static void encodeBits(const std::vector<bool>&  bits,
                           const int                 samplingRate,
                           const int                 bit0Frequency,
                           const int                 bit1Frequency,
                           std::vector<float>       *frames);
};

}  // library namespace

#endif
