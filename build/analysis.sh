#!/bin/bash

for file in sphere teapot locomotive man bouddha1m; do
	echo "### $file ###"
	./SurfaceMeasurer -t 2 ../data/$file.off | grep Processing | sed 's/.* \([\.0-9]\+\)s/\1/'
	./SurfaceMeasurer -t 2 ../data/$file.off | grep Processing | sed 's/.* \([\.0-9]\+\)s/\1/'
	./SurfaceMeasurer -t 4 ../data/$file.off | grep Processing | sed 's/.* \([\.0-9]\+\)s/\1/'
	./SurfaceMeasurer -t 8 ../data/$file.off | grep Processing | sed 's/.* \([\.0-9]\+\)s/\1/'
	./SurfaceMeasurer -omp ../data/$file.off | grep Processing | sed 's/.* \([\.0-9]\+\)s/\1/'
	echo -e "\n\n"
done
