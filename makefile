# Example Makefile for ROSE users
# This makefile is provided as an example of how to use ROSE when ROSE is
# installed (using "make install").  This makefile is tested as part of the
# "make distcheck" rule (run as part of tests before any CVS checkin).
# The test of this makefile can also be run by using the "make installcheck"
# rule (run as part of "make distcheck").


# Location of include directory after "make install"
ROSE_INCLUDE_DIR = /home/kamna/rose/rose_build/include
BOOST_INCLUDE_DIR=/home/kamna/rose/boost_build/include
BOOST_CPPFLAGS = -pthread -I /home/kamna/rose/boost_build/include
CC                    = gcc
CXX                   = g++
CPPFLAGS              = 
#CXXCPPFLAGS           = @CXXCPPFLAGS@
CXXFLAGS              =  -g -Wall
LDFLAGS               = 

ROSE_SOURCE_DIR = /home/kamna/rose/own/original_code/benchmarks


main_file: dependency.lo gcd_banerjee.lo  new_loop_normalization.lo cycle_shrinking.lo readWrie.lo main_file.lo extShrinking.lo CodeGen_Cycle_Shrink.lo affinec.lo CodeGen_Affinekernal_Interface.lo Dependence_Testing_Interface.lo
	/usr/bin/libtool --mode=link $(CXX) $(CXXFLAGS) -o main_file dependency.lo gcd_banerjee.lo  new_loop_normalization.lo cycle_shrinking.lo readWrie.lo main_file.lo extShrinking.lo CodeGen_Cycle_Shrink.lo affinec.lo CodeGen_Affinekernal_Interface.lo Dependence_Testing_Interface.lo /home/kamna/rose/rose_build/lib/librose.la
dependency.lo: dependency.cpp ds.hpp  dependency.h
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o  dependency.lo dependency.cpp

gcd_banerjee.lo: gcd_banerjee.cpp  gcd_banerjee.hpp ds.hpp
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o gcd_banerjee.lo gcd_banerjee.cpp 
              
new_loop_normalization.lo:new_loop_normalization.cpp new_loop_normalization.hpp ds.hpp                  
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o new_loop_normalization.lo new_loop_normalization.cpp
                    
cycle_shrinking.lo:cycle_shrinking.cpp cycle_shrinking.hpp ds.hpp                  
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o cycle_shrinking.lo cycle_shrinking.cpp
                    
readWrie.lo:readWrie.cpp readWrie.hpp ds.hpp                  
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o readWrie.lo readWrie.cpp   

main_file.lo:main_file.cpp  ds.hpp                  
	/usr/bin/libtool --mode=compile $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o main_file.lo main_file.cpp 
  
extShrinking.lo:extShrinking.cpp extShrinking.hpp ds.hpp                  
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o extShrinking.lo extShrinking.cpp 
                    
CodeGen_Cycle_Shrink.lo:CodeGen_Cycle_Shrink.cpp CodeGen_Cycle_Shrink.hpp ds.hpp                  
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o CodeGen_Cycle_Shrink.lo CodeGen_Cycle_Shrink.cpp                     
                                                    
affinec.lo:affinec.cpp affinec.hpp ds.hpp                  
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o affinec.lo affinec.cpp  

CodeGen_Affinekernal_Interface.lo:CodeGen_Affinekernal_Interface.cpp CodeGen_Affinekernal_Interface.hpp ds.hpp                  
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o CodeGen_Affinekernal_Interface.lo CodeGen_Affinekernal_Interface.cpp 
                            
Dependence_Testing_Interface.lo:Dependence_Testing_Interface.cpp Dependence_Testing_Interface.hpp ds.hpp                  
	/usr/bin/libtool --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w  -I$(ROSE_INCLUDE_DIR) $(BOOST_CPPFLAGS) -c -o Dependence_Testing_Interface.lo Dependence_Testing_Interface.cpp         
	
	
# Rule used by make installcheck to verify correctness of installed libraries
check:
	./main_file -c -w $(ROSE_SOURCE_DIR)/in.c
	
	

	
	
	
	
	                                                                                                                       
