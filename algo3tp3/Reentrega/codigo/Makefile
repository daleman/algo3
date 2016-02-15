all:	EXACTO EXACTO_TEST PEOR_CASO
	
EXACTO:
	g++ -o exacto/exacto exacto/exacto.cpp -lrt
	
EXACTO_TEST:
	g++ -o exacto/test_exacto exacto/test_exacto.cpp -lrt

PEOR_CASO:
	g++ -o exacto/test_peor_caso exacto/test_peor_caso.cpp -lrt

clean:
	rm exacto/exacto
	rm exacto/test_exacto
	rm exacto/test_peor_caso
