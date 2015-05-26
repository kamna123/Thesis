***********************************************************************
************************About files************************************
*********affinec.cpp************
Used to check whether loop is affine or not.
***new_loop_normalization.cpp***
Used to normalize the loop.
*******gcd_banerjee.cpp*********
Used to find whether dependency exists or not.
*******dependency.cpp***********
Used to find RAW WAR WAW.
*******readWrie.cpp*************
used to collect variables involved in dependency.
*******cycle_shrinking.cpp******
used to apply simple cycle shrinking.
*******extShrinking.cpp*********
Used to apply shrinking when variable dependency exists.
***CodeGen_Cycle_Shrinking.cpp***
used for final code generation(in form of cuda file).
***********main_file.cpp*********
finally execute the all files.


*******************************Usage***********************************
***********************************************************************
Firstly install the rose compiler with the help of steps give in rose maunal
Then run the C2Cuda.sh script.

****************how to run the script**************************************
***********************************************************************
./main_file benchmarks/[name of the input file] [gcd/banerjee] [simple/extShrinking1/extShrinking2]

After this cuda file is generated named [name of the input file].cu
