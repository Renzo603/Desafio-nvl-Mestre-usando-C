// TRABALHO PRÁTICO - ESTRUTURAS DE DADOS
// ALUNO: RENZO FRATTIN 202408142961
// ALUNO: VINICIUS PULHIESE DE MELLO 202408142919

#include <stdio.h>      // Biblioteca padrão de entrada e saída
#include <stdlib.h>     // Biblioteca padrão
#include <string.h>     // Biblioteca para manipulação de strings
#include <stdbool.h>    // Biblioteca para trabalhar com booleanos

#define MAX_ITENS 10    // Define a quantidade máxima de itens da mochila
#define MAX_STRING 30   // Define a quantidade máxima de caracteres das strings

// Estrutura que representa um item da mochila
typedef struct {
    char nome[50];      // Nome do item
    char tipo[30];      // Tipo do item
    int quantidade;     // Quantidade (não utilizado no programa)
    int prioridade;     // Nível de prioridade do item
} Item;

// Enum para definir os critérios de ordenação disponíveis
typedef enum {
    NOME = 1,           // Ordenar por nome
    TIPO = 2,           // Ordenar por tipo
    PRIORIDADE = 3      // Ordenar por prioridade
} Ordenacao;

// Fução do Bubble Sort com contagem de comparações
int bubbleSort(Item mochila[], int n, Ordenacao criterio){
	int comparacoes = 0;
	int i, j;
	
	for (i = 0; i < n; i++){ //Percorre a mochila
		for(j = 0; j < n - i - 1; j++){
			comparacoes++;
			
			bool cond = false; //Condição de ordenção
			
			if(criterio == NOME){
				cond = strcmp(mochila[j].nome,  mochila[j+1].nome) > 0; //Compara os nomes
			}
			else if(criterio == TIPO){
				cond = strcmp(mochila[j].tipo, mochila[j+1].tipo) > 0; //Compara os tipos
			}
			else if(criterio == PRIORIDADE){
				cond = mochila[j].prioridade > mochila[j+1].prioridade; //Compara as prioridades
			}
			
			if(cond) {
				Item temp = mochila[j];
				mochila[j] = mochila[j + 1];
				mochila[j + 1] = temp;
			}
		}
	}
	return comparacoes;
}
// Função do Insertion Sort com contagem de comparações
int insertionSort(Item mochila[], int n, Ordenacao criterio) {
    int comparacoes = 0;
    int i;
    for (i = 1; i < n; i++) { //Percorre a mochila
        Item atual = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            bool cond = false; //Condição de ordenção
            if (criterio == NOME){
                cond = strcmp(mochila[j].nome, atual.nome) > 0;//Compara os nomes
			}
            else if (criterio == TIPO){
                cond = strcmp(mochila[j].tipo, atual.tipo) > 0;//Compara os tipos
			}
            else if (criterio == PRIORIDADE){
                cond = mochila[j].prioridade > atual.prioridade;//Compara as prioridades
			}

            if (cond){
                mochila[j + 1] = mochila[j]; // Desloca item para direita
			}
            else{
                break;
			}
            j--;
        }
        mochila[j + 1] = atual; // Insere na posição correta
    }
    return comparacoes;
}

// Função do Selection Sort com contagem de comparações
int selectionSort(Item mochila[], int n, Ordenacao criterio) {
    int i, j, comparacoes = 0;

    for (i = 0; i < n - 1; i++) { //Percorre a mochila
        int min = i;

        for (j = i + 1; j < n; j++) {

            comparacoes++;
            bool cond = false; //Condição de ordenação

            if (criterio == NOME){
                cond = strcmp(mochila[j].nome, mochila[min].nome) < 0; //Compara os nomes
			}	 
            else if (criterio == TIPO){
                cond = strcmp(mochila[j].tipo, mochila[min].tipo) < 0; //Compara os tipos
			}	 
            else if (criterio == PRIORIDADE){
                cond = mochila[j].prioridade < mochila[min].prioridade; //Compara os prioridades
			}
				
            if (cond){
                min = j;
			}
        }
		
		// Troca os itens (se necessário)
        if (min != i) {
            Item temp = mochila[i];
            mochila[i] = mochila[min];
            mochila[min] = temp;
        }
    }

    return comparacoes;
}

