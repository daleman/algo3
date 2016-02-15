set terminal pdf
set output "exacto.pdf"

set key left
set xlabel "Cantidad De Nodos (n)"
set ylabel "Tiempo (segundos) [ESCALA LOGARÍTMICA]"
set xrange [0.5:52]
set yrange [0.000003:50]
set logscale y

set style line 1 lc rgb '#FF0000' lt 1 pt 0 lw 0.1 # --- red
set style line 2 lc rgb '#EE8888' lt 1 pt 0 lw 1 # --- Lred
set style line 3 lc rgb '#440000' lt 1 pt 9 ps 0.3 lw 1 # --- Dred
set style line 7 lc rgb '#440000' lt 1 pt 11 ps 0.3 lw 1 # --- Dred

set style line 4 lc rgb '#0000FF' lt 1 pt 0 lw 0.1 # --- blue
set style line 5 lc rgb '#000044' lt 1 pt 9 ps 0.3 lw 1 # --- Dblue
set style line 6 lc rgb '#000044' lt 1 pt 11 ps 0.3 lw 1 # --- Dblue

plot \
	0.0000008*(2.12**x) with lines ls 2 title '2^n', \
	'exacto.data' using 1:2 with lines ls 5 title '', \
	'exacto.data' using 1:7 with lines ls 3 title '', \
	'exacto.data' using 1:2:3:4 with yerrorbars ls 4 title 'Con Poda', \
	'exacto.data' using 1:7:8:9 with yerrorbars ls 1 title 'Sin Poda', \
	'exacto.data' using 1:5 with points ls 5 title '', \
	'exacto.data' using 1:6 with points ls 6 title '', \
	'exacto.data' using 1:10 with points ls 3 title '', \
	'exacto.data' using 1:11 with points ls 7 title ''

