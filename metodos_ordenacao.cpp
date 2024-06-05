#include <stdio.h>
#include <stdlib.h> 
#include <time.h> // Para medir o tempo de execu��o

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Consumir caracteres do buffer at� encontrar uma nova linha ou EOF
}

// Fun��o para carregar n�meros de um arquivo para um vetor din�mico
int *carregarArquivo(const char *nome_arquivo, int *tamanho) {
    int x;
    FILE *file; // cria ponteiro que aponta para arquivo
    file = fopen(nome_arquivo, "r"); // coloca na vari�vel o arquivo escolhido
    if (file == NULL) { // Controle para caso o arquivo n�o exista
        printf("Arquivo nao pode ser aberto");
        return NULL; // Retorna NULL se o arquivo n�o puder ser aberto
    }

    int *vetor = NULL; // Vetor para armazenar os n�meros

    // Ler os n�meros do arquivo e armazen�-los em um vetor din�mico
    while (fscanf(file, "%i", &x) == 1) { // L� os n�meros at� o final do arquivo
        (*tamanho)++;
        vetor = (int*)realloc(vetor, (*tamanho) * sizeof(int)); // Realoca o vetor para armazenar o pr�ximo elemento
        vetor[(*tamanho) - 1] = x; // Armazena o elemento no vetor
    }

    fclose(file); // fecha o arquivo
    
    return vetor; // Retorna o vetor com os n�meros carregados do arquivo
}

