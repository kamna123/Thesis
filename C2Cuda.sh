#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o dependency.lo dependency.cpp
#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c  -o  gcd_banerjee.lo gcd_banerjee.cpp
#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o CodeGen_Cycle_Shrink.lo CodeGen_Cycle_Shrink.cpp
#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o new_loop_normalization.lo new_loop_normalization.cpp
#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o cycle_shrinking.lo cycle_shrinking.cpp
#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o CodeGen_Affinekernal_Interface.lo CodeGen_Affinekernal_Interface.cpp
#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o Dependence_Testing_Interface.lo Dependence_Testing_Interface.cpp
#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o readWrie.lo readWrie.cpp
#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o extShrinking.lo extShrinking.cpp
#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o affinec.lo affinec.cpp

#/usr/bin/libtool --mode=compile g++ -g -Wall -I /home/kamna/rose/rose_build/include -pthread -I /home/kamna/rose/boost_build/include -c -o main_file.lo main_file.cpp
rm main_file
/usr/bin/libtool --mode=link g++ -g -Wall -o main_file dependency.lo gcd_banerjee.lo  new_loop_normalization.lo cycle_shrinking.lo readWrie.lo main_file.lo extShrinking.lo CodeGen_Cycle_Shrink.lo affinec.lo CodeGen_Affinekernal_Interface.lo Dependence_Testing_Interface.lo /home/kamna/rose/rose_build/lib/librose.la
echo first is $1 second is $2 third is $3
echo $2>config.txt
echo $3>>config.txt

./main_file  $1 
