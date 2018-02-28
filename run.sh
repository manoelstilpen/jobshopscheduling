#!/usr/bin/env bash

files=`ls instances/testes`
rm execucoes/*

echo -n "Script initialized at: " && date

for arch in ${files}; do
	for i in `seq 0 30`; do
	    for mode in grasp vns; do
		    #echo -n "mod " >> execucoes/${arch}
		    ./app -i instances/${arch} -m ${mode} >> execucoes/${mode}_${arch}
		done
	done
done

echo -n "Script ended at: " && date
