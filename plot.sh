#!/bin/bash

for file in Instances/abz5_f13.txt;
    do

        rm *.txt

        for mode in sprt priority
            do
                for alpha in 0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1
                    do
                        ./app -m ${mode} -i ${file} -a ${alpha} -r 20 >> ${mode}.txt
                    done
            done

                gnuplot -persist <<-EOFMarker

                    set terminal png
                    set output 'teste.png'
                    set xlabel "Alpha"
                    set ylabel "Atraso"
                    set title '${file}'
                    set grid

                    plot "priority.txt" using 1:2 title 'PRIORITY' with linespoints, \
                        "sprt.txt" using 1:2 title 'SPRT' with linespoints
                        

EOFMarker

    done