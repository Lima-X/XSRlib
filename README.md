# XSRlib (C/C++)
XSRlib is a small Collection\ of all XoShiRo LFSR-PRNG's.\
This Project aims to bring a small and compact "library", 
that comes with all the functionality and tools you need to use XoShiRo,
without sacrificing speed and efficiency.

Im using the original referencecode taken from [unimi](http://prng.di.unimi.it/),
but heavily modified in order to make it as compact as possible without loosing speed.\
As for the special tools it will come with,
I only planned so far to include tools to initialize the generators and
to generate numbers uniformly in a specified interval.

## Current Progress
XSRlib is now in Beta state.\
Development is moving along nicely and the results seem promising with
about 2.6ns per execution for XSR256 on x64 and half that for XSR128.\
XSR512 obviously takes twice the time as XSR256.

It's also multithreading-safe now ^^, and the Setupfunction is now too in a state where it can be used,
though not finished yet.\
There is also still no documentation yet (, this will come in the future though).