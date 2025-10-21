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
void ler_texto(char *buffer, int tamanho, const char *mensagem) {
    printf("%s", mensagem);
    fflush(stdout);
    if (fgets(buffer, tamanho, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
    }
}

void ler_double(double *valor, const char *mensagem) {
    char buffer[64];
    while (1) {
        printf("%s", mensagem);
        fflush(stdout);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL && sscanf(buffer, "%lf", valor) == 1) break;
        printf("Entrada inválida. Tente novamente.\n");
    }
}

void ler_int(int *valor, const char *mensagem) {
    char buffer[64];
    while (1) {
        printf("%s", mensagem);
        fflush(stdout);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL && sscanf(buffer, "%d", valor) == 1) break;
        printf("Entrada inválida. Tente novamente.\n");
    }
}

void ler_numeros(double *peso, double *distancia, int *prioridade, double *tempo, double *custo) {
    ler_double(peso, "Informe o peso da encomenda: ");
    ler_double(distancia, "Informe a distância: ");
    ler_int(prioridade, "Informe a prioridade da encomenda: ");
    ler_double(custo, "Informe o custo da entrega: ");
    ler_double(tempo, "Informe o tempo de entrega: ");
}

int main() {
    Lista *lista = NULL;
    Lista *listaB = NULL;
    int opcao;

    char origem[32], destino[32];
    double peso, distancia, custo, tempo;
    int prioridade;
    Entrega *nova = NULL;

    do {
        printf("\n#########################\n");
        printf("         MENU\n");
        printf("#########################\n");
        printf("1 - Inicializar lista A\n");
        printf("2 - Criar e adicionar entrega na lista A\n");
        printf("3 - Remover entrega da lista A\n");
        printf("4 - Imprimir lista A\n");
        printf("5 - Ordenar lista A por prioridade\n");
        printf("6 - Inicializar lista B\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        fflush(stdout);

        ler_int(&opcao, "");

        switch (opcao) {
            case 1:
                if (!lista) {
                    lista = inicializar_entregas(lista);
                    printf("Lista A criada com sucesso.\n");
                } else {
                    printf("Lista A já foi criada.\n");
                }
                break;
            case 2:
                if (!lista) {
                    printf("Crie a lista A antes de adicionar entregas.\n");
                    break;
                }
                ler_texto(origem, sizeof(origem), "Informe a origem: ");
                ler_texto(destino, sizeof(destino), "Informe o destino: ");
                ler_numeros(&peso, &distancia, &prioridade, &tempo, &custo);

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
                    printf("Lista A vazia, não há entregas para remover.\n");
                } else {
                    int id_remover;
                    ler_int(&id_remover, "Informe o ID da entrega a ser removida: ");
                    remover_entrega(lista, id_remover);
                    printf("Entrega removida, se o ID existir.\n");
                }
                break;
            case 4:
                if (!lista || lista->tamanho == 0) {
                    printf("Lista A vazia.\n");
                } else {
                    percorrer_lista(lista, mostrar_entrega);
                }
                break;
            case 5:
                if (!lista || lista->tamanho == 0) {
                    printf("Lista A vazia.\n");
                } else {
                    ordenar_prioridade_entrega(lista);
                    printf("Lista A ordenada por prioridade.\n");
                }
                break;
            case 6:
                if (!listaB) {
                    listaB = inicializar_entregas(listaB);
                    printf("Lista B criada com sucesso.\n");
                } else {
                    printf("Lista B já foi criada.\n");
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
