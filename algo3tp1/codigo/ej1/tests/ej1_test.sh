if (( "$#" != 3 )) 
then
  echo "Para correr un test, ejecutar este script con los parametros: n maximo, salto entre n y cantidad de test cases para cada n."
  echo "Por ejemplo ./correrTests 100 10 5 = ejecutar tests desde n = 0 hasta n = 100, con saltos de 10 en n y 5 tests para cada n."
  exit 1
fi
cd ..
echo 'Compilando...'
make
echo 'Listo.'
cd tests
echo 'Corriendo tests...'
./ej1_test $1 $2 $3 > test.out
echo 'Listo'
echo 'Archivo con los resultados creado en test.out'
echo 'Graficando...'
gnuplot ej1_test.gnuplot
echo 'Listo'
