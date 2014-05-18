#ifndef STINKEE_SIGNAL
#define STINKEE_SIGNAL

#include <vector>

namespace stinkee {

class Signal {
  private:
    std::vector<float> m_frames;   // audio signal in the range [-1,1]

  public:
    static const int SAMPLING_RATE;

    void encode(const bool red, const bool green, const bool blue);
    const std::vector<float>& frames() const;
};

}  // library namespace

#endif
