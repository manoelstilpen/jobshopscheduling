#!/bin/bash

for file in Instances/*.txt;
    do
        rm saida.txt

        for alpha in 0 0.3 0.5 0.7 0.9 1
            do
                ./app -i ${file} -a ${alpha} >> saida.txt
            done

        gnuplot -persist <<-EOFMarker

            set terminal png
            set output '${file}.png'
            set xlabel "Alpha"
            set ylabel "Atraso"
            set title '${file}'
            set grid

            plot "saida.txt" using 1:2 title 'Tempo de atraso' with linespoints

EOFMarker

    done