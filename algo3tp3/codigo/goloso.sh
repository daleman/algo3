make clean

make goloso

FILES1="./in1/*.in"
for f in $FILES1
do
	echo "Procesando $f"
	./goloso < $f > $f.out
done

cd ./in1
mkdir out1
for f in *.out
do
	echo "moviendo el arvhivo $f"
	mv $f out1/$f
done


