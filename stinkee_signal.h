#ifndef STINKEE_SIGNAL
#define STINKEE_SIGNAL

#include <vector>

namespace stinkee {
namespace signal {

// Audio samples per second (Hz)
static const int SAMPLING_RATE = 44100;

void encode(const bool          red,
            const bool          green,
            const bool          blue,
            std::vector<float> *signal);

}  // module namespace
}  // library namespace

#endif
