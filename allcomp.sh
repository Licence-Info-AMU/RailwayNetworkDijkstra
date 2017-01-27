#! /bin/bash
for f in *.c ; do
	test -s "$f" || continue  # fichier vide
	test "$f" -nt "${f%.c}.o" || continue
	./compgtk3.sh "$f"
done
