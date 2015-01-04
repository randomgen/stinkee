#include <stinkee_diffuser.h>
#include <stinkee_signal.h>

#include <cstdlib>

int main()
{
    stinkee::Diffuser diffuser;

    if (0 != diffuser.init()) {
        return EXIT_FAILURE;                                          // RETURN
    }

    stinkee::Signal signal;
    signal.encode(true,  true, false);  // Yellow
    signal.encode(true, false,  true);  // Purple

    if (0 != diffuser.process(signal)) {
        return EXIT_FAILURE;                                          // RETURN
    }

    return EXIT_SUCCESS;
}
