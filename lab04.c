#include <stdio.h>
#include <stdlib.h>

#define PARA_DIREITA '1'
#define PARA_BAIXO '2'
#define PARA_ESQUERDA '3'
#define PARA_CIMA '4'
#define MATOU_O_MINOTAURO 1
#define AINDA_NAO_CONSEGUIU_ESPADA 'N'
#define JA_CONSEGUIU_ESPADA 'Y'
#define PERDEU 0
#define Y_ENTRADA 0
/* int chegouAoFimDaLinha(int i, int n) {
	if (i % (n - 1) == 0) {
		return 1;	
	}
	return 0;
}*/

/*void imprimeMatriz(int m, int n, char** matriz) {
	for (int i = 0; i < m; i++) {
		printf("%s", matriz[i]);	
		printf("\n");
	}
}*/

char** M; // matriz
int**  posicao_visitada;

int m, n;

int resolve_possibilidades_de_matar_minotauro(int linha, int coluna, char direcao, char conseguiu_espada);
int resolve_minotauro(int linha, int coluna, char direcao, char conseguiu_espada);

int resolve_possibilidades_de_matar_minotauro(int linha, int coluna, char direcao, char conseguiu_espada) {
	if (direcao == PARA_DIREITA) {
		if (!resolve_minotauro(linha, coluna + 1, PARA_DIREITA, conseguiu_espada)) {
			if (!resolve_minotauro(linha + 1, coluna, PARA_BAIXO, conseguiu_espada)) {
				return resolve_minotauro(linha - 1, coluna, PARA_CIMA, conseguiu_espada);
			} else {
				return MATOU_O_MINOTAURO;
			}
		} else {
			return MATOU_O_MINOTAURO;
		}
	} else if (direcao == PARA_BAIXO) {
		if (!resolve_minotauro(linha, coluna + 1, PARA_DIREITA, conseguiu_espada)) {
			if(!resolve_minotauro(linha + 1, coluna, PARA_BAIXO, conseguiu_espada)) {
				return resolve_minotauro(linha, coluna - 1, PARA_ESQUERDA, conseguiu_espada);
			} else {
				return MATOU_O_MINOTAURO;
			}
		} else {
			return MATOU_O_MINOTAURO;
		}
	} else if (direcao == PARA_ESQUERDA) {
		if (!resolve_minotauro(linha + 1, coluna, PARA_BAIXO, conseguiu_espada)) {
			if (!resolve_minotauro(linha, coluna - 1, PARA_ESQUERDA, conseguiu_espada)) {
				return resolve_minotauro(linha - 1, coluna, PARA_CIMA, conseguiu_espada);
			} else {
				return MATOU_O_MINOTAURO;
			}
		} else {
			return MATOU_O_MINOTAURO;
		}
	} else {
		if (!resolve_minotauro(linha, coluna + 1, PARA_DIREITA, conseguiu_espada)) {
			if (!resolve_minotauro(linha, coluna - 1, PARA_ESQUERDA, conseguiu_espada)) {
				return resolve_minotauro(linha - 1, coluna, PARA_CIMA, conseguiu_espada);
			} else {
				return MATOU_O_MINOTAURO;
			}
		} else {
			return MATOU_O_MINOTAURO;
		}
	}
}

void destruir_matriz_visitados() {
	for (int i = 0; i < m; i++) {
		free(posicao_visitada[i]);
	}
	free(posicao_visitada);
}

void reinicializar_vetor_visitados() {
	if (posicao_visitada != NULL) {
		destruir_matriz_visitados();
	}

	int* linha_visitada = malloc(n * sizeof(int));
	
	posicao_visitada = malloc(m * sizeof(linha_visitada));
	free(linha_visitada);
	
	for (int i = 0; i < m; i++) {
		linha_visitada = malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			linha_visitada[j] = 0;
		}
		posicao_visitada[i] = linha_visitada;
	}
}

int resolve_minotauro(int linha, int coluna, char direcao, char conseguiu_espada) {
	if (linha >= m || coluna >= n || linha < 0 || coluna < 0) {
		return PERDEU;
	}

	if (M[linha][coluna] == 'E' || M[linha][coluna] == '#' || posicao_visitada[linha][coluna]) {
		posicao_visitada[linha][coluna] = 1;
		return PERDEU;
	} 

	posicao_visitada[linha][coluna] = 1;
	
	if (M[linha][coluna] == 'M' && conseguiu_espada == 'Y') {
		return MATOU_O_MINOTAURO;
	} 
	
	if (M[linha][coluna] == 'M' && conseguiu_espada == 'N') {
		return PERDEU;
	} 
	
	if (M[linha][coluna] == 'S') {
		reinicializar_vetor_visitados();
		return resolve_possibilidades_de_matar_minotauro(linha, coluna, direcao, JA_CONSEGUIU_ESPADA);
	} 
	
	if (resolve_possibilidades_de_matar_minotauro(linha, coluna, direcao, conseguiu_espada)) {
		M[linha][coluna] = '*';
		return MATOU_O_MINOTAURO;
	}

	return PERDEU;
}

int comecar_resolucao (int linha, int coluna) {
	//M[linha][coluna] = '*';
	if (!resolve_minotauro(linha, coluna + 1, PARA_DIREITA, AINDA_NAO_CONSEGUIU_ESPADA)) {
		if (!resolve_minotauro(linha + 1, coluna, PARA_BAIXO, AINDA_NAO_CONSEGUIU_ESPADA)) {
			if (!resolve_minotauro(linha, coluna - 1, PARA_ESQUERDA, AINDA_NAO_CONSEGUIU_ESPADA)) {
				return resolve_minotauro(linha - 1, coluna, PARA_CIMA, AINDA_NAO_CONSEGUIU_ESPADA);
			} else {
				return MATOU_O_MINOTAURO;
			}
		} else {
			return MATOU_O_MINOTAURO;
		}
	} else {
		return MATOU_O_MINOTAURO;
	}
}

void imprimir_matriz() {
	for (int i = 0; i < m; i++) {
		printf("%s", M[i]);
		printf("\n");
	}
}
	
void destruir_matriz_mapa() {
	for (int i = 0; i < m; i++) {
		free(M[i]);
	}
	free(M);
}

int main() {
	scanf("%d %d", &m, &n);

	char* linha = malloc((n + 1) * sizeof(char)); //+1 para o caracter ('\0')

	reinicializar_vetor_visitados();

	M = malloc(m * sizeof(linha));

	for (int i = 0; i < m; i++) {
		scanf("%*c"); //descartar \n
		int j;
		for (j = 0; j < n; j++) {
			char caracter;
			scanf("%c", &caracter);
			linha[j] = caracter;
		}
		linha[j] = '\0';
		M[i] = linha;

		linha = malloc((n + 1) * sizeof(char));

		//printf("%s", M[i]); //TODO - remover isso
		// printf("\n"); //TODO - remover isso
	}
	free(linha);

	int x_entrada;

	 for (int i = 0; i < n; i++) {
		if (M[0][i] == 'E') {
			x_entrada = i;
			break;
		}		
	}

	comecar_resolucao(x_entrada, Y_ENTRADA + 1);

	imprimir_matriz();
	destruir_matriz_mapa();
	destruir_matriz_visitados();

	return EXIT_SUCCESS;
}



