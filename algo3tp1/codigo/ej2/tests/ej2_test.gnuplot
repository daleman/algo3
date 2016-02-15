set terminal pdf
set output "ej2.pdf"

set key left
set xlabel "Cantidad de Cursos (n)"
set ylabel "Tiempo (segundos)"
set yrange [0:]

set style line 1 lc rgb '#0060ad' lt 1 lw 2 # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 7 ps 0.3 # --- red
set xtics rotate by -45

plot 'test.out' title 'ej2(n)' with yerrorbars ls 2 ,  x* log (x) /37500000 title 'f(n) = n*log(n)' w lines ls 1  
