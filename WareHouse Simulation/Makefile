#
# Makefile for Operation
#
CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra
LDFLAGS  = -g3

Nozama: main.o Operation.o Orderqueue.o \
    	Packer.o Retrieve.o Parser.o \
    	string2int.o
	${CXX} ${LDFLAGS} -o Nozama main.o Operation.o Orderqueue.o Packer.o \
					Retrieve.o Parser.o string2int.o 

main.o: main.cpp Operation.h string2int.h
Operation.o: Operation.cpp Operation.h Parser.h Packer.h Retrieve.h Orderqueue.h
Parser.o: Parser.cpp Parser.h Order.h
Packer.o: Packer.cpp Packer.h
Retrieve.o: Retrieve.cpp Retrieve.h
Orderqueue.o: Orderqueue.cpp Orderqueue.h Order.h
string2int.o: string2int.cpp string2int.h

clean:
	rm -rf Nozama *.o *~ *.dSYM

provide:
	provide comp15 proj1part2 main.cpp Operation.cpp Operation.h Packer.cpp \
	Packer.h Retrieve.cpp Retrieve.h Orderqueue.cpp Orderqueue.h Order.h \
	Parser.cpp Parser.h string2int.cpp string2int.h README Makefile
