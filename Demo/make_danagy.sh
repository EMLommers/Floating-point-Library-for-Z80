#!/bin/bash 
pasmo -I ../danagy/ -d spectrum.asm 32768.bin > test.asm
cat test.asm | grep "GRL0"
cat test.asm | grep "PRINT_FNUM"