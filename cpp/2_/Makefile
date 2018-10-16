CPPFLAGS=-Wpedantic -std=c++14 -g
LDFLAGS=
OFNAME=main
SRC=main.cpp Set.cpp MultiSet.cpp

build:
	@g++ ${CPPFLAGS} ${SRC} -o ${OFNAME} ${LDFLAGS}

run: build
	@./${OFNAME}

clean:
	@rm -f ${OFNAME} *.o