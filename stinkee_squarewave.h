#ifndef STINKEE_SQUAREWAVE
#define STINKEE_SQUAREWAVE

#include <vector>

namespace stinkee {

static const float SILENCE_AMPLITUDE    =  0.0;
static const float LOW_LEVEL_AMPLITUDE  = -1.0;
static const float HIGH_LEVEL_AMPLITUDE = +1.0;

// Convert a 'byte' to a signal formed of eight square waves, one for each bit,
// and append them to the provided 'frames' vector.  The 'samplingRate'
// indicates the number of samples per second in the generated signal, while
// 'bit0Frequency' and 'bit1Frequency' define the two wave lengths used to
// encode each binary value.
void encodeByte(const unsigned char  byte,
                const int            samplingRate,
                const int            bit0Frequency,
                const int            bit1Frequency,
                std::vector<float>  *frames);

// Convert 'bits' to a square wave signal, one wave for each bit, and append
// them to the provided 'frames' vector.
void encodeBits(const std::vector<bool>&  bits,
                const int                 samplingRate,
                const int                 bit0Frequency,
                const int                 bit1Frequency,
                std::vector<float>       *frames);

}  // library namespace

#endif
