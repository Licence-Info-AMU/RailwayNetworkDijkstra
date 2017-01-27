#! /bin/bash
if (($#<1)); then
	echo "Usage: $0 prog1.c [module.c ...]" >&2 ; exit 1
fi
cf="-Wall -std=c99" ; gv="gtk+-3.0" ; ob=()
for i ; do
	n=${i%.c}
	test "$i" = "$n.c" || { echo "Not a C file." >&2 ; exit 1 ;}
	ob+=("$n.o")
	echo "gcc $cf \$(pkg-config --cflags $gv) -c $i"
	gcc $cf $(pkg-config --cflags $gv) -c "$i" || exit 1
done
echo "gcc "${ob[@]}" -o "${1%.c}" \$(pkg-config --libs $gv)"
gcc "${ob[@]}" -o "${1%.c}"  $(pkg-config --libs $gv) || exit 1
echo "Success, can run ./${1%.c}"