// Função de Menu de organização
void orgarnizarMochila(Item mochila[],int *qtdItens){
	int escolha = 0, ordem;
	printf("\n-----| ORGANIZAR MOCHILA |-----\n\n");
	
	if(*qtdItens <= 0){
		printf("Sua mochila esta vazia\n");
		return;
	}
	printf("Escolha o criterio de ordenacao: \n\n");
	printf("[ 1 ] Nome\n");
	printf("[ 2 ] Tipo\n");
	printf("[ 3 ] Prioridade\n\n");
	printf(">>>>>> ");
	scanf("%d", &escolha); // Escolhe qual o critério de ordenação
	
	printf("\n\nEscolha o metodo de alteracao: \n\n");
	printf("[ 1 ] Bubble Sort\n");
	printf("[ 2 ] Insertion Sort\n");
	printf("[ 3 ] Selection Sort\n\n");
	printf(">>>>> ");
	scanf("%d", &ordem); // Escolhe qual será a forma de ordenação
	
	Ordenacao ord = (Ordenacao)ordem;
	int comparacoes = 0;
	
	if(escolha < 1 || escolha > 3){
		printf("Opcao invalida");
		return;
	}
	
	if (escolha == 1){
		comparacoes = bubbleSort(mochila, *qtdItens, ord);
	}
	
	if(escolha == 2){
		comparacoes = insertionSort(mochila, *qtdItens, ord);
	}
	if(escolha == 3){
		comparacoes = selectionSort(mochila, *qtdItens, ord);
	}
	
	printf("\nMochila ordenada com sucesso!\n");
    printf("Comparacoes realizadas: %d\n\n", comparacoes);

    printf("Pressione ENTER para voltar...");
    getchar(); getchar();
}
// Função Busca binária
int buscaBinaria(Item mochila[], int n, char nomeBusca[], Item *resultado) {
	int esq = 0, dir = n - 1, comparacoes = 0; //Inicia os indices
    while (esq <= dir) {
        int meio = (esq + dir) / 2; //Calcula o meio
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, nomeBusca); // Compara os nomes 
        if (cmp == 0) { // Nome encontrado
            *resultado = mochila[meio];
            return comparacoes;  //Retorna o numero de comparações
        } else if (cmp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return -comparacoes; // Retorna negativo quando não encontra
}

// Menu de busca binaria
void menuBuscaBinaria(Item mochila[], int qtdItens) {
	if (qtdItens <= 0) {
		printf("\nA mochila esta vazia!\n");
		getchar(); getchar();
		return;
	}

	printf("\n----- BUSCA BINARIA -----\n");
	printf("Digite o nome do item para buscar: ");
	getchar();
	char nomeBusca[MAX_STRING];
	fgets(nomeBusca, MAX_STRING, stdin);
	nomeBusca[strcspn(nomeBusca, "\n")] = 0;


	Item achado;
	int resultado = buscaBinaria(mochila, qtdItens, nomeBusca, &achado);
	
	if (resultado > 0) {
		printf("\nItem encontrado!\n");
		printf("Nome: %s\nTipo: %s\nPrioridade: %d\n", achado.nome, achado.tipo, achado.prioridade);
	}
	 
	else {
		printf("\nItem nao encontrado!\n");
	}

	printf("Comparacoes realizadas: %d\n", resultado < 0 ? -resultado : resultado);
	printf("Pressione ENTER para voltar...");
	getchar();
}

// Função para adicionar item na mochila
void adicionarComponente(Item mochila[], int *qtdItens) {
    printf("\n-----| Adicionando componente |-----\n\n");
    
    if (*qtdItens >= MAX_ITENS) { // Verifica quantos itens na mochila
        printf("Mochila estï¿½ cheia!\n\n");
        return;
    }
    
    Item itemColetado;
    getchar();
    
    printf("Nome: ");
    fgets(itemColetado.nome, MAX_STRING, stdin);
    itemColetado.nome[strcspn(itemColetado.nome, "\n")] = 0;
    
    printf("Tipo (Eletronico, Estrutural, Energia): ");
    fgets(itemColetado.tipo, MAX_STRING, stdin);
    itemColetado.tipo[strcspn(itemColetado.tipo, "\n")] = 0;
    
    printf("Prioridade: ");
    scanf("%d", &itemColetado.prioridade);
    
    mochila[*qtdItens] = itemColetado;
    (*qtdItens)++;
    
    printf("\nItem armazenado na mochila!\n\n");
}

// Função para listar os itens na mochila
void listarItens(Item mochila[], int *qtdItens) {
    int i;

    printf("-----| MOCHILA |-----\n");
    
    if (*qtdItens <= 0) {
        printf("Sua mochila esta vazia\n\n");
        printf("Pressione ENTER para voltar...");
        getchar(); getchar();        
        return;
    }
    
    printf("%-20s | %-20s | %-15s\n", "NOME", "TIPO", "PRIORIDADE");
    for (i = 0; i < *qtdItens; i++) {
        printf("%-20s | %-20s | %-15d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].prioridade);
    }
    
    printf("\nPressione ENTER para voltar...");
    getchar(); getchar();
}

// Função para remover o item da mochila
void removerItem(Item mochila[], int *qtdItens) {
    int i, j, encontrado = 0;
    char escolha[MAX_STRING];
    
    printf("-----| REMOVER |-----\n");
    
    if (*qtdItens <= 0) {
        printf("Sua mochila esta vazia\n\n");
        printf("Pressione ENTER para voltar...");
        getchar(); getchar();        
        return;
    }
    
    printf("Nome do item para remover: ");
    getchar();
    fgets(escolha, MAX_STRING, stdin);
    escolha[strcspn(escolha, "\n")] = 0;

    for (i = 0; i < *qtdItens; i++) {
        if (strcmp(escolha, mochila[i].nome) == 0) {
            for (j = i; j < *qtdItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtdItens)--;
            encontrado = 1;
            printf("\nItem '%s' removido com sucesso!\n\n", escolha);
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nï¿½o encontrado na mochila.\n\n", escolha);
    }

    printf("Pressione ENTER para voltar...");
    getchar();
}

// Função principal
int main(){
	int qtdItens = 0; // Contador de itens
	Item mochila[MAX_ITENS]; // Array mochila, onde serão armezanados os itens
	int escolha; // Escolha do menu
	
	while(1){
		printf("==================================\n");
		printf("             NIVEL MESTRE         \n");
		printf("==================================\n\n");
		printf("Itens na mochila: %d/%d\n\n", qtdItens, MAX_ITENS);
	
		printf("[ 1 ] Adicionar componente\n");
		printf("[ 2 ] Remover componente\n");
		printf("[ 3 ] Listar componentes\n");
		printf("[ 4 ] Organizar mochila\n");
		printf("[ 5 ] Busca binaria\n");
		printf("[ 0 ] Sair\n\n");
		
		printf(">>>>> ");
		scanf("%d", &escolha);
		
		if(escolha == 1) adicionarComponente(mochila, &qtdItens);
		else if(escolha == 2) removerItem(mochila, &qtdItens);
		else if(escolha == 3) listarItens(mochila, &qtdItens);
		else if(escolha == 4) orgarnizarMochila(mochila, &qtdItens);
		else if(escolha == 5) menuBuscaBinaria(mochila, qtdItens);
		else if(escolha == 0){printf("Finalizando"); break;}
		else {printf("Opcao invalida!");}		
	}
	
	return 0;
}