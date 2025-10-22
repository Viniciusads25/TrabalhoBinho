/*
 * entrega.h
 *
 *  Created on: 20 de out. de 2025
 *      Author: vn092
 */

#ifndef INCLUDES_ENTREGA_H_
#define INCLUDES_ENTREGA_H_
#include "lista.h"
/*
 * Definicao de cabecalho da biblioteca de entregas da funcao
 *
 * Permite adicionar novas entregas
 *
 * Permite Excluir entregas
 *
 * Permite exibir entregas
 *
 * Esse componente essencial do projeto permite que as entregas possam ser estruturadas por seus atributos
   Facilitando sua submissao a lista de entregas com o fito de otimizar os processos logísticos organização
 */

typedef struct {
    int id;
    char origem[32];
    char destino[32];
    double peso;           // kg
    double distancia;      // km
    int prioridade;
    double custo;          // R$
    double tempo_estimado; // horas
} Entrega;

// Funções para criar, destruir e mostrar entrega

Lista *inicializar_entregas();

void entrada_entrega(char origem[32], char destino[32], double peso,
		double distancia, int prioridade, double custo, double tempo);

Entrega *criar_entrega( const char *origem, const char *destino,
                        double peso, double distancia, int prioridade, double custo, double tempo, Lista *lista);
void destruir_entrega(void *entrega); // compatível com lista

void remover_entrega(Lista *lista, int id);

void mostrar_entrega(void *entrega);

void adicionar_entrega(Lista *lista, Entrega *entrega);

void ordenar_prioridade_entrega(Lista *lista);

void editar_entrega(const char *origem, const char *destino,
        double peso, double distancia, int prioridade, double custo, double tempo, Lista *lista,  int id);



#endif /* INCLUDES_ENTREGA_H_ */
