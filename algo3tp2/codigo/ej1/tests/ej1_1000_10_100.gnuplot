set terminal pdf
set output "./ej1/tests/ej1_1000_10_100.pdf"

set key left
set xlabel "Cantidad Trabajos (n)"
set ylabel "Tiempo (segundos)"
set yrange [0:]

set style line 1 lc rgb '#0060ad' lt 1 lw 2 # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 7 ps 0.3 # --- red

plot './ej1/tests/ej1_1000_10_100.out' title 'ej1(n)' with yerrorbars ls 2 ,  x * x /20500000 title 'f(n) = C * n^2' w lines ls 1
