set terminal postscript enhanced color
set output '| ps2pdf - tests/ej1.pdf'
set title 'Performance - Ejercicio 1'
set xlabel 'Tamanio de la entrada'
set ylabel 'Cantidad de ticks'
plot "tests/ej1.dat" using 1:2 with linespoints linecolor rgb "red" title'i hate my life'
