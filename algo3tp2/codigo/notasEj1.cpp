/*
j=2
	co[2]= c02 + cc01; uom[2] = 1
	i=1
		ca= c01 + c12 + cc21
		(1>1) ? no
		(ca < co[2]) {	uom[2] = uom[1] (0)

j=3
	co[3]= c03 + cc02; uom[3] = 2
	i=1
		ca= c01 + c13 + cc22
		(2>1) ? si: + c02
		(ca < co[3]) {	uom[3] = j-1 (2)
	i=2
		ca= co[2] + c23 + cc32
		(1>1) ? no
		(ca < co[3]) {	uom[3] = uom[2] (1 o 0)

j=4
	co[4]= c04 + cc03; uom[4] = 3
	i=1
		ca= c01 + c14 + cc23
		(3>1) ? si: + c02
		(ca < co[4]) {	uom[4] = j-1 (3)
	i=2
		ca= co[2] + c24 + cc33
		(2>1) ? si: + cX3 con X ultimoOtraMaquina[2] (0 o 1)
		(ca < co[4]) {	uom[4] = uom[2] (0 o 1)
	i=3
		ca= co[3] + c34 + cc43
		(1>1) ? no
		(ca < co[4]) {	uom[4] = uom[3] (0, 1 o 2)

*/


