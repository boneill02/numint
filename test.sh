#!/bin/sh

test_prog() { 
	printf "$4^5 + $5x^4 + $6x^3 + $7x^2 + $8x + $9. [$1-$2]. $3 iterations\n"
	cat << EOF | ./numint | sed '1,2d;s/^/	* /'
$1
$2
$3
$4
$5
$6
$7
$8
$9
EOF

printf '\n\n'
}

test_prog 1 10 4 1 1 1 1 1 1
test_prog 1 10 8 1 1 1 1 1 1
test_prog 1 10 64 1 1 1 1 1 1
test_prog 1 10 1024 1 1 1 1 1 1

test_prog 0 3 4 6 2 10 1 8 15
test_prog 0 3 8 6 2 10 1 8 15
test_prog 0 3 64 6 2 10 1 8 15
test_prog 0 3 1024 6 2 10 1 8 15
