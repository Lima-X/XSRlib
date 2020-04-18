# Documentation
The official Documentation for XSRlib.\
This Document will provide Information about XSRlib's "API",
it's Functions and Macros, as well as how to use them.

## Files:
`xoshiro.c`: XSRlib's Implementation File, contains all Functions.

`xoshiro.h`: XSRlib's Declaration and configuration File.\
Contains all Declarations, Typedefinitions and Structures.\
It also contains the Preprocessor Definitions used to configure XSRlib
and the "Wrapper"-Macros used to make interfacing with XSRlib easier and safer.

## XSR Generator Structure:
```c
typedef struct {               // Contains internal Data for Xoshiro Generators
    struct {
        uint64_t(*fnSS)(pXSR); // FunctionPointer to Xoshiro** Algorithm
        uint64_t(*fnPP)(pXSR); // FunctionPointer to Xoshiro++ Algorithm
        uint64_t(*fnP)(pXSR);  // FunctionPointer to Xoshiro+  Algorithm

        void (*fnLJ)(pXSR);    // FunctionPointer to LongJump  Function
        void (*fnSJ)(pXSR);    // FunctionPointer to ShortJump Function
    };
    pXSR pS;                   // Pointer to State Memory
} sXSRT, * pXSRT;
```

## Functions:

###### Allocate- / Reallocate- XoShiRo:
```c
pXSRT fnAllocXSR(      // Allocates and configures a XSR Data Structure
    uint64_t ui64Seed, // Seed for SplitMix64 used to seed Xoshiro
    uint32_t ui32XSR,  // Parameters for Xoshiro State initialization (compressed)
    uint8_t  ui8SM     // Parameters for SplitMix64 initialization (compressed)
)
void fnRelocXSR(       // Reallocates/Reseeds an already existing XSR Data Structure
    pXSRT xsr,         // Pointer to XSR Data Structure to be reallocated/reseeded
    uint64_t ui64Seed,
    uint32_t ui32XSR,
    uint8_t ui8SM
)
```
`ui32XSR`: use the `XSRParamA()` Macro to convert your parameters for the Xoshiro Generator into this single value.\
`ui32XSR`: use the `XSRParamB()` Macro to convert your parameters for the SplitMix64 Seeder into this single value.
Note: `fnRelocXSR()` is not yet able to reallocate the basic size of the State,
this is a feature to be implemented in a future release.

###### Copy-XoShiRo:
```c
pXSRT fnCopyXSR( // Creates a copy of an already existing XSR Data Structure
    pXSRT xsr    // Pointer to XSR Data Structure to be copied
)
```
The Copied Structure can be used in parallel with the original Structure,
from which it was copied from, as a separate Generator.

###### Deallocate-XoShiRo:
```c
void fnDelocXSR( // Deallocates an existing XSR Data Structure
    pXSRT xsr    // Existing XSR Data Structure to be deallocated
)
```

## Macros
