set terminal pdf
set output "golosa-local.pdf"

set key left bottom
set xlabel "Cantidad De Nodos (n)"
set ylabel "Diferencia con la solución óptima (Porcentaje)"
set xrange [1:152]
set yrange [-35:0.5]

set style line 1 lc rgb '#FF0000' lt 0 pt 0 lw 0.1 # --- GOLOSO red
set style line 2 lc rgb '#FFFF00' lt 1 pt 0 lw 1 # --- yellow
set style line 3 lc rgb '#980000' lt 1 pt 9 ps 0.3 lw 1 # --- Dred
set style line 4 lc rgb '#980000' lt 1 pt 11 ps 0.3 lw 1 # --- Dred

set style line 5 lc rgb '#333333' lt 0 pt 0 lw 0.1 # --- LOCAL () black
set style line 6 lc rgb '#000000' lt 1 pt 9 ps 0.3 lw 1 # --- Dblack
set style line 7 lc rgb '#000000' lt 1 pt 11 ps 0.3 lw 1 # --- Dblack

set style line 20 lc rgb '#FF6000' lt 0 pt 0 lw 0.1 # --- LOCAL (G) orange
set style line 21 lc rgb '#BD4700' lt 1 pt 9 ps 0.3 lw 1 # --- Dorange
set style line 22 lc rgb '#BD4700' lt 1 pt 11 ps 0.3 lw 1 # --- Dorange

set style line 23 lc rgb '#BD4700' lt 1 pt 0 ps 0.3 lw 1 # --- Dorange Local (G)
set style line 24 lc rgb '#000000' lt 1 pt 0 ps 0.3 lw 1 # --- Dblack Local ()
set style line 25 lc rgb '#980000' lt 1 pt 0 ps 0.3 lw 1 # --- Dred Goloso

plot \
	0 with lines ls 2 title 'Óptimo', \
	'comp_local2.data' using 1:2 with linespoints ls 23 title 'Local (Sol. Golosa)', \
	'comp_local2.data' using 1:2:3:4 with yerrorbars ls 20 title '', \
	'comp_local2.data' using 1:5 with points ls 21 title '', \
	'comp_local2.data' using 1:6 with points ls 22 title '', \
	'comp_local.data' using 1:2 with linespoints ls 24 title 'Local (Sol. Vacía)', \
	'comp_local.data' using 1:2:3:4 with yerrorbars ls 5 title '', \
	'comp_local.data' using 1:5 with points ls 6 title '', \
	'comp_local.data' using 1:6 with points ls 7 title '', \
	'comp_goloso.data' using 1:2 with linespoints ls 25 title 'Goloso', \
	'comp_goloso.data' using 1:2:3:4 with yerrorbars ls 1 title '', \
	'comp_goloso.data' using 1:5 with points ls 3 title '', \
	'comp_goloso.data' using 1:6 with points ls 4 title ''
