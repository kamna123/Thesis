#!/bin/bash
rm y.tab.c
lex src/ansiC.l
yacc -d -y src/cuda.y
rm bin/text
gcc -o bin/text src/dependency_abstraction_2.c src/Loop_Normalization.c src/AffineTest.c src/fdisplay_2.c src/CodeGen_1_only_WAW.c src/GCD_Banerjee_Test.c src/Omega_Test.c src/Dependence_Testing_Interface.c src/ExtendedCS.c src/Cycle_Shrinking.c src/CodeGen_ExtendedCycleShrinking.c src/CodeGen_CycleShrinking.c src/CodeGen_AffineKernel_Interface.c y.tab.c
./bin/text $1 $2 $3 $4
