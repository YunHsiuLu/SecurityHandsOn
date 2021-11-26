#!/bin/sh
rm va*
for i in 2 1 0
do
	sudo sysctl -w kernel.randomize_va_space=$i
	for j in 1 2 3
	do
		echo "run: $j" >> va$i.txt
		./a.out >> va$i.txt
	done
done

