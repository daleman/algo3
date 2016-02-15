all:	GOLOSO EXACTO LOCAL TABU EXACTO_TEST GOLOSO_TEST LOCAL_TEST TABU_TEST GOLOSO_OPT LOCAL_OPT TABU_OPT GOLOSO_COTA SUPER GOLOSA-LOCAL
	
GOLOSO:
	g++ -o goloso/goloso goloso/goloso.cpp -lrt
	
EXACTO:
	g++ -o exacto/exacto exacto/exacto.cpp -lrt

LOCAL:
	g++ -o local/local local/local.cpp -lrt

TABU:
	g++ -o tabu/tabu tabu/tabu.cpp -lrt	
	
EXACTO_TEST:
	g++ -o exacto/test_exacto exacto/test_exacto.cpp -lrt
	
GOLOSO_TEST:
	g++ -o goloso/test_goloso goloso/test_goloso.cpp -lrt

LOCAL_TEST:
	g++ -o local/test_local local/test_local.cpp -lrt
	
TABU_TEST:
	g++ -o tabu/test_tabu tabu/test_tabu.cpp -lrt
	
GOLOSO_OPT:
	g++ -o goloso/opt_goloso goloso/opt_goloso.cpp -lrt

LOCAL_OPT:
	g++ -o local/opt_local local/opt_local.cpp -lrt
	
TABU_OPT:
	g++ -o tabu/opt_tabu tabu/opt_tabu.cpp -lrt
	
GOLOSO_COTA:
	g++ -o goloso/cota_goloso goloso/cota_goloso.cpp -lrt

SUPER:
	g++ -o super_opt super_opt.cpp -lrt
	g++ -o super_test super_test.cpp -lrt

GOLOSA-LOCAL:
	g++ -o golosa-local golosa-local.cpp -lrt

clean:
	rm goloso/goloso
	rm exacto/exacto
	rm local/local
	rm tabu/tabu
	rm goloso/test_goloso
	rm exacto/test_exacto
	rm local/test_local
	rm tabu/test_tabu
	rm goloso/opt_goloso
	rm local/opt_local
	rm tabu/opt_tabu
	rm goloso/cota_goloso
	rm super_test
	rm super_opt
	rm golosa-local
