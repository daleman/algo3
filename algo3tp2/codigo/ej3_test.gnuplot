set terminal pdf
set output "ej3.pdf"

set key left
set xlabel "Cantidad de Ciudades y Fábricas (n)"
set ylabel "Tiempo (segundos)"
set yrange [0:]

set style line 1 lc rgb '#0060ad' lt 1 lw 2 # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 7 ps 0.3 # --- red

plot 'ej3.out' title 'ej3(n)' with yerrorbars ls 2 ,  x * x /41000000 title 'f(n) = C * n^2' w lines ls 1
