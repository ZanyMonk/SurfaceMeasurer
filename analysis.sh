#!/bin/bash

cd build
for file in sphere teapot locomotive man bouddha1m; do
	echo "### $file ###"
	./SurfaceMeasurer -a ../data/$file.off
done
