set terminal pdf
set output "goloso.pdf"

set key left
set xlabel "Cantidad De Nodos (n)"
set ylabel "Tiempo (segundos) [ESCALA LOGARÍTMICA]"
set xrange [20:3050]
set yrange [0.0005:6]
set logscale y

set style line 1 lc rgb '#FF0000' lt 1 pt 0 lw 0.1 # --- red
set style line 2 lc rgb '#EE8888' lt 1 pt 0 lw 1 # --- Lred
set style line 3 lc rgb '#440000' lt 1 pt 9 ps 0.3 lw 1 # --- Dred
set style line 4 lc rgb '#440000' lt 1 pt 11 ps 0.3 lw 1 # --- Dred

plot \
	(0.00000000005*(x**3))+(0.00000035*(x**2)) with lines ls 2 title 'n^3', \
	'goloso.data' using 1:2 with lines ls 3 title '', \
	'goloso.data' using 1:2:3:4 with yerrorbars ls 1 title 'Goloso', \
	'goloso.data' using 1:5 with points ls 3 title '', \
	'goloso.data' using 1:6 with points ls 4 title ''
