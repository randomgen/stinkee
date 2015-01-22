#ifndef STINKEE_DIFFUSER
#define STINKEE_DIFFUSER

#include <vector>

namespace stinkee {

// This class implements a mechanism to activate Scentee diffusers.
class Diffuser {
  private:
    bool m_initialized;  // 'true' if 'init()' has been executed

    // Not copyable
    Diffuser(const Diffuser&) = delete;
    Diffuser& operator=(const Diffuser&) = delete;

    // Not movable
    Diffuser(Diffuser&&) = delete;
    Diffuser& operator=(Diffuser&&) = delete;

  public:
    // Create an uninitialized 'Diffuser'.  Although multiple objects may be
    // instantiated, an application should just need one as there cannot be
    // more than one diffuser plugged to the *default* audio device at a given
    // time.
    Diffuser();

    // Destroy this object and, if it had been initialized, release audio
    // resources.
    ~Diffuser();

    // Prepare audio resources.  Return 0 on success, and a non-zero value
    // otherwise.  The behaviour is undefined if this method is called more
    // than once per object.
    int init();

    // Play the provided 'signal' to the default audio device, which should
    // activate the diffuser if it is plugged correctly and if the signal is
    // valid.  Return 0 on success, and a non-zero value otherwise.  The
    // behaviour is undefined if the diffuser has not been initialized.
    int process(const std::vector<float>& signal) const;
};

}  // library namespace

#endif
