CC	=g++  
CFLAGS	= -O3 -fno-builtin -mtune=core2 -D_REENTRANT -DRENDER -pthread -m64 -I/Users/wutzis_spam/root/root/include   -fno-pic  -fomit-frame-pointer  -ffast-math -ffunction-sections  -fopenmp    -msse4.1  -Wall -march=core2 -I/Users/wutzis_spam/Downloads/boost_1_47_0 
LDFLAGS	= -lSpectrum   -L/Users/wutzis_spam/Downloads/boost_1_47_0/stage/lib/  -lboost_filesystem -lboost_system -lboost_program_options 
OPTFL	=  
ROOTCFLAGS = `root-config --cflags` 
ROOTLFLAGS =  `root-config --libs`
.PHONY: plot_lib
plot_lib:$(OBJ)	
	$(CC) $(CFLAGS)$(ROOTCFLAGS) $(OPTFL)  -fPIC  -c plot_lib.cpp
	ar -cq libplot.a plot_lib.o
.PHONY: test
test: 
	$(CC) $(CFLAGS) $(ROOTCLFAGS) $(OPTFL) -c test.cpp
	$(CC) $(LDFLAGS) $(ROOTLFLAGS) -L. -lplot -o  ep test.o




