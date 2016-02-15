make all
./super_opt 150 2 10
cd goloso
./opt_goloso 100 1 10
./cota_goloso 100 1 10
cd ../local
./opt_local 100 2 10
cd ../tabu
./opt_tabu 100 2 10
cd ..
./golosa-local 150 2 10
