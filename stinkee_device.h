#ifndef STINKEE_DEVICE
#define STINKEE_DEVICE

namespace stinkee { class Signal; }
namespace stinkee {

class Device {
  public:
    ~Device();
    int init() const;
    int process(const Signal& signal) const;
};

}  // library namespace

#endif
