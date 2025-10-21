/*
 * lista.h
 *
 *  Created on: 20 de out. de 2025
 *      Author: vn092
 */

#ifndef INCLUDES_LISTA_H_
#define INCLUDES_LISTA_H_


typedef struct No {
    void *dado;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct Lista {
    No *inicio;
    No *fim;
    int tamanho;
} Lista;

// Funções básicas
Lista *criar_lista();

void destruir_lista(Lista *lista, void (*liberar_dado)(void*));

void *inserir_no_final(Lista *lista, void *dado);

void *inserir_no_inicio(Lista *lista, void *dado);

void remover_no(Lista *lista, No *no);

void percorrer_lista(Lista *lista, void (*func)(void*));


#endif /* INCLUDES_LISTA_H_ */
