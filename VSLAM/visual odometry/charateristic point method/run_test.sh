#!/bin/bash
mkdir -p build \
	&& cd build \
	&& scan-build-10 -o scanbuildout cmake .. \
	&& scan-build-10 -o scanbuildout make