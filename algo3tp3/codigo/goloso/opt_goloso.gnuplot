set terminal pdf
set output "opt_goloso.pdf"

set key left bottom
set xlabel "Cantidad De Nodos (n)"
set ylabel "Diferencia con la solución óptima (Porcentaje)"
set xrange [1:102]
set yrange [-40:0.5]

set style line 1 lc rgb '#FF0000' lt 1 pt 0 lw 0.1 # --- red
set style line 2 lc rgb '#FFFF00' lt 1 pt 0 lw 1 # --- yellow
set style line 3 lc rgb '#440000' lt 1 pt 9 ps 0.3 lw 1 # --- Dred
set style line 4 lc rgb '#440000' lt 1 pt 11 ps 0.3 lw 1 # --- Dred

plot \
	0 with lines ls 2 title 'Óptimo', \
	'opt_goloso.data' using 1:2 with lines ls 3 title '', \
	'opt_goloso.data' using 1:2:3:4 with yerrorbars ls 1 title 'Goloso', \
	'opt_goloso.data' using 1:5 with points ls 3 title '', \
	'opt_goloso.data' using 1:6 with points ls 4 title ''
