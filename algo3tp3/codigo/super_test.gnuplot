set terminal pdf
set output "super_test.pdf"

set key left
set xlabel "Cantidad De Nodos (n)"
set ylabel "Tiempo (segundos) [ESCALA LOGARÍTMICA]"
set xrange [1:155]
set yrange [0.00002:1000]
set logscale y

set style line 1 lc rgb '#FF0000' lt 1 pt 0 lw 0.1 # --- GOLOSO red
set style line 3 lc rgb '#980000' lt 1 pt 9 ps 0.3 lw 1 # --- Dred
set style line 4 lc rgb '#980000' lt 1 pt 11 ps 0.3 lw 1 # --- Dred

set style line 11 lc rgb '#0060FF' lt 1 pt 0 lw 0.1 # --- TABU V=1 blue
set style line 12 lc rgb '#0042AE' lt 1 pt 9 ps 0.3 lw 1 # --- Dblue
set style line 13 lc rgb '#0042AE' lt 1 pt 11 ps 0.3 lw 1 # --- Dblue

set style line 5 lc rgb '#00FF00' lt 1 pt 0 lw 0.1 # --- LOCAL V=2 green
set style line 6 lc rgb '#004400' lt 1 pt 9 ps 0.3 lw 1 # --- Dgreen
set style line 7 lc rgb '#004400' lt 1 pt 11 ps 0.3 lw 1 # --- Dgreen

set style line 8 lc rgb '#000000' lt 0 pt 11 ps 0.3 lw 1 # --- black

set style line 14 lc rgb '#FFFF00' lt 1 pt 0 lw 0.1 # --- EXACTO yellow
set style line 15 lc rgb '#444400' lt 1 pt 9 ps 0.3 lw 1 # --- Dyellow
set style line 16 lc rgb '#444400' lt 1 pt 11 ps 0.3 lw 1 # --- Dyellow

set style line 20 lc rgb '#00FFBA' lt 1 pt 0 lw 0.1 # --- LOCAL V=3 cyan
set style line 21 lc rgb '#00AB77' lt 1 pt 9 ps 0.3 lw 1 # --- Dcyan
set style line 22 lc rgb '#00AB77' lt 1 pt 11 ps 0.3 lw 1 # --- Dcyan

set style line 17 lc rgb '#7800FF' lt 1 pt 0 lw 0.1 # --- TABU V=2 violet
set style line 18 lc rgb '#43008E' lt 1 pt 9 ps 0.3 lw 1 # --- Dviolet
set style line 19 lc rgb '#43008E' lt 1 pt 11 ps 0.3 lw 1 # --- Dviolet

set style line 23 lc rgb '#00FFBA' lt 1 pt 0 ps 0.3 lw 1 # --- Dcyan Local V=3
set style line 24 lc rgb '#00FF00' lt 1 pt 0 ps 0.3 lw 1 # --- Dgreen Local V=2
set style line 25 lc rgb '#980000' lt 1 pt 0 ps 0.3 lw 1 # --- Dred Goloso
set style line 26 lc rgb '#7800FF' lt 1 pt 0 ps 0.3 lw 1 # --- Dpurple Tabu V=2
set style line 27 lc rgb '#0060FF' lt 1 pt 0 ps 0.3 lw 1 # --- Dblue Tabu V=1
set style line 29 lc rgb '#FFFF00' lt 1 pt 0 ps 0.3 lw 1 # --- Dyellow Exacto

plot \
	0.0000008*(2.12**x) with lines ls 8 title '2^n', \
	'exacto.data' using 1:2 with lines ls 29 title 'Exacto', \
	'exacto.data' using 1:2:3:4 with yerrorbars ls 14 title '', \
	'exacto.data' using 1:5 with points ls 15 title '', \
	'exacto.data' using 1:6 with points ls 16 title '', \
	'tabu2.data' using 1:2 with lines ls 26 title 'Tabu V = 2', \
	'tabu2.data' using 1:2:3:4 with yerrorbars ls 17 title '', \
	'tabu2.data' using 1:5 with points ls 18 title '', \
	'tabu2.data' using 1:6 with points ls 19 title '',\
	'tabu.data' using 1:2 with lines ls 27 title 'Tabu V = 1', \
	'tabu.data' using 1:2:3:4 with yerrorbars ls 11 title '', \
	'tabu.data' using 1:5 with points ls 12 title '', \
	'tabu.data' using 1:6 with points ls 13 title '',\
	'local2.data' using 1:2 with lines ls 23 title 'Local V = 3', \
	'local2.data' using 1:2:3:4 with yerrorbars ls 20 title '', \
	'local2.data' using 1:5 with points ls 21 title '', \
	'local2.data' using 1:6 with points ls 22 title '', \
	'local.data' using 1:2 with lines ls 24 title 'Local V = 2', \
	'local.data' using 1:2:3:4 with yerrorbars ls 5 title '', \
	'local.data' using 1:5 with points ls 6 title '', \
	'local.data' using 1:6 with points ls 7 title '', \
	'goloso.data' using 1:2 with lines ls 25 title 'Goloso', \
	'goloso.data' using 1:2:3:4 with yerrorbars ls 1 title '', \
	'goloso.data' using 1:5 with points ls 3 title '', \
	'goloso.data' using 1:6 with points ls 4 title ''
