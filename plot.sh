#!/bin/bash

for file in Instances/*.txt;
    do

        rm grasp.txt
        rm greedy.txt

        for mode in grasp greedy
            do

                for alpha in 0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1
                    do
                        ./app -m ${mode} -i ${file} -a ${alpha} >> ${mode}.txt
                    done
            done

                gnuplot -persist <<-EOFMarker

                    set terminal png
                    set output '${file}.png'
                    set xlabel "Alpha"
                    set ylabel "Atraso"
                    set title '${file}'
                    set grid

                    plot "grasp.txt" using 1:2 title 'GRASP' with linespoints, \
                        "greedy.txt" using 1:2 title 'GREEDY' with linespoints
EOFMarker

    done