// Fun��o para exibir o menu e retornar o nome do arquivo escolhido
char *menu() {
    int op = 0;
    char *arquivo = (char *)malloc(sizeof(char) * 20); // Alocar mem�ria para o nome do arquivo
    do {
        printf("===============================================\n");
        printf("\t\tArquivos para ordenar:\n\n");
        printf("1- 50 numeros(duplicado/decrescente)\n");
        printf("2- 100 numeros(unico/aleatorios)\n");
        printf("3- 500 numeros(duplicado/concavo)\n");
        printf("4- 5000 numeros(unico/concavo)\n");
        printf("5- 10000 numeros(unico/aleatorio)\n");
        printf("6- 500000 numeros(unico/decrescente)\n");
        printf("7- Sair do programa\n");
        printf("===============================================\n->>");
        scanf("%d", &op);
        switch (op) {
            case 1:
                arquivo = "dtdecre50dup3.txt";
                break;
            case 2:
                arquivo = "dtaleat100uni0.txt";
                break;
            case 3:
                arquivo = "dtconcv500dup4.txt";
                break;
            case 4:
                arquivo = "dtconcv5kuni2.txt";
                break;
            case 5:
                arquivo = "dtcresc10kuni4.txt";
                break;
            case 6:
            	arquivo = "dtdecre50kdup8.txt";
            	break;
            case 7:
            	exit(1);
            	break;
            default:
                printf("Digite um numero valido\n");
        }
    } while (op < 1 || op > 7);
    return arquivo;
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Troca os elementos
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void bubbleSort(int vetor[], int n) {
    int k, j, aux;
    for (k = 0; k < n - 1; k++) {
        for (j = 0; j < n - k - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

int particionar(int *vetor, int inicio, int fim)
{
	int pivo = (vetor[inicio] + vetor[fim] + vetor[(inicio + fim)/2]) / 3;
	while(inicio < fim)
	{
		while(inicio < fim && vetor[inicio] <= pivo)
		{
			inicio++;
		}
		while(inicio < fim && vetor[fim] > pivo)
		{
			fim--;
		}
		int auxiliar = vetor[inicio];
		vetor[inicio] = vetor[fim];
		vetor[fim] = auxiliar;
	}
	return inicio;
}

void quickSort(int *vetor, int inicio, int fim)
{
	if(inicio < fim)
	{
		int pos = particionar(vetor, inicio, fim);
		quickSort(vetor, inicio, pos-1);
		quickSort(vetor, pos, fim);
	}
}


void mensagem(double tempos[]) {
    printf("\n\n------------------------------------------------------------------------------\n");
printf("\t\t\tRESULTADOS:\n\n");
double mais_rapido = tempos[0];
double segundo_mais_rapido = tempos[1];
double mais_lento = tempos[2];

// Verifica se os tempos s�o iguais e trata separadamente
if (mais_rapido == segundo_mais_rapido) {
    printf("\tAmbos os algoritmos mais r�pidos foram o ");
    if (mais_rapido == tempos[0]) {
        printf("Selection Sort");
    } else if (mais_rapido == tempos[1]) {
        printf("Bubble Sort");
    } else {
        printf("Quick Sort");
    }
    printf(", levaram %.6f segundos.\n", mais_rapido);
} else {
    // Encontra o algoritmo mais r�pido
    if (segundo_mais_rapido < mais_rapido) {
        mais_rapido = tempos[1];
        segundo_mais_rapido = tempos[0];
    }
    if (mais_lento < mais_rapido) {
        double temp = mais_rapido;
        mais_rapido = mais_lento;
        mais_lento = temp;
    }
    if (mais_lento < segundo_mais_rapido) {
        double temp = segundo_mais_rapido;
        segundo_mais_rapido = mais_lento;
        mais_lento = temp;
    }

    printf("\tO algoritmo mais rapido foi o ");
    if (mais_rapido == tempos[0]) {
        printf("Selection Sort");
    } else if (mais_rapido == tempos[1]) {
        printf("Bubble Sort");
    } else {
        printf("Quick Sort");
    }
    printf(", levou %.6f segundos.\n", mais_rapido);

    printf("\tO segundo algoritmo mais rapido foi o ");
    if (segundo_mais_rapido == tempos[0]) {
        printf("Selection Sort");
    } else if (segundo_mais_rapido == tempos[1]) {
        printf("Bubble Sort");
    } else {
        printf("Quick Sort");
    }
    printf(", levou %.6f segundos.\n", segundo_mais_rapido);
}

printf("\tO algoritmo mais lento foi o ");
if (mais_lento == tempos[0]) {
    printf("Selection Sort");
} else if (mais_lento == tempos[1]) {
    printf("Bubble Sort");
} else {
    printf("Quick Sort");
}
printf(", levou %.6f segundos.\n", mais_lento);

printf("\n------------------------------------------------------------------------------");
}

int main() {
    double vetor_tempo[3]; //vetor para salvar o tempo de cada m�todo
    int tamanho = 0;
    do{
    	tamanho = 0;
    	// Obter o nome do arquivo selecionado pelo usu�rio atrav�s do menu
	    char *arquivo = menu();
	
	    // Carregar n�meros do arquivo
	    int *vetor = carregarArquivo(arquivo, &tamanho);
	    if (vetor == NULL) {
	        return 1; // Encerra o programa se o arquivo n�o puder ser carregado
	    }
	
	    // Medi��o do tempo de execu��o
	    clock_t inicio, fim;
	    double tempo_execucao;
	
	    //selection sort
		printf("----------------------------------------------\n");
		inicio = clock(); // Marca o in�cio do tempo de execu��o
		// Ordena os n�meros usando Selection Sort
		selectionSort(vetor, tamanho);
		// Imprime os n�meros ordenados
		printf("Numeros lidos e ordenados do arquivo:\n");
		for (int j = 0; j < tamanho; j++) {
		    printf("%i\n", vetor[j]);
		}
		fim = clock(); // Marca o fim do tempo de execu��o
		tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC; // Calcula o tempo de execu��o em segundos
		printf("\nTempo de execucao (Selection Sort): %.6f", tempo_execucao); // Imprime o tempo de execu��o
		vetor_tempo[0] = tempo_execucao;
		
		// Bubble sort
		printf("\n----------------------------------------------\n");
		inicio = clock(); // Marca o in�cio do tempo de execu��o
		// Ordena os n�meros usando Bubble Sort
		bubbleSort(vetor, tamanho);
		///Imprime os n�meros ordenados
		printf("\nNumeros lidos e ordenados do arquivo:\n");
		for (int j = 0; j < tamanho; j++) {
		    printf("%i\n", vetor[j]);
		}
		fim = clock(); // Marca o fim do tempo de execu��o
		tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC; // Calcula o tempo de execu��o em segundos
		printf("\nTempo de execucao (Bubble Sort): %.6f", tempo_execucao); // Imprime o tempo de execu��o
		printf("\n----------------------------------------------\n");
		// Libera a mem�ria alocada para o vetor din�mico
		vetor_tempo[1] = tempo_execucao;
		// Quick sort
	    printf("\n----------------------------------------------\n");
	    inicio = clock(); // Marca o in�cio do tempo de execu��o
	    // Ordena os n�meros usando Quick Sort
	    quickSort(vetor, 0, tamanho - 1);
	    // Imprime os n�meros ordenados
	    printf("\nNumeros lidos e ordenados do arquivo:\n");
	    for (int j = 0; j < tamanho; j++) {
	        printf("%i\n", vetor[j]);
	    }
	    fim = clock(); // Marca o fim do tempo de execu��o
	    tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC; // Calcula o tempo de execu��o em segundos
	    printf("\nTempo de execucao (Quick Sort): %.6f", tempo_execucao); // Imprime o tempo de execu��o
	    vetor_tempo[2] = tempo_execucao;
	    printf("\n----------------------------------------------\n");
	    // Libera a mem�ria alocada para o vetor din�mico
	    free(vetor);
	    mensagem(vetor_tempo);
	    printf("\nPressione qualquer tecla para continuar...");
	    limparBuffer();
	    getchar();
	}while(1);
    
    return 0;
}



