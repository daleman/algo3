set terminal pdf
set output "ej3a.pdf"

set key left
set xlabel "Cantidad de Casilleros Vacíos (n)"
set ylabel "Tiempo (segundos) [ESCALA LOGARÍTMICA]"
set yrange [0.000001:1000]
set logscale y

set style line 1 lc rgb '#0060ad' lt 1 lw 2 # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 0.3 # --- red
set style line 3 lc rgb '#18dd1f' lt 1 lw 2 pt 7 ps 0.3 # --- green
set style line 4 lc rgb '#dd181f' lt 1 lw 2 pt 1 ps 0.3 # --- red
set style line 5 lc rgb '#18dd1f' lt 1 lw 2 pt 1 ps 0.3 # --- green

plot 'testn.out' title 'ej3' w yerrorbars ls 2 ,\
	'testnsp.out' title 'ej3 sin podas' w yerrorbars ls 3, \
	'testmm.out' using 1:2 title '' w points ls 4, \
	'testmm.out' using 1:3 title '' w points ls 4, \
	'testmm.out' using 1:6 title '' w points ls 5, \
	'testmm.out' using 1:7 title '' w points ls 5, \
	4**x /4000000 title '4^n' w lines ls 1

set output "ej3b.pdf"
set xlabel "Cantidad de Casilleros Totales (w*h)"

plot 'testwh.out' title 'ej3' w yerrorbars ls 2 ,\
	'testwhsp.out' title 'ej3 sin podas' w yerrorbars ls 3, \
	'testmm.out' using 1:4 title '' w points ls 4, \
	'testmm.out' using 1:5 title '' w points ls 4, \
	'testmm.out' using 1:8 title '' w points ls 5, \
	'testmm.out' using 1:9 title '' w points ls 5, \
	4**x /3500000 title '4^n' w lines ls 1 
