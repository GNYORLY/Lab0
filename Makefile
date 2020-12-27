#!/bin/bash
#Jeannie Chiem
#'gnyorly@gmail.com'
#ID:504666652

.SILENT: check testComplete testOpt testIO testSeg

default:
	gcc -Wall -Wextra -g lab0.c -o lab0

check: default testComplete testOpt testIO testSeg
	if [ -s log.txt ]; then \
        cat log.txt; \
        echo "Check failed"; \
	else \
        echo "Passed all checks"; \
	fi; \
	rm -f lab0 log.txt;

clean:
	rm -f lab0 *.txt lab0-504666652.tar.gz

dist:
	tar -czvf lab0-504666652.tar.gz Makefile README lab0.c breakpoint.png backtrace.png

testComplete:
	echo "hello world" > input.txt; \
	echo | ./lab0 -i input.txt -o output.txt &>/dev/null; \
	if [ $$? -ne 0 ]; then \
        echo "ERROR-program failed to complete" >> log.txt; \
	fi; \
	rm -f input.txt output.txt

testOpt:
	echo | ./lab0 -p &>/dev/null; \
	if [ $$? -ne 1 ]; then \
        echo "ERROR-program failed to catch invalid argument" >> log.txt; \
	fi

testIO:
	echo "hello world" > test.txt;
	chmod u-rwx test.txt;
	echo | ./lab0 -i test.txt &>/dev/null; \
	if [ $$? -ne 2 ]; then \
        echo "ERROR-incorrect handling of input" >> log.txt; \
	fi;	\
	echo | ./lab0 -o test.txt &>/dev/null; \
	if [ $$? -ne 3 ]; then \
        echo "ERROR-incorrect handling of output" >> log.txt; \
	fi; \
	rm -f test.txt

testSeg:
	echo | ./lab0 -s -c &>/dev/null; \
	if [ $$? -ne 4 ]; then \
        echo "ERROR-program failed to catch segfault" >> log.txt; \
	fi

