#!/usr/bin/env bash

files=`ls instances/testes`
#rm execucoes/*

echo -n "Script initialized at: " && date

for arch in ${files}; do
    for i in `seq 1 30`; do
        #echo -n "mod " >> execucoes/${arch}
        build/app -i instances/${arch} -m grasp >> ../execucoes/sprt_${arch}
    done
done

echo -n "Script ended at: " && date
