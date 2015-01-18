#ifndef STINKEE_SIGNAL
#define STINKEE_SIGNAL

#include <vector>

namespace stinkee {

// Audio samples per second (Hz)
static const int SAMPLING_RATE = 44100;

// Generate a signal that emits a scent and produces a colour when played to a
// diffuser, and append it to the provided 'frames' vector.  Then one second of
// silence is included, so that another signal may be encoded right after it.
// Combine the primary colours 'red, 'green' and 'blue' to compose other
// colours.
void encode(const bool          red,
            const bool          green,
            const bool          blue,
            std::vector<float> *frames);

}  // library namespace

#endif
