CC=gcc

all: process prefilter postfilter

process:
	gcc -o process process.c

prefilter:
	gcc -o prefilter prefilter.c

postfilter:
	gcc -o postfilter postfilter.c


.PHONY: clean
clean:
	rm process prefilter postfilter
