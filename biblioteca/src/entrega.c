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

    printf("ID %d:-  Prioridade: %d  %s -> %s | %.1f km | R$ %.2f | %.2f h\n",

           ent->id, ent->prioridade, ent->origem, ent->destino, ent->distancia, ent->custo, ent->tempo_estimado);
}
//Chamada de funcao remover_no() para remoção da entrega que usuário deseja.
//procura a entrega pelo id infomardo e exclui
void remover_entrega(Lista *lista, int id){
	if (lista == NULL || id < 0){
		printf("Erro. Nao ha entregas.\n");
		return;
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

int comparar_prioridade(void *a, void *b) {
    Entrega *entA = (Entrega*) a;
    Entrega *entB = (Entrega*) b;

    if (!entA || !entB) return 0; // proteção extra

    if (entA->prioridade < entB->prioridade) return -1;
    if (entA->prioridade > entB->prioridade) return 1;
    return 0;
}

void ordenar_prioridade_entrega(Lista *lista) {
    if (!lista || !lista->inicio) {
        printf("Lista de entregas não inicializada ou vazia.\n");
        return;
    }
    ordenar_lista(lista, comparar_prioridade); // sem parênteses!
}

void editar_entrega(Lista *lista, int id) {
    if (!lista || lista->tamanho == 0) {
        printf("Lista vazia.\n");
        return;
    }

    No *atual = lista->inicio;
    while (atual) {
        Entrega *ent = (Entrega*)atual->dado;
        if (ent->id == id) {
            printf("Editando entrega ID %d\n", id);

            // Editar origem
            printf("Origem atual: %s\n", ent->origem);
            ler_texto("Nova origem: ", ent->origem, 32);

            // Editar destino
            printf("Destino atual: %s\n", ent->destino);
            ler_texto("Novo destino: ", ent->destino, 32);

            // Editar peso
            printf("Peso atual: %.2f\n", ent->peso);
            ent->peso = ler_double_positivo("Novo peso: ");

            // Editar distância
            printf("Distância atual: %.2f\n", ent->distancia);
            ent->distancia = ler_double_positivo("Nova distância: ");

            // Editar prioridade
            printf("Prioridade atual: %d\n", ent->prioridade);
            ent->prioridade = ler_prioridade("Nova prioridade (1-3): ");

            // Editar custo
            printf("Custo atual: %.2f\n", ent->custo);
            ent->custo = ler_double_positivo("Novo custo: ");

            // Editar tempo estimado
            printf("Tempo estimado atual: %.2f\n", ent->tempo_estimado);
            ent->tempo_estimado = ler_double_positivo("Novo tempo estimado: ");

            printf("Entrega ID %d editada com sucesso!\n", id);
            return;
        }
        atual = atual->proximo;
    }

    printf("Entrega com ID %d não encontrada.\n", id);
}



