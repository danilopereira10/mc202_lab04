#include <stdio.h>
#include <stdlib.h>

#define PARA_DIREITA '1'
#define PARA_BAIXO '2'
#define PARA_ESQUERDA '3'
#define PARA_CIMA '4'
#define MATOU_O_MINOTAURO 1
#define NAO 'N'
#define SIM 'Y'
#define PERDEU 0
#define Y_ENTRADA 0
#define ACHOU_ESPADA 1
#define NAO_ACHOU_ESPADA 0
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
char conseguiu_espada;
char direcao;
//int linha;
//int coluna;

int resolve_possibilidades_de_matar_minotauro(int linha, int coluna);
int resolve_minotauro(int linha, int coluna);
int possibilidades_de_achar_espada(int linha, int coluna);
int achar_espada(int linha, int coluna);

int possibilidades_de_achar_espada(int linha, int coluna) {
	if (direcao == PARA_DIREITA) {
		if (!achar_espada(linha, coluna + 1)) {
			direcao = PARA_BAIXO;
			if (!achar_espada(linha + 1, coluna)) {
				direcao = PARA_CIMA;
				return achar_espada(linha - 1, coluna);
			} else {
				return ACHOU_ESPADA;
			}
		} else {
			return ACHOU_ESPADA;
		}
	} else if (direcao == PARA_BAIXO) {
		direcao = PARA_DIREITA;
		if (!achar_espada(linha, coluna + 1)) {
			direcao = PARA_BAIXO;
			if(!achar_espada(linha + 1, coluna)) {
				direcao = PARA_ESQUERDA;
				return achar_espada(linha, coluna - 1);
			} else {
				return ACHOU_ESPADA;
			}
		} else {
			return ACHOU_ESPADA;
		}
	} else if (direcao == PARA_ESQUERDA) {
		direcao = PARA_BAIXO;
		if (!achar_espada(linha + 1, coluna)) {
			direcao = PARA_ESQUERDA;
			if (!achar_espada(linha, coluna - 1)) {
				direcao = PARA_CIMA;
				return achar_espada(linha - 1, coluna);
			} else {
				return ACHOU_ESPADA;
			}
		} else {
			return ACHOU_ESPADA;
		}
	} else {
		direcao = PARA_DIREITA;
		if (!achar_espada(linha, coluna + 1)) {
			direcao = PARA_ESQUERDA;
			if (!achar_espada(linha, coluna - 1)) {
				direcao = PARA_CIMA;
				return achar_espada(linha - 1, coluna);
			} else {
				return ACHOU_ESPADA;
			}
		} else {
			return ACHOU_ESPADA;
		}
	}
}

