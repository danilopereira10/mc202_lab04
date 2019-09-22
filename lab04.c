#include <stdio.h>
#include <stdlib.h>

int chegouAoFimDaLinha(int i, int n) {
	if (i % (n - 1) == 0) {
		return 1;	
	}
	return 0;
}

void imprimeMatriz(int m, int n, char** matriz) {
	for (int i = 0; i < 2; i++) {
		printf("%s", matriz[i]);	
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
	//char matriz[m][n];
	char** matriz;
	//char discard = ' ';

	matriz = malloc(m * sizeof(char *));
	for (int i = 0; i < 2; i++) {
		matriz[i] = malloc(n * sizeof(char));
		for (int j = 0; j < n; j++) {
			//scanf("%c", &discard);
			scanf("%c", &matriz[i][j]);
			if (j == n - 1) {
				//scanf("%c", &discard);		
			} 		
		}
		printf("%s", matriz[i]);
		printf("\n");
	}


	
	//imprimeMatriz(m, n, matriz);


	return EXIT_SUCCESS;
}


