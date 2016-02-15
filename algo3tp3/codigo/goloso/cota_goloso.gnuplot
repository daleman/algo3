set terminal pdf
set output "cota_goloso.pdf"

set key left bottom
set xlabel "Cantidad De Nodos (n)"
set ylabel "Diferencia con la solución óptima (Porcentaje)"
set xrange [1:102]
set yrange [-100:1]

set style line 1 lc rgb '#FF0000' lt 1 pt 0 ps 0.3 lw 0.1 # --- red
set style line 2 lc rgb '#FFFF00' lt 1 pt 0 lw 1 # --- yellow
set style line 3 lc rgb '#440044' lt 1 pt 0 ps 0.3 lw 1 # --- Dpurple

plot \
	0 with lines ls 2 title 'Óptimo', \
	'cota_goloso.data' using 1:3 with points ls 3 title 'Grado máximo', \
	'cota_goloso.data' using 1:2 with points ls 1 title 'Goloso'
