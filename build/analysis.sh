#!/bin/bash

for file in sphere locomotive man; do
	echo "Sequentiel"
	./SurfaceMeasurer -t 2 ../data/$file.off
	# echo "2 threads"
	# ./SurfaceMeasurer -t 2 ../data/teapot.off
	# echo "4 threads"
	# ./SurfaceMeasurer -t 4 ../data/teapot.off
	# echo "8 threads"
	# ./SurfaceMeasurer -t 8 ../data/teapot.off
	# echo "OpenMP"
	# ./SurfaceMeasurer -omp ../data/teapot.off
done
