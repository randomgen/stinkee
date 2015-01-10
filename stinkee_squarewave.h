#ifndef STINKEE_SQUAREWAVE
#define STINKEE_SQUAREWAVE

#include <vector>

namespace stinkee {
namespace squarewave {

static const float SILENCE_AMPLITUDE    =  0.0;
static const float LOW_LEVEL_AMPLITUDE  = -1.0;
static const float HIGH_LEVEL_AMPLITUDE = +1.0;

void encodeByte(const unsigned char  byte,
                const int            samplingRate,
                const int            bit0Frequency,
                const int            bit1Frequency,
                std::vector<float>  *frames);

void encodeBits(const std::vector<bool>&  bits,
                const int                 samplingRate,
                const int                 bit0Frequency,
                const int                 bit1Frequency,
                std::vector<float>       *frames);

}  // module namespace
}  // library namespace

#endif
