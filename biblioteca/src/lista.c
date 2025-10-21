/*
 * lista.c
 *
 *  Created on: 20 de out. de 2025
 *      Author: vn092
 */


#include <stdlib.h>
#include "lista.h"


Lista *criar_lista(){
	Lista *lista = malloc(sizeof *lista);

	if(!lista){
		printf("Erro de alocacao.\n");
		return NULL; // @suppress("Symbol is not resolved")
	}
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->tamanho = 0;

	return lista;
}

void destruir_lista(Lista *lista, void (*liberar_dado)(void*)){
	if(lista->inicio == NULL){
		printf("Erro. Lista vazia.\n");
		return;
	}
	No *atual = lista->inicio;
	while(atual != NULL){
		No *prox = atual->proximo;
		if(liberar_dado != NULL) liberar_dado(atual->dado);
		free(atual);
		atual = prox;

	}
	free(lista);

}

void *inserir_final(Lista *lista, void *dado){
	No *novo = malloc(sizeof *novo );
	if(novo == NULL){
		printf("Erro de alocacao.\n");
		return NULL;
	}
	novo->dado = dado;
	novo->proximo = NULL;
	novo->anterior = NULL;

	if (lista->fim != NULL){
		lista->fim->proximo = novo; //o atual fim aponta pra o novo nó

		novo->anterior = lista->fim; //o novo nó aponta para o antigo fim

		lista->fim = novo; //atualizo o fim da lista
	}else{
		lista->inicio = novo;
		lista->fim = novo;
	}

	lista->tamanho++;
}

void *inserir_inicio(Lista *lista, void *dado){
	No *novo = malloc(sizeof *novo);
	if(novo == NULL){
		printf("Erro de alocacao.\n");
		return; // @suppress("No return value")
	}
	novo->dado = dado;
	novo->anterior = NULL;
	novo->proximo = NULL;

	if(lista->inicio == NULL){
		lista->inicio = novo;
		lista->fim = novo;


	}else{
		lista->inicio->anterior = lista->inicio;
		lista->inicio = novo;
	}
	lista->tamanho ++;
}

void remover_no(Lista *lista, No *no){
	if(no == NULL){

	}
	if(no->anterior != NULL){

		//pego o no anterior do atual e atribuo a ele o proximo nó do atual
		//ex.: pego o anterior de 4 (3) e aponto para o proximo de 4 (5).
		//para no que nao e o primeiro da lista

		no->anterior->proximo = no->proximo;
	}else{
		//para remover o primeiro no
		lista->inicio = no->proximo;
	}
	if(no->proximo != NULL){
		//pego o no proximo do atual e atribuo a ele o no anterior ao atual
		//ex.: pego o proximo de 4 (5) e aponto para ele o no anterior de 4 (3).
		//para no que nao e o ultimo lista
		no->proximo->anterior = no->anterior;

	}else{
		//remover o ultimo

		lista->fim = no->anterior;
	}

	free(no);
	lista->tamanho--;
}
// percorre todos os elementos da lista e aplica a função passada (imprimir entrega)
void percorrer_lista(Lista *lista, void (*funcao)(void*)) {

    if (!lista || !funcao) return;

    No *atual = lista->inicio;
    while (atual != NULL) {
        funcao(atual->dado);
        atual = atual->proximo;
    }
}
void ordenar_lista(Lista *lista, int (*comparar)(void *, void *)){
	if(!lista || !lista->inicio) {
	printf("Erro. Endero de lista ou funcao invalido.\n");
	return;
	}
	int trocou;
	No *i;
	do {
		i = lista->inicio;
		trocou = 0;
		while(i->proximo != NULL){
			void *a =  i->dado;
			void *b =  i->proximo->dado;
			//ex.: pra facilitar, quanto menor o numero, maior a prioridade: a=10 b=4
			//atual: [a] -> [b] -> NULL
			//depois: [b] -> [a] -> NULL
			if(comparar(a, b) > 0){
				void *temp = i->dado; //variável temporaria para armazenar o dado do no atual

				i->dado = i->proximo->dado; //ex.: inicio recebe o endereco da proxima entrega [b]
											//b esta num nivel de prioridade mais importante e passa
				i->proximo->dado = temp;//o proximo aqui aponta para [a]
				trocou = 1;
			}
			i = i->proximo;
		}
	} while (trocou != 0);
}











