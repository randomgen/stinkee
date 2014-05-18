#include <stinkee_device.h>
#include <stinkee_signal.h>

#include <cstdlib>

int main(int argc, char* argv[])
{
    stinkee::Signal yellow;
    stinkee::Signal purple;
    yellow.encode(true,  true, false);
    purple.encode(true, false,  true);

    stinkee::Device device;

    if (0 != device.init()) {
        return EXIT_FAILURE;                                          // RETURN
    }

    if (0 != device.process(yellow)) {
        return EXIT_FAILURE;                                          // RETURN
    }

    if (0 != device.process(purple)) {
        return EXIT_FAILURE;                                          // RETURN
    }

    return EXIT_SUCCESS;
}
