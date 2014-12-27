#ifndef STINKEE_DEVICE
#define STINKEE_DEVICE

namespace stinkee { class Signal; }
namespace stinkee {

class Device {
  private:
    bool m_initialized;

  public:
    Device();
    ~Device();
    int init();
    int process(const Signal& signal) const;
};

}  // library namespace

#endif
