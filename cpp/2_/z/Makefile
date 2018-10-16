SRC=main.cpp
CPPFLAGS=-Wall -Wpedantic -Werror -O3 -std=c++14
LDFLAGS=
OFNAME=main

build:
	@g++ ${CPPFLAGS} ${SRC} -o ${OFNAME} ${LDFLAGS}

run: build
	@./${OFNAME}

clean:
	@rm -f ${OFNAME} *.o
