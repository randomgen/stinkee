#include <stinkee_diffuser.h>
#include <stinkee_signal.h>

#include <cstdlib>
#include <vector>

int main()
{
    stinkee::Diffuser diffuser;

    if (0 != diffuser.init()) {
        return EXIT_FAILURE;                                          // RETURN
    }

    std::vector<float> signal;
    stinkee::signal::encode(true,  true, false, &signal);  // Yellow
    stinkee::signal::encode(true, false,  true, &signal);  // Purple
    int rc = diffuser.process(signal);

    return 0 == rc ? EXIT_SUCCESS : EXIT_FAILURE;
}
