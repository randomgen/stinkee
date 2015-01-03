#include <stinkee_diffuser.h>
#include <stinkee_signal.h>

#include <cstdlib>

int main(int argc, char* argv[])
{
    stinkee::Signal yellow;
    stinkee::Signal purple;
    yellow.encode(true,  true, false);
    purple.encode(true, false,  true);

    stinkee::Diffuser diffuser;

    if (0 != diffuser.init()) {
        return EXIT_FAILURE;                                          // RETURN
    }

    if (0 != diffuser.process(yellow)) {
        return EXIT_FAILURE;                                          // RETURN
    }

    if (0 != diffuser.process(purple)) {
        return EXIT_FAILURE;                                          // RETURN
    }

    return EXIT_SUCCESS;
}
