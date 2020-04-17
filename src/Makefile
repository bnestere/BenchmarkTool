CC=gcc
CXX=$(CC)
CFLAGS=-g -O3
CXXFLAGS=-std=c++11
LDFLAGS=-lm 

SRC_FILES=benchtool.cpp writer/csv_writer.cpp utils/utils.cpp
INTERNAL_HEADERS=writer/common.hpp utils/utils.hpp


LIB_FILENAME=libbenchtool.so
HEADER_FILENAME=benchtool.h
EXT_HEADERS=benchtool benchtool_datatypes

PREFIX=/usr/local
LIB_PREFIX=lib

default: build

build: so

so: $(SRC_FILES) $(HEADER_FILENAME) $(INTERNAL_HEADERS)
	$(CXX) -shared $(CFLAGS) $(CXXFLAGS) -o $(LIB_FILENAME) -fPIC $(SRC_FILES) $(LDFLAGS)

install: so $(EXT_HEADERS)
	sudo cp $(LIB_FILENAME) $(PREFIX)/$(LIB_PREFIX)


clean:
	rm $(LIB_FILENAME)

$(EXT_HEADERS) : % :  %.h
	sudo cp $< $(PREFIX)/include

.PHONY: NIL/%
