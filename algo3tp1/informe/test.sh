cd ../codigo/ej1
make
./testGen > ej1.in
./ej1 < ej1.in > ej1.out
#gnuplot plot "ej1.out"
cd ../ej2
make
./testGen > ej2.in
./ej2 < ej2.in > ej2.out
#gnuplot plot "ej2.out"
cd ../ej3
make
./testGen > ej3.in
./ej3 < ej3.in > ej3.out
#gnuplot plot "ej3.out"
