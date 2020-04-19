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

### Allocate- / Reallocate- XoShiRo:
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
It has the following Structure:
```
ui32XSR: 00-000-00000000-00000000-00000000000
Bit: 31-30 ( 2Bit): Binary  - GeneratorStateSize:  11 = 512b; 10 = 256b; 01 = 128b;
     29-27 ( 3Bit): Bitwise - Random Initializers: 1XX = LJ; X1X = SJ; XX1 = NS;
     26-19 ( 8Bit): Binary  - Count of LongJumps:  0-255;
     18-11 ( 8Bit): Binary  - Count of ShortJumps: 0-255;
     10-0  (11Bit): Binary  - Count of NextState:  0-2047;
```
`ui8SM`: use the `XSRParamB()` Macro to convert your parameters for the SplitMix64 Seeder into this single value.\
It has the following Structure:
```
ui8SM: 0-0000000
Bit:   7 (1Bit): Bitwise - Random Initializers: 1 = NS;
     6-0 (7Bit): Binary  - Count of NextState:  0-127;
```
### Copy-XoShiRo:
```c
pXSRT fnCopyXSR( // Creates a copy of an already existing XSR Data Structure
    pXSRT xsr    // Pointer to XSR Data Structure to be copied
)
```
The Copied Structure can be used in parallel with the original Structure,
from which it was copied from, as a separate Generator.

### Deallocate-XoShiRo:
```c
void fnDelocXSR( // Deallocates an existing XSR Data Structure
    pXSRT xsr    // Existing XSR Data Structure to be deallocated
)
```

## Macros

### XSR Parameter -A / -B:
```c
XSRParamA( // Converts Parameters into 
    mod,   // XSR StateSize: XSR_512, -256, -128
    ran,   // RandomInitialization: XSR_RANDOM_LJUMP, -SJUMP, -NEXTS, -ALL
    lj,    // Count of LongJumps:            0-255
    sj,    // Count of ShortJumps:           0-255
    ns     // Count of NextState executions: 0-2047
)
XSRParamB( // Converts Parameters into 
    ran,   // RandomInitialization: XSR_RANDOM_SM
    ns     // Count of NextState executions: 0-127
)
```
For more information see the Datalayout of the Value above