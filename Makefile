# CRink Makefile

# Location of ROSE and BOOST. Use environment variable to setup for portability.
# If set properly as env variable, You should not be changing these
ROSE_INCLUDES  = -I$(ROSE_HOME)/include -I$(ROSE_HOME)/include/rose
ROSE_LIB       =   $(ROSE_HOME)/lib/librose.la
BOOST_INCLUDES = -I$(BOOST_HOME)/include 
BOOST_CPPFLAGS = -pthread $(BOOST_INCLUDES)

BOOST_LIBDIR   = -L$(BOOST_HOME)/lib
BOOST_LIBS     = -lboost_system -lboost_iostreams

CC             = gcc
CXX            = g++
CPPFLAGS       = 
CXXFLAGS       = -g -Wall
LDFLAGS        = 
LIBTOOL        = /usr/bin/libtool --quiet


LOBJS = dependency.lo gcd_banerjee.lo \
        new_loop_normalization.lo cycle_shrinking.lo \
        readWrie.lo main_file.lo extShrinking.lo \
        CodeGen_Cycle_Shrink.lo affinec.lo \
        CodeGen_Affinekernal_Interface.lo Dependence_Testing_Interface.lo

main_file: $(LOBJS)
	@echo "LINK "$@; $(LIBTOOL) --mode=link $(CXX) $(CXXFLAGS) -o $@ $(LOBJS) $(ROSE_LIB) $(BOOST_LIBDIR) $(BOOST_LIBS)

%.lo: %.h ds.hpp

%.lo: %.cpp
	@echo "COMPILE "$@; $(LIBTOOL) --mode=compile  $(CXX) $(CXXFLAGS)  $(CPPFLAGS) -w $(ROSE_INCLUDES) $(BOOST_CPPFLAGS) -c -o  $@ $<


.PHONY: clean
clean:
	$(RM) -f main_file *.lo 
