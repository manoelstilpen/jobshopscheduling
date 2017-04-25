#!/bin/bash

for file in Instances/*.txt;
    do

        rm *.txt

        for mode in sprt
            do
                for alpha in 0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1
                    do
                        ./app -m ${mode} -i ${file} -a ${alpha} -r 20 >> ${mode}.txt
                    done
            done

                  gnuplot -persist <<-EOFMarker

                    set terminal png
                    set output 'sprt.png'
                    set xlabel "Alpha"
                    set ylabel "Atraso"
                    set title 'SPRT'
                    set grid

                    plot "sprt.txt" using 1:2 title 'ESCOLHA FIXA' with linespoints
                        

EOFMarker

    done