/*
 * Tenemos que formar una matriz que diga en la casilla (i,j) cuanto es el costo minimo de la configuracion
dado el trabajo i despues del trabajo j.

Para eso vamos a realizar el algoritmo agregando los trabajos en orden (del trabajo 1 al n).

Para poner el trabajo 1 hay solo una opcion, que es el costo de prepararla al inicio.

Luego para preparar el trabajo 2 hay dos opciones:
	Prepararla despues del trabajo 1
	Prepararla al inicio en la otra maquina.
Notar que estos dos costos ya estarian en la matriz (que me sirven para memorizar los resultados) y no los deberia calcular.

Para la maquina 3 hay tres maneras posibles:
	Prepararla al inicio en la otra maquina + Lo que cuesta preparar desde el trabajo 1 hasta el 2
	Prepararla despues del trabajo 1 		+ Lo que cuesta preparar desde el trabajo 2 hasta el 2
	Prepararla despues del trabajo 2 		+ 0 
	Prepararla al inicio en la otra maquina.
	
Para la maquina 8 hay siete maneras posibles:
	Prepararla al inicio en la otra maquina + Lo que cuesta preparar desde el trabajo 1 hasta el 7
	Prepararla despues del trabajo 1 		+ Lo que cuesta preparar desde el trabajo 2 hasta el 7
	Prepararla despues del trabajo 2 		+ Lo que cuesta preparar desde el trabajo 3 hasta el 7
	...
	...
	...
	Prepararla despues del trabajo 6		+ Lo que cuesta preparar desde el trabajo 7 hasta el 7
	Prepararla despues del trabajo 7 		+ 0
	
Luego para la maquina i existen i-1 posibilidades de colocar a cada maquina. Se puede calcular
las i-1 posibilidades de agregar el trabajo i en estas i-1 posibilidades (solo debo sumar el costo de preparar el trabajo
i luego del trabajo j + el costo de preparar desde el trabajo j+1 hasta el i-1 ).

A su vez uno debe tener ya precomputado en otra matriz lo que cuesta preparar los trabajos desde el trabajo i hasta el trabajo j.

supongamos que tengo la siguiente matriz de costos
0	0	0	0	0
3	0	0	0	0		--->	0	5	11	15	16
1	2	0	0	0		--->	0	0	5	6	8
2	4	6	0	0		--->	0	0	0	
3	2	1	4	0		--->	0	0	0	0	
5	1	3	2	1		--->	0	0	0	0	0



MATRIZ COSTOS:: (t FILAS x t+1 COLUMNAS) -> EN Cij ESTÁ EL COSTO DE
	PONER EL TRABAJO j DESPUÉS DEL TRABAJO i (ES EL Cij ENTRADA)

C00	C01	C02	C03	C04	C05
C10	C11	C12	C13	C14	C15
C20	C21	C22	C23	C24	C25
C30	C31	C32	C33	C34	C35
C40	C41	C42	C43	C44	C45
C50	C51	C52	C53	C54	C55 <- NO HACE FALTA

___	C01	C02	C03	C04	C05
___	___	C12	C13	C14	C15
___	___	___	C23	C24	C25
___	___	___	___	C34	C35
___	___	___	___	___	C45

MATRIZ CONSECUTIVOS:: (t FILAS x t+1 COLUMNAS) -> EN Cij ESTÁ EL
	COSTO DE PONER COMO CONSECUTIVOS A TODOS ENTRE EL i Y EL j.

C00		C01		C02			C03				C04					C05
C10		C11		C12			C13				C14					C15
C20		C21		C22			C23				C24					C25
C30		C31		C32			C33				C34					C35
C40		C41		C42			C43				C44					C45
C50		C51		C52			C53				C54					C55 <- NO HACE FALTA

___		C01		C02			C03				C04					C05
___		___		C12			C13				C14					C15
___		___		___			C23				C24					C25
___		___		___			___				C34					C35
___		___		___			___				___					C45
___		___		___			___				___					___

___		C01		C01+C12		C01+C12+C23		C01+C12+C23+C34		C01+C12+C23+C34+C45
___		___		C12			C12+C23			C12+C23+C34			C12+C23+C34+C45
___		___		___			C23				C23+C34				C23+C34+C45
___		___		___			___				C34					C34+C45
___		___		___			___				___					C45



	int cantTrabajos ;
	cin >> cantTrabajos;
	
	vector<int> minimosPorNivel(cantTrabajos);
	
	// Me creo la primera matriz, mientras recibo el input de los costos
	
	int **matrizCostos;
	int **matrizConsecutivos;
	int **matrizDinamica;
	matrizCostos  = new int*[cantTrabajos];
	matrizConsecutivos  = new int*[cantTrabajos];
	matrizDinamica  = new int*[cantTrabajos];
	
	for( int i = 0; i < cantTrabajos+1; ++i){
		matrizCostos[i] = new int[cantTrabajos];
		matrizConsecutivos[i] = new int[cantTrabajos];
		matrizDinamica[i] = new int[cantTrabajos];
	}
	
	for ( int i =0 ; i< cantTrabajos; ++i)
	{
		for (int j=0; j< cantTrabajos ; ++j)
		{
			if (j < i)
				cin >> matrizCostos[i][j];
			else
				matrizCostos[i][j] = 0;
			
		}
	}
	
	cout << "Ahora viene la matrizCostos" << endl;
	mostrarMatriz ( matrizCostos, cantTrabajos, cantTrabajos );
	
	//  Computo la matriz de costos consecutivos
		
	for (int i = 0; i < cantTrabajos; i++)
	{
		int temp = matrizCostos[i][0];	//poner el trabajo i en la maquina inicialmente
		int fila = i+1;
		for (int j = i+1; j < cantTrabajos; j++)
		{
			temp += matrizCostos[fila][fila];
			matrizConsecutivos[i][j] = temp;
			fila++; 
		}
	}
	
	
	cout << "Ahora viene la matrizConsecutivos" << endl;
	mostrarMatriz ( matrizConsecutivos, cantTrabajos, cantTrabajos );
	
	
	// Termine de computar la matriz de costos consecutivos.
	
	// Ahora voy a crear la matriz dinamica colocando el casilla i,j el menor costo de poner el trabajo i despues del trabajo j.


	matrizDinamica[0][0] = matrizCostos[0][0];
	minimosPorNivel[0] = matrizCostos[0][0];
	int trabajoIPostJ = 0;
	
	for (int i = 1; i < cantTrabajos; i++)
	{
		int minimoDeNivel = INT_MAX;
		for (int j = 0; j < i+1 ; j++)
		{		
			//Poner la maquina i despues de la j + lo minimo de configurar hasta la i + matrizConsecutivos desde la j+1 hasta la i-1
			trabajoIPostJ = minimosPorNivel[i-1]+matrizCostos[i][j] + matrizConsecutivos[j+1][i-1];
			minimoDeNivel = min(minimoDeNivel,trabajoIPostJ);
			matrizDinamica[i][j] = trabajoIPostJ;
		}
		minimosPorNivel[i] = minimoDeNivel;
	}
}*/
