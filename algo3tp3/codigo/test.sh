make clean

make 

rm goloso.out
rm exacto.out
rm local.out

FILES1="./in1/*.in"
for f in $FILES1
do
	echo "Procesando $f"
	#echo "exacto"
	./exacto/exacto < $f >> exacto.out
	#echo "goloso"
	./goloso/goloso < $f >> goloso.out
	#echo "local"
	./local/local < $f >> local.out	
done

