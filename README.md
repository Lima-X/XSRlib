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
XSRlib is still in Beta state.

Development is almost done, everything considering code is Implemented (at least i think so). (edit: nope it wasn't, should be now though.)\
The only things left for me to do are:
- Review the code for any mistakes and last minute optimizations (including syntax)
- Add proper preprocessor statements for configuration of features
- Write the f*cking documentation...

### Guick Update:
Im still trying to optimize stuff and I've found out that for x86...
well let's just say passing a ui32 Functionpointer through a ui64 Functionpointer
and casting it back to ui32 isn't that optimal nor beautiful
and seems to slow down XSRlib wehn compiled for x86.\
There're also some small beauty mistakes which I want to take care of.

## Quick Benchmarknumbers
Xoshiro256 on Intel i5 8600k @ 4,3GHz (x64 MSVC): 1.904ns - 2.082ns per generated number