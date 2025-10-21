/*
 * entrega.c
 *
 *  Created on: 20 de out. de 2025
 *      Author: vn092
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrega.h"
#include "lista.h"

//extern Lista *lista_entregas = NULL; // lista privada dentro do modulo

//Essa lista serve como estrutura interna para organizar todas as funcoes dentro do modulo

/*
 * Essa parte do código é um construtor que serve para criar uma lista.
 * Esse construtor inicializa a classe em seu estado interno.
 *inicia a classe entregas
 */
Lista *inicializar_entregas(Lista *lista) {
    if (!lista){
        lista = criar_lista();
        return lista;
    }
}


/*
 * crio o objeto entrega.
 * Aqui eu apenas aloco a memória e inicializo os campos.
 * Não adiciono nada na minha lista.
 */
Entrega *criar_entrega( const char *origem, const char *destino,
                        double peso, double distancia, int prioridade, double custo, double tempo, Lista *lista){
	Entrega *entrega = malloc(sizeof(*entrega));
	if (entrega == NULL){
		printf("Erro de alocacao.\n");
		fflush(stdout);
		return 1;
	}
		entrega->id = lista->tamanho;

		strncpy(entrega->origem, origem, 31);
		entrega->origem[31] = '\0'; //garante que o ultimo elemento seja nulo

		strncpy(entrega->destino, destino, 31);
		entrega->destino[31] = '\0';

		entrega->peso = peso;

		entrega->distancia = distancia;
		entrega->prioridade = prioridade;

		entrega->custo = custo;

		entrega->tempo_estimado = tempo;

		return entrega;

}
/*
 * Destruidor
 * Destrói todo os elementos da lista e seus dados
 * garante que nao haja vazamento de dados
 */

void destruir_entrega(void *entrega) {
	Entrega *ent = (Entrega*) entrega;
    free(entrega);
}
/*
 * Exibe tidas as entregas da lista
 */
void mostrar_entrega(void *dado) {
    Entrega *ent = (Entrega*)dado;

    printf("ID %d: %s -> %s | %.1f km | R$ %.2f | %.2f h\n",

           &ent->id, ent->origem, ent->destino, ent->distancia, ent->custo, ent->tempo_estimado);
}
//Chamada de funcao remover_no() para remoção da entrega que usuário deseja.
//procura a entrega pelo id infomardo e exclui
void remover_entrega(Lista *lista, int id){
	if (lista == NULL){
		printf("Erro. Nao ha entregas.\n");
	}
	No *atual = lista->inicio;
	while(atual != NULL){
		Entrega *entrega = (Entrega*) atual->dado;
		if(entrega->id == id){
			remover_no(lista, atual);
			return;
		}

	}
}
/*
 * adiciono uma entrega que já existe dentro da minha lista
 */
void adicionar_entrega(Lista *lista, Entrega *entrega) {
    if (!lista || !entrega) return;
    inserir_final(lista, entrega);
}

void ordenar_prioridade_entrega(Lista *lista){
	if(!lista){
		printf("Lista entregas nao incializada.");
		return;
	}
	    ordenar_lista(lista, comparar_prioridade);
}

int comparar_prioridade(void *a, void *b){
	Entrega *entA = (Entrega*)a;
	Entrega *entB = (Entrega*)b;
	if(entA->prioridade < entB->prioridade) return -1;
	if(entA->prioridade > entB->prioridade) return 1;
	return 0;

}


