#!/bin/bash

for file in sphere teapot locomotive man bouddha1m; do
	echo "### $file ###"
	echo -e "Algo\tResults\t\t\t\t\t\t\t\t\t\t\t\t\tAverage"
	for arg in "t 0" "t 2" "t 4" "t 8" "omp"; do
		echo -en "$arg, \t"
		avg=0
		for i in {1..10}; do
			x=$(./SurfaceMeasurer -$arg ../data/$file.off | grep Processing | sed 's/.* \([\.0-9]\+\)ms/\1/' | tr -d '\n')
			if [ "$(python -c "if $avg == 0: print('true')")" == "true" ]; then
				avg="$x"
			else
				avg=$(python -c "print(($avg + $x)/2)")
			fi
			echo -n "$x, "
		done
		echo $avg
	done
done
