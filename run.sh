#/usr/bin/env bash

files=`ls Instances/Testes`

for arch in $files; do

	for i in `seq 1 30`; do
		./app -i $arch >> execucoes/${arch}_parc
	done

done
