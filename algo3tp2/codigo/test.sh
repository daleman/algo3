
if  [ $# != 4 ]
then
	echo "El programa se llama asi: ./test.sh NUM_EJERCICIO MAX_N STEP CANT_TESTS"
	exit 0
else

	echo "inicializo los parametros"
	EJERCICIO=$1
	N=$2
	STEP=$3
	CANT=$4
	FILE=./ej${EJERCICIO}/tests/ej${EJERCICIO}_${N}_${STEP}_${CANT}

	echo "hago make en la carpeta del ejercicio actual"
	cd ./ej${EJERCICIO}
	make

	echo "hago make en la carpeta tests"
	cd ../
	make

	echo "ejecuto el test"
	mkdir -p ej${EJERCICIO}/tests
	./tests $EJERCICIO $N $STEP $CANT > $FILE.out

	echo "lo ploteo"
	ESCAPED=${FILE//\//\\\/}
	cat ej${EJERCICIO}_test.gnuplot | sed "s/ej$EJERCICIO\.pdf/$ESCAPED\.pdf/" | sed "s/ej$EJERCICIO\.out/$ESCAPED\.out/" > $FILE.gnuplot
	gnuplot $FILE.gnuplot

fi
