#/usr/bin/env bash

files=`ls Instances/Testes`
rm execucoes/*

for arch in $files; do
	./app -i $arch -r 30 -a 0.3 -m priority >> execucoes/${arch}_0-3
	./app -i $arch -r 30 -a 0.5 -m priority >> execucoes/${arch}_0-5
	./app -i $arch -r 30 -a 0.7 -m priority >> execucoes/${arch}_0-7
done
