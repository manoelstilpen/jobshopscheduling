#!/usr/bin/env bash

files=`ls instances/testes`
#rm execucoes/*

echo -n "Script initialized at: " && date

for arch in ${files}; do
	for i in `seq 1 30`; do
	    for alpha in 0.3; do
		    #echo -n "mod " >> execucoes/${arch}
            build/app -i instances/${arch} -m cons -a ${alpha} >> execucoes/asprt_${alpha}_${arch}
            sleep 1
		done
	done
done

echo -n "Script ended at: " && date
