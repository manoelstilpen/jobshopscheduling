#!/usr/bin/env bash

files=`ls instances/testes`
rm execucoes/*

echo -n "Script initialized at: " && date

for arch in ${files}; do
	for i in `seq 0 10`; do
		#echo -n "mod " >> execucoes/${arch}
		./app -i instances/${arch} >> execucoes/${arch}
	done
done

echo -n "Script ended at: " && date
