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
XSRlib is still in Beta state. ( well maybe Gamma ¯\\\_(ツ)_/¯ )

The Development of the XSRlib is basically done, the code works like it was intended to.\
So it is kinda like ready for release...\
The only things left for me to do are:
- Review the code for any mistakes and last minute optimizations (including syntax and spellchecking)
- Maybe renaming and commenting things (idk tbh)
- ~~Write~~ Fix the f*cking documentation... (adapt it to the new changes)

and well then im done...\
I might also take some proper Benchmarknumbers if i can. 

## Quick Benchmarknumbers
Xoshiro256 on Intel i5 8600k @ 4,3GHz (x64 MSVC): 1.904ns - 2.082ns per generated number