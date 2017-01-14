#!/bin/bash

for file in Instances/*.txt;
    do

        rm grasp1.txt
        rm greedy.txt
        rm grasp2.txt

        for mode in grasp1 grasp2
            do

                for alpha in 0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1
                    do
                        ./app -m ${mode} -i ${file} -a ${alpha} -r 10 >> ${mode}.txt
                    done
            done

                gnuplot -persist <<-EOFMarker

                    set terminal png
                    set output '${file}.png'
                    set xlabel "Alpha"
                    set ylabel "Atraso"
                    set title '${file}'
                    set grid

                    plot "grasp1.txt" using 1:2 title 'GRASP 1' with linespoints, \
                        "grasp2.txt" using 1:2 title 'GRASP 2'with linespoints

EOFMarker

    done