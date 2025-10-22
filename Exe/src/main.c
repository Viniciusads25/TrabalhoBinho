/*
 * main.c
 *
 *  Created on: 20 de out. de 2025
 *      Author: vn092
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrega.h"
#include "lista.h"

// Funções auxiliares para leitura segura
void ler_texto(const char *mensagem, char *texto, int tamanho) {
    printf("%s", mensagem);
    fflush(stdout);
    fgets(texto, tamanho, stdin);

    // Remove o '\n' final se existir
    size_t len = strlen(texto);
    if (len > 0 && texto[len - 1] == '\n') {
        texto[len - 1] = '\0';
    }
}

void ler_double_positivo(double *valor, const char *mensagem) {
    int valid;
    do {
        printf("%s", mensagem);
        fflush(stdout);
        valid = scanf("%lf", valor);

        // Limpa buffer em caso de entrada inválida
        while (valid != 1){
        	while (getchar() != '\n');
        	printf("Entrada inválida! Digite um número.\n");
        	printf("%s", mensagem);
        	fflush(stdout);
        	valid = scanf("%lf", valor);
        }
        while(*valor < 0){
        	printf("O valor não pode ser negativo. Tente novamente.\n");
        	printf("%s", mensagem);
        	fflush(stdout);
        	valid = scanf("%lf", valor);
        }


    } while (*valor < 0);
}

// Lê um int positivo
void ler_int_positivo( int *valor, const char *mensagem) {
    int valid;
    do {
        printf("%s", mensagem);
        fflush(stdout);
        valid = scanf("%d", valor);

        while (valid != 1){
        	while (getchar() != '\n');
        	printf("Entrada inválida! Digite um número.\n");
        	printf("%s", mensagem);
        	fflush(stdout);
        	valid = scanf("%lf", valor);
                }
        while(*valor < 0){
        	printf("O valor não pode ser negativo. Tente novamente.\n");
        	printf("%s", mensagem);
        	fflush(stdout);
        	valid = scanf("%lf", valor);
                }

    } while (*valor < 0);
}

void ler_prioridade(int *prioridade) {
    int valid;
    do {
        printf("Informe a prioridade da entrega (1-3): ");
        fflush(stdout);
        valid = scanf("%d", prioridade);

        if (valid != 1) {
            while (getchar() != '\n');
            printf("Entrada inválida! Digite 1, 2 ou 3.\n");
            continue;
        }

        if (*prioridade < 1 || *prioridade > 3) {
            printf("Prioridade inválida! Apenas 1, 2 ou 3 são válidos.\n");
        }

    } while (*prioridade < 1 || *prioridade > 3);
}

void ler_numeros(double *peso, double *distancia, double *tempo, double *custo) {
    ler_double_positivo(peso, "Informe o peso da encomenda: ");
    ler_double_positivo(distancia, "Informe a distância: ");
    ler_double_positivo(custo, "Informe o custo da entrega: ");
    ler_double_positivo(tempo, "Informe o tempo de entrega: ");
}

int main() {
    Lista *lista = NULL;
    int opcao;

    char origem[32], destino[32];
    double peso, distancia, custo, tempo;
    int prioridade;
    Entrega *nova = NULL;

    do {
        printf("\n#########################\n");
        printf("         MENU\n");
        printf("#########################\n");
        printf("1 - Inicializar lista.\n");
        printf("2 - Criar e adicionar entrega na lista A\n");
        printf("3 - Remover entrega da lista A\n");
        printf("4 - Imprimir lista A\n");
        printf("5 - Ordenar lista A por prioridade\n");
        printf("6 - Editar Entrega.\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção:");
        fflush(stdout);

        scanf("%d", &opcao);
        while(getchar() != '\n');

        switch (opcao) {
            case 1:
                if (!lista) {
                    lista = inicializar_entregas(lista);
                    printf("Lista criada com sucesso.\n");
                } else {
                    printf("Lista já foi criada.\n");
                }
                break;
            case 2:
                if (!lista) {
                    printf("Crie a lista A antes de adicionar entregas.\n");
                    break;
                }
                ler_texto("Informe a Origem:", origem, 32);
                ler_texto("Informe o Destino:", destino, 32);
                ler_numeros(&peso, &distancia, &custo, &tempo);
                ler_prioridade(&prioridade);

                nova = criar_entrega(origem, destino, peso, distancia, prioridade, custo, tempo, lista);
                if (nova) {
                    adicionar_entrega(lista, nova);
                    printf("Entrega criada e adicionada com sucesso (ID: %d).\n", nova->id);
                } else {
                    printf("Erro ao criar entrega.\n");
                }
                break;
            case 3:
                if (!lista || lista->tamanho == 0) {
                    printf("Lista vazia, não há entregas para remover.\n");
                } else {
                    int id_remover;
                    ler_int_positivo(&id_remover, "Informe o ID da entrega a ser removida: ");
                    remover_entrega(lista, id_remover);
                    printf("Entrega removida, se o ID existir.\n");
                }
                break;
            case 4:
                if (!lista || lista->tamanho == 0) {
                    printf("Lista vazia.\n");
                } else {
                    percorrer_lista(lista, mostrar_entrega);
                }
                break;
            case 5:
                if (!lista || lista->tamanho < 0) {
                    printf("Lista vazia ou com menos de 2 elementos.\n");
                } else {
                    ordenar_prioridade_entrega(lista);
                    printf("Lista ordenada por prioridade.\n");
                    fflush(stdout);
                }
                break;
            case 6: // opção para editar
            	if (!lista || lista->tamanho < 0) {
            		printf("Lista vazia.\n");
            	}else{
                printf("Digite o ID da entrega que deseja editar: ");
                fflush(stdout);
                int id_editar;
                scanf("%d", &id_editar);
                while(getchar() != '\n'); // limpa buffer
                editar_entrega(lista, id_editar);
            	}
                break;

            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 0);

    if (lista) destruir_lista(lista, destruir_entrega);
    if (listaB) destruir_lista(listaB, destruir_entrega);

    return 0;
}
