CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS  = -g3 -Wall -Wextra -std=c++11

gerp: gerp.o ReadFile.o Search.o Hashing.o FSTreeTraversal.o  
	${CXX} ${LDFLAGS} -o gerp gerp.cpp ReadFile.cpp Search.cpp Hashing.cpp \
	    			FSTreeTraversal.cpp DirNode.o FSTree.o

gerp.o:   gerp.cpp

ReadFile.o:    ReadFile.cpp   ReadFile.h

Search.o:       Search.cpp Search.h

Hashing.o:	Hashing.cpp Hashing.h

FSTreeTraversal.o: FSTreeTraversal.cpp FSTreeTraversal.h

.PHONY: gerp

clean:
	rm -rf gerp *.dSYM

provide:
	provide comp15 proj2part3 \
	    gerp.cpp ReadFile.cpp ReadFile.h Search.cpp Search.h \
	    Hashing.cpp Hashing.h FSTreeTraversal.cpp FSTreeTraversal.h \
	    DirNode.o DirNode.h FSTree.o FSTree.h \
	    Makefile README
