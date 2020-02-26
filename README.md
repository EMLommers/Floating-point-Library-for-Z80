# Floating-point library for Z80
Floating-Point Arithmetic Library for Z80


## bfloat

https://en.wikipedia.org/wiki/Bfloat16_floating-point_format

![Ray tracing using bfloat](https://github.com/DW0RKiN/Floating-point-Library-for-Z80/blob/master/bfloat.png)

    FEDC BA98 7654 3210                  
    eeee eeee Smmm mmmm

    S (bit[7]):     Sign bit
    e (bits[F:8]):  Biased exponent
    m (bits[6:0]):  Fraction

    BIAS = $7F = 127
    MIN = 2^-127 * 1 = 5.8774717541114375×10⁻³⁹
    MAX = 2^+128 * 1.9921875 = 6.779062778503071×10³⁸

floating-point number = (-1)^S * 2^(eeee eeee - BIAS) * ( 128 + mmm mmmm) / 128

Sign position is moved from the original.

## danagy 

https://github.com/nagydani/lpfp

![Ray tracing using danagy](https://github.com/DW0RKiN/Floating-point-Library-for-Z80/blob/master/danagy.png)

    FEDC BA98 7654 3210                  
    Seee eeee mmmm mmmm

    S (bit[F]):     Sign bit
    e (bits[E:8]):  Biased exponent
    m (bits[7:0]):  Fraction

    BIAS = $40 = 64
    MIN = 2^-64 * 1 = 5.421010862427522170037264×10⁻²⁰
    MAX = 2^+63 * 1.99609375 = 1.8410715276690587648×10¹⁹

floating-point number = (-1)^S * 2^(eee eeee - BIAS) * ( 256 + mmmm mmmm) / 256


## binary16 (half)

https://en.wikipedia.org/wiki/Half-precision_floating-point_format

![Ray tracing using binary16](https://github.com/DW0RKiN/Floating-point-Library-for-Z80/blob/master/binary16.png)

    FEDC BA98 7654 3210                  
    Seee eemm mmmm mmmm

    S (bit[F]):     Sign bit
    e (bits[E:A]):  Biased exponent
    m (bits[9:0]):  Fraction

    BIAS = $F = 15
    MIN = 2^-15 * 1 = 0.000030517578125
    MAX = 2^+16 * 1.9990234375 = 131008

floating-point number = (-1)^S * 2^(ee eee - BIAS) * ( 1024 + mm mmmm mmmm) / 1024 

## applies to everything

Without support for infinity, zero, and NaN.

    if ( a + b > MAX ) { res = MAX; set carry }
    if ( a - b < MIN ) { res = MIN; set carry }

Rounding of lost bits is (no matter what the sign):

    mmmm 0000 .. mmmm 1000 => mmmm + 0
    mmmm 1001 .. mmmm 1111 => mmmm + 1
    
finit.asm should be included as the first file.

If a math operation needs to include another operation, it will do it itself.
But data files ( *.tab ) must be included manually! 
They must be aligned to the address divisible by 256.

The natural logarithmic auxiliary tables (`fln.tab`) do not have a size divisible by 256. It is best to include them last.
The natural exponential function auxiliary tables (`fexp.tab`) do not have a size divisible by 256. It is best to include them last.


Inaccuracy of least significant bit in floating point operations. More information in *.dat files.

|        `FDIV`        | binary16 |  danagy  |  bfloat  |  comment                               |
| :------------------: | :------: | :------: | :------: | :---                                   |
|         ± 1          |          |          |          |  BC / HL counted as BC * (1 / HL)      | 
|         ± 2          | accurate | accurate | accurate |                                        |


| `FLN` `fix_ln EQU 0` | binary16 |  danagy  |  bfloat  |  comment                               |
| :------------------: | :------: | :------: | :------: | :---                                   |
|         ± 1          |  29.93%  |  24.07%  |  24.09%  |                                        |
|         ± 2          |   0.30%  |   0.05%  |   0.05%  |  When input exponent = -1              |
|         ± 3          |   0.19%  |   0.03%  |   0.03%  |  When input exponent = -1              |
|         ± more       |   0.48%  |   0.07%  |   0.05%  |  When input exponent = -1              |
|       min, max       | -59, 6   | -10, 7   |   4, 7   |  Correctly - Result                    |


| `FLN` `fix_ln EQU 1` | binary16 |  danagy  |  bfloat  |  comment                               |
| :------------------: | :------: | :------: | :------: | :---                                   |
|         ± 1          |  28.53%  |  23.90%  |  24.60%  |  Input with exponent -1, is corrected. |
|         ± 2          | accurate | accurate | accurate |                                        |


|        `FEXP`        | binary16 |  danagy  |  bfloat  |  comment                               |
| :------------------: | :------: | :------: | :------: | :---                                   |
|         ± 1          |  16.73%  |   4.52%  |   2.40%  |                                        |
|         ± 2          |   0.91%  |   0.56%  |   0.34%  |                                        |
|         ± 3          |   0.05%  |   0.05%  |   0.02%  |                                        |

    e^(ln(2)) = e^0.6931471805599453094172321 = 2
    2^(log₂(e)) = 2^1.4426950408889634073599247 = e
    e^x = 2^(x*1.4426950408889634073599247)
    Learn more about algorithms (natural) exponential function http://guihaire.com/code/?p=1107

|         Other        | binary16 |  danagy  |  bfloat  |  comment                               |
| :------------------: | :------: | :------: | :------: | :---                                   |
|                      | accurate | accurate | accurate |                                        |


    call  fadd          ; HL = HL + DE
    call  faddp         ; HL = HL + DE, HL and DE have the same signs
    call  fsub          ; HL = HL - DE
    call  fsubp         ; HL = HL - DE, HL and DE have the same signs

    call  fmul          ; HL = BC * DE
    call  fdiv          ; HL = BC / HL
    call  fmod          ; HL = BC % HL

    call  fln           ; HL = ln(abs(HL))
    call  fexp          ; HL = e^HL
    call  fpow2         ; HL = HL * HL
    call  fsqrt         ; HL = abs(HL) ^ 0.5

    call  frac          ; HL = HL % 1
    call  fint          ; HL = truncate(HL) * 1.0 = HL - ( HL % 1 )

    call  fwld          ; HL = unsigned word HL * 1.0
    call  fwst          ; HL = (unsigned word) abs(HL)
    call  fbld          ; DE = unsigned char A * 1.0
    
    call  fcmp          ; set flag for HL - DE
    call  fcmpa         ; set flag for abs(HL) - abs(DE)
    call  fcmps         ; set flag for HL - DE, HL and DE have the same signs

    Macros (must be included before first use):

    mtst  H, L          ; set flag for (HL - 0), +-MIN => set zero flag, (HL <= -MIN) => set carry flag   
    mcmpa H, L, D, E    ; set flag for abs(HL) - abs(DE)
    mcmps H, L, D, E    ; set flag for HL - DE, HL and DE have the same signs
    mneg  H, L          ; HL = -HL
    mabs  H, L          ; HL = abs(HL)
    mge0  H, L          ; if (HL >= 0) set zero;
    msor  H, L, D, E    ; (BIT 7, A) = HL_sign or DE_sign
    mmul2 H, L          ; HL = HL * 2
    mdiv2 H, L          ; HL = HL / 2


Size in bytes

     color_flow_warning  EQU     0
     carry_flow_warning  EQU     1

                          binary16  danagy    bfloat    use
                          --------  --------  --------  --------
     fadd+fsub:           369       177       188       
     fadd:                365       173       184       
     fsub:                369       177       188       

     fmul+fdiv:           10453     1931      1422      fmul.tab + fdiv.tab
     fmul:                8322      1629      1108      fmul.tab
     fdiv:                10453     1931      1422      fdiv.tab (include itself fmul.tab)

     fln (fix_ln EQU 0):  2511      966       976       fln.tab
     fln (fix_ln EQU 1):  3551      1489      1504      fln.tab
     fexp:                8525      2201      1683      fexp.tab (include itself fmul.tab)

     fmod:                118       69        77        

     fpow2:               8333      279       158       fpow2.tab
     fsqrt:               4120      527       269       fsqrt.tab

     frac:                55        31        33        
     fint:                38        23        23        

     fwld:                57        32        37        
     fwst:                53        49        46        
     fbld:                18        16        17        

     all:                 18873     5029      4300 
