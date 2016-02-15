set terminal pdf
set output "local.pdf"

set key bottom
set xlabel "Cantidad De Nodos (n)"
set ylabel "Tiempo (segundos) [ESCALA LOGARÍTMICA]"
set xrange [5:1220]
set yrange [0.001:400]
set logscale y

set style line 1 lc rgb '#00FF00' lt 1 pt 0 lw 0.1 # --- green
set style line 2 lc rgb '#FF0000' lt 1 pt 0 lw 0.1 # --- red
set style line 3 lc rgb '#0000FF' lt 1 pt 0 lw 0.1 # --- blue

set style line 4 lc rgb '#88EE88' lt 1 pt 0 lw 1 # --- Lgreen
set style line 5 lc rgb '#EE8888' lt 1 pt 0 lw 1 # --- Lred
set style line 6 lc rgb '#8888EE' lt 1 pt 0 lw 1 # --- Lblue

set style line 7 lc rgb '#004400' lt 1 pt 9 ps 0.3 lw 1 # --- Dgreen
set style line 8 lc rgb '#440000' lt 1 pt 9 ps 0.3 lw 1 # --- Dred
set style line 9 lc rgb '#000044' lt 1 pt 9 ps 0.3 lw 1 # --- Dblue
set style line 10 lc rgb '#004400' lt 1 pt 11 ps 0.3 lw 1 # --- Dgreen
set style line 11 lc rgb '#440000' lt 1 pt 11 ps 0.3 lw 1 # --- Dred
set style line 12 lc rgb '#000044' lt 1 pt 11 ps 0.3 lw 1 # --- Dblue

set style line 13 lc rgb '#DDDD00' lt 1 pt 11 ps 0.3 lw 1 # --- yellow

plot \
	0.00000000005*0.00000001*0.0005*(2**x) with lines ls 13 title '2^n', \
	'complex.data' using 1:4 with lines ls 6 title '3*F(3)*n^3', \
	'complex.data' using 1:3 with lines ls 5 title '2*F(2)*n^3', \
	'complex.data' using 1:2 with lines ls 4 title 'F(1)*n^3', \
	'local3.data' using 1:2 with lines ls 9 title '', \
	'local2.data' using 1:2 with lines ls 8 title '', \
	'local1.data' using 1:2 with lines ls 7 title '', \
	'local3.data' using 1:2:3:4 with yerrorbars ls 3 title 'local V = 3', \
	'local2.data' using 1:2:3:4 with yerrorbars ls 2 title 'local V = 2', \
	'local1.data' using 1:2:3:4 with yerrorbars ls 1 title 'local V = 1', \
	'local3.data' using 1:5 with points ls 9 title '', \
	'local3.data' using 1:6 with points ls 12 title '', \
	'local2.data' using 1:5 with points ls 8 title '', \
	'local2.data' using 1:6 with points ls 11 title '', \
	'local1.data' using 1:5 with points ls 7 title '', \
	'local1.data' using 1:6 with points ls 10 title ''
