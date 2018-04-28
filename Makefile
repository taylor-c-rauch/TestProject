CXX=clang++ $(CXXFLAGS)
DEBUG=-Wall -g
CXXFLAGS=-Wall -O2 -std=c++11
OFILES=test.o

.SUFFIXES: .o .cpp

output: $(OFILES)
	$(CXX) $(OFILES)

clean:
	-rm -f *.o *~ outputfile
test.o: test.cpp
