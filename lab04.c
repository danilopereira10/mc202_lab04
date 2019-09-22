#include <stdio.h>
#include <stdlib.h>

void imprimeMatriz(int m, int n, char matriz[][n]) {
	for (int i = 0; i < m; i++) {
		printf(matriz[i]);	
		printf("\n");
	}
}

int main() {
	int m, n;

	scanf("%d %d", &m, &n);
	//char direction1;
	//char direction2;
	//char direction3;
	//char direction4;
	char matriz[m][n];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%c", &matriz[i][j]);		
		}
	}



	imprimeMatriz(m, n, matriz);


	return EXIT_SUCCESS;
}

