# Stinkee

**libstinkee** is a reverse-engineered C++ library to control
[Scentee](http://scentee.com) diffusers plugged into laptops or other non-iOS
devices.  I started working on it during a hackathon in May 2014 (Skills Matter
iOScon Hackathon, London) because the official Scentee SDK targeted iOS
platforms only and therefore an Apple developer license was required to play
with the diffuser.  This proof-of-concept doesn't offer all the functionalities
of the offical implementation: it only provides a unique call that releases a
scent and emits a colour.

![Scentee diffuser activated from a laptop](photo.jpg)

## Build instructions

Stinkee depends on the cross-platform [PortAudio](http://www.portaudio.com)
library (version 20140130) to transmit the encoded sound signal, which
activates the Scentee diffuser, to the audio output device.  It is
straightforward to install with a package manager, such as Homebrew on OS X
(`brew install portaudio`) or APT on Ubuntu (`apt-get install
portaudio19-dev`).  Otherwise, consult the instructions on the PortAudio
website to build the library from the source code.

Once PortAudio is correctly installed, just run

    make

from the root of your cloned `stinkee` git repository to build the
`libstinkee.a` static library and the `stinkeedemo` example program.

The build passed on the following platforms:

- Mac OS X Yosemite (clang++ 6.0)
- Linux Ubuntu 14.04 LTS (g++ 4.8.2)

**Note, however, that on Linux with ALSA the audio signal drops due to
unresolved latency issues.**

## Run the demo

1. Charge the diffuser with the USB cable.
2. Plug the diffuser firmly into the audio port of your computer.
3. Set the volume to the maximum.
4. Execute `stinkeedemo` to produce a puff, a yellow and a purple light!
