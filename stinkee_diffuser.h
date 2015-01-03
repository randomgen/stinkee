#ifndef STINKEE_DIFFUSER
#define STINKEE_DIFFUSER

namespace stinkee { class Signal; }
namespace stinkee {

class Diffuser {
  private:
    bool m_initialized;

  public:
    Diffuser();
    ~Diffuser();
    int init();
    int process(const Signal& signal) const;
};

}  // library namespace

#endif
