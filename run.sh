#/usr/bin/env bash

files=`ls Instances/Testes`

for arch in $files; do
	for modo in sprt priority mod; do
		./app -i $arch -r 30 -a 0.7 -m $modo >> execucoes/${arch}_parc
	done

	for modo in sprt priority mod; do
		./app -i $arch -a 0 -m $modo >> execucoes/${arch}_parc
	done

done
