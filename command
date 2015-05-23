/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o Cuda.lo Cuda.c



 /usr/bin/libtool --mode=link g++ -g -Wall -o Cuda Cuda.lo /home/kamna/rose/rose_build/lib/librose.la 


 ./Cuda -c rose_inputFile.C



changed in GCD_Banerjee.cpp  
 /* if(b.compare("*") || stmt_string[j]=='\0')
                             {
                                constt=constt+(var*sign);
                             }*/


fill coefficient array
