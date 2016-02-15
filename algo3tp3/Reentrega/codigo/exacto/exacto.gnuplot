set terminal pdf
set output "exacto.pdf"

set key left
set xlabel "Cantidad De Nodos (n)"
set ylabel "Tiempo (segundos) [ESCALA LOGARÍTMICA]"
set xrange [0.5:30.5]
set yrange [0.0000103:5500]
set logscale y

set style line 1 lc rgb '#FF0000' lt 1 pt 0 lw 0.1 # --- red
set style line 2 lc rgb '#EE8888' lt 1 pt 0 lw 1 # --- Lred
set style line 3 lc rgb '#440000' lt 1 pt 9 ps 0.3 lw 1 # --- Dred
set style line 7 lc rgb '#440000' lt 1 pt 11 ps 0.3 lw 1 # --- Dred

set style line 4 lc rgb '#0000FF' lt 1 pt 0 lw 0.1 # --- blue
set style line 5 lc rgb '#000044' lt 1 pt 9 ps 0.3 lw 1 # --- Dblue
set style line 6 lc rgb '#000044' lt 1 pt 11 ps 0.3 lw 1 # --- Dblue

set style line 8 lc rgb '#00FF00' lt 1 pt 0 lw 0.1 # --- green
set style line 9 lc rgb '#004400' lt 1 pt 9 ps 0.3 lw 1 # --- Dgreen
set style line 10 lc rgb '#004400' lt 1 pt 11 ps 0.3 lw 1 # --- Dgreen

plot \
	0.0000002*(2**x)*x with lines ls 2 title 'n.2^n', \
	'exacto2p.data' using 1:2 with lines ls 9 title '', \
	'exacto.data' using 1:2 with lines ls 5 title '', \
	'exactosp.data' using 1:2 with lines ls 3 title '', \
	'exactosp.data' using 1:2:3:4 with yerrorbars ls 1 title 'Sin Poda', \
	'exacto.data' using 1:2:3:4 with yerrorbars ls 4 title 'Con Poda', \
	'exacto2p.data' using 1:2:3:4 with yerrorbars ls 8 title '2 Podas', \
	'exacto2p.data' using 1:5 with points ls 9 title '', \
	'exacto2p.data' using 1:6 with points ls 10 title '', \
	'exacto.data' using 1:5 with points ls 5 title '', \
	'exacto.data' using 1:6 with points ls 6 title '', \
	'exactosp.data' using 1:5 with points ls 3 title '', \
	'exactosp.data' using 1:6 with points ls 7 title ''

