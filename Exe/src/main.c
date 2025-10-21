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
void ler_linha(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

double ler_double(const char *mensagem) {
    char buffer[64];
    double valor;
    while (1) {
        printf("%s", mensagem);
        fflush(stdout);
        ler_linha(buffer, sizeof(buffer));
        if (sscanf(buffer, "%lf", &valor) == 1) break;
        printf("Entrada inválida. Tente novamente.\n");
    }
    return valor;
}

int ler_int(const char *mensagem) {
    char buffer[64];
    int valor;
    while (1) {
        printf("%s", mensagem);
        fflush(stdout);
        ler_linha(buffer, sizeof(buffer));
        if (sscanf(buffer, "%d", &valor) == 1) break;
        printf("Entrada inválida. Tente novamente.\n");
    }
    return valor;
}

// Funções de entrada de dados
void ler_texto(char *origem, char *destino) {
    printf("Informe a origem:\n");
    fflush(stdout);
    ler_linha(origem, 32);

    printf("Informe o destino:\n");
    fflush(stdout);
    ler_linha(destino, 32);
}

void ler_numeros(double *peso, double *distancia, int *prioridade, double *tempo, double *custo) {
    *peso = ler_double("Informe o peso da encomenda: ");
    *distancia = ler_double("Informe a distancia: ");
    *prioridade = ler_int("Informe a prioridade da encomenda: ");
    *custo = ler_double("Informe o custo da entrega: ");
    *tempo = ler_double("Informe o tempo de entrega: ");
}

int main() {
    Lista *lista = NULL;
    int opcao;
    char origem[32];
    char destino[32];
    double peso, distancia, custo, tempo;
    int prioridade;
    Entrega *nova = NULL;

    do {
        printf("\n#########################\n");
        printf("         MENU\n");
        printf("#########################\n");
        printf("1 - Inicializar entregas (criar lista)\n");
        printf("2 - Criar entrega\n");
        printf("3 - Adicionar entrega\n");
        printf("4 - Remover entrega\n");
        printf("5 - Imprimir entregas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        fflush(stdout);

        opcao = ler_int(""); // Lê opção de menu de forma segura

        switch (opcao) {
            case 1:
                if (!lista) {
                    lista = inicializar_entregas();
                    printf("Lista criada com sucesso.\n");
                } else {
                    printf("Lista já inicializada.\n");
                }
                break;
            case 2:
                if (!lista) {
                    printf("Crie a lista antes de adicionar entregas.\n");
                    break;
                }
                ler_texto(origem, destino);
                ler_numeros(&peso, &distancia, &prioridade, &tempo, &custo);

                nova = criar_entrega(origem, destino, peso, distancia, prioridade, custo, tempo, lista);
                if (nova) {
                    printf("Entrega criada com sucesso (ID: %d).\n", &nova->id);
                    adicionar_entrega(nova); // adiciona na lista
                } else {
                    printf("Erro ao criar entrega.\n");
                }
                break;
            case 3:
                printf("Funcionalidade de adicionar entrega já integrada no passo 2.\n");
                break;
            case 4:
                if (!lista || lista->tamanho == 0) {
                    printf("Lista vazia, não há entregas para remover.\n");
                    break;
                }
                {
                    int id_remover = ler_int("Informe o ID da entrega a ser removida: ");
                    remover_entrega(id_remover);
                    printf("Entrega removida, se o ID existir.\n");
                }
                break;
            case 5:
                if (!lista || lista->tamanho == 0) {
                    printf("Lista vazia.\n");
                } else {
                    percorrer_lista(lista, mostrar_entrega);
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

    return 0;
}
