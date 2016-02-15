set terminal pdf
set output "opt_local.pdf"

set key left bottom
set xlabel "Cantidad De Nodos (n)"
set ylabel "Diferencia con la solución óptima (Porcentaje)"
set xrange [1:102]
set yrange [-35:0.5]

set style line 1 lc rgb '#00FF00' lt 0 pt 0 lw 1 # --- green
set style line 2 lc rgb '#FF0000' lt 0 pt 0 lw 1 # --- red
set style line 3 lc rgb '#0000FF' lt 0 pt 0 lw 1 # --- blue

set style line 7 lc rgb '#004400' lt 1 pt 9 ps 0.3 lw 1 # --- Dgreen
set style line 8 lc rgb '#440000' lt 1 pt 9 ps 0.3 lw 1 # --- Dred
set style line 9 lc rgb '#000044' lt 1 pt 9 ps 0.3 lw 1 # --- Dblue
set style line 10 lc rgb '#004400' lt 1 pt 11 ps 0.3 lw 1 # --- Dgreen
set style line 11 lc rgb '#440000' lt 1 pt 11 ps 0.3 lw 1 # --- Dred
set style line 12 lc rgb '#000044' lt 1 pt 11 ps 0.3 lw 1 # --- Dblue

set style line 13 lc rgb '#FFFF00' lt 1 pt 11 ps 0.3 lw 1 # --- yellow

plot \
	0 with lines ls 13 title 'Óptimo', \
	'opt_local3.data' using 1:2 with lines ls 9 title '', \
	'opt_local2.data' using 1:2 with lines ls 8 title '', \
	'opt_local1.data' using 1:2 with lines ls 7 title '', \
	'opt_local3.data' using 1:2:3:4 with yerrorbars ls 3 title 'local V = 3', \
	'opt_local2.data' using 1:2:3:4 with yerrorbars ls 2 title 'local V = 2', \
	'opt_local1.data' using 1:2:3:4 with yerrorbars ls 1 title 'local V = 1', \
	'opt_local3.data' using 1:5 with points ls 9 title '', \
	'opt_local3.data' using 1:6 with points ls 12 title '', \
	'opt_local2.data' using 1:5 with points ls 8 title '', \
	'opt_local2.data' using 1:6 with points ls 11 title '', \
	'opt_local1.data' using 1:5 with points ls 7 title '', \
	'opt_local1.data' using 1:6 with points ls 10 title ''
