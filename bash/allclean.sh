#! /bin/bash
for f in *.c ; do
	test -f "${f%.c}.o" && rm -f "${f%.c}.o"
	test -f "${f%.c}" && rm -f "${f%.c}"
	test -f "$f~" && rm -f "$f~"
done