int resolve_possibilidades_de_matar_minotauro(int linha, int coluna) {
	if (direcao == PARA_DIREITA) {
		if (!resolve_minotauro(linha, coluna + 1)) {
			direcao = PARA_BAIXO;
			if (!resolve_minotauro(linha + 1, coluna)) {
				direcao = PARA_CIMA;
				return resolve_minotauro(linha - 1, coluna);
			} else {
				return MATOU_O_MINOTAURO;
			}
		} else {
			return MATOU_O_MINOTAURO;
		}
	} else if (direcao == PARA_BAIXO) {
		direcao = PARA_DIREITA;
		if (!resolve_minotauro(linha, coluna + 1)) {
			direcao = PARA_BAIXO;
			if(!resolve_minotauro(linha + 1, coluna)) {
				direcao = PARA_ESQUERDA;
				return resolve_minotauro(linha, coluna - 1);
			} else {
				return MATOU_O_MINOTAURO;
			}
		} else {
			return MATOU_O_MINOTAURO;
		}
	} else if (direcao == PARA_ESQUERDA) {
		direcao = PARA_BAIXO;
		if (!resolve_minotauro(linha + 1, coluna)) {
			direcao = PARA_ESQUERDA;
			if (!resolve_minotauro(linha, coluna - 1)) {
				direcao = PARA_CIMA;
				return resolve_minotauro(linha - 1, coluna);
			} else {
				return MATOU_O_MINOTAURO;
			}
		} else {
			return MATOU_O_MINOTAURO;
		}
	} else {
		direcao = PARA_DIREITA;
		if (!resolve_minotauro(linha, coluna + 1)) {
			direcao = PARA_ESQUERDA;
			if (!resolve_minotauro(linha, coluna - 1)) {
				direcao = PARA_CIMA;
				return resolve_minotauro(linha - 1, coluna);
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

int achar_espada(int linha, int coluna) {
	if (linha >= m || coluna >= n || linha < 0 || coluna < 0) {
		return NAO_ACHOU_ESPADA;
	}

	if (M[linha][coluna] == 'E' || M[linha][coluna] == '#' || posicao_visitada[linha][coluna]) {
		posicao_visitada[linha][coluna] = 1;
		return NAO_ACHOU_ESPADA;
	} 

	posicao_visitada[linha][coluna] = 1;
	
	if (M[linha][coluna] == 'M') {
		return NAO_ACHOU_ESPADA;
	}
	
	if (M[linha][coluna] == 'S') {
		reinicializar_vetor_visitados();
		posicao_visitada[linha][coluna] = 1;
		conseguiu_espada = SIM;
		return ACHOU_ESPADA;
	} 
	
	if (possibilidades_de_achar_espada(linha, coluna)) {
		M[linha][coluna] = '*';
		return ACHOU_ESPADA;
	}

	return NAO_ACHOU_ESPADA;
}

int resolve_minotauro(int linha, int coluna) {
	if (linha >= m || coluna >= n || linha < 0 || coluna < 0) {
		return PERDEU;
	}

	if (M[linha][coluna] == 'E' || M[linha][coluna] == '#' || posicao_visitada[linha][coluna]) {
		posicao_visitada[linha][coluna] = 1;
		return PERDEU;
	} 

	posicao_visitada[linha][coluna] = 1;
	
	if (M[linha][coluna] == 'M' && conseguiu_espada == SIM) {
		return MATOU_O_MINOTAURO;
	} 
	
	if (M[linha][coluna] == 'M' && conseguiu_espada == NAO) {
		return PERDEU;
	} 
	
	if (resolve_possibilidades_de_matar_minotauro(linha, coluna)) {
		M[linha][coluna] = '*';
		return MATOU_O_MINOTAURO;
	}

	return PERDEU;
}

void achar_coordenadas_espada(int *linha, int* coluna) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if(M[i][j] == 'S') {
				*linha = i;
				*coluna = j;
				return;
			}
		}
	}

}

int comecar_resolucao (int linha, int coluna) {
	M[linha][coluna] = '*';
	conseguiu_espada = NAO;
	direcao = PARA_DIREITA;
	if (!achar_espada(linha, coluna + 1)) {
		direcao = PARA_BAIXO;
		if (!achar_espada(linha + 1, coluna)) {
			direcao = PARA_ESQUERDA;
			if (!achar_espada(linha, coluna - 1)) {
				direcao = PARA_CIMA;
				achar_espada(linha - 1, coluna);
			}
		}
	}
	
	int linha_espada = -1, coluna_espada = -1;
	achar_coordenadas_espada(&linha_espada, &coluna_espada);
	linha = linha_espada;
	coluna = coluna_espada;

	direcao = PARA_DIREITA;
	if (!resolve_minotauro(linha, coluna + 1)) {
		direcao = PARA_BAIXO;
		if (!resolve_minotauro(linha + 1, coluna)) {
			direcao = PARA_ESQUERDA;
			if (!resolve_minotauro(linha, coluna - 1)) {
				direcao = PARA_CIMA;
				return resolve_minotauro(linha - 1, coluna);
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
		scanf("%*c"); //descarta \n
		int j;
		for (j = 0; j < n; j++) {
			char caracter;
			scanf("%c", &caracter);
			linha[j] = caracter;
		}
		linha[j] = '\0';
		M[i] = linha;

		linha = malloc((n + 1) * sizeof(char));
	}
	free(linha);

	int x_entrada;

	 for (int i = 0; i < n; i++) {
		if (M[0][i] == 'E') {
			x_entrada = i;
			break;
		}		
	}
	
	comecar_resolucao(Y_ENTRADA + 1, x_entrada);

	imprimir_matriz();
	destruir_matriz_mapa();
	destruir_matriz_visitados();

	return EXIT_SUCCESS;
}



