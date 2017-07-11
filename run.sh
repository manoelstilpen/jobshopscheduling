#/usr/bin/env bash

files=`ls Instances/Testes`
rm execucoes/*

for arch in $files; do
	for modo in sprt mod priority; do
		echo -n "${modo} " >> execucoes/${arch}_parc
		./app -i $arch -r 30 -a 0.7 -m $modo >> execucoes/${arch}_parc
	done

	for modo in sprt mod priority; do
		echo -n "${modo} " >> execucoes/${arch}_guloso
		./app -i $arch -a 0 -m $modo >> execucoes/${arch}_guloso
	done

done
