#/usr/bin/env bash

files=`ls Instances/Testes`
rm execucoes/*

for arch in $files; do
	for i in `seq 1 30`; do
		echo -n "mod " >> execucoes/${arch}
		./app -i $arch -a 0.7 >> execucoes/${arch}
	done
done
