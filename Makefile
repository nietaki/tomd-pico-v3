SHELL := /bin/bash

.PHONY: all
all: build

.PHONY: clean
clean: build/Makefile
	cd build && make clean

build/Makefile: CMakeLists.txt
	cd build && cmake ..

.PHONY: build
build:
	cd build && make -j8

.PHONY: copy
copy: build
	cp build/tomd.uf2 /Volumes/RPI-RP2/tomd.uf2
