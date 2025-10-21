/*
 * playlist.c
 *
 *  Created on: 21 de out. de 2025
 *      Author: vn092
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

// Inicializa a playlist
void inicializarPlaylist(Playlist* pl){
    pl->fim = NULL;
}

// Verifica se a playlist está vazia
int playlistVazia(Playlist* pl){
    return pl->fim == NULL;
}

// Insere música no final da playlist
void inserirMusica(Playlist* pl, Musica m){
    No* novo = (No*) malloc(sizeof(No));
    if(!novo) {
        printf("Erro de alocação!\n");
        return;
    }
    novo->musica = m;
    if(playlistVazia(pl)){
        novo->prox = novo;
        pl->fim = novo;
    } else {
        novo->prox = pl->fim->prox;
        pl->fim->prox = novo;
        pl->fim = novo;
    }
}

// Remove música pelo nome
int removerMusica(Playlist* pl, char* nome){
    if(playlistVazia(pl)) return 0;

    No *atual = pl->fim->prox;
    No *ant = pl->fim;
    do {
        if(strcmp(atual->musica.nome, nome) == 0){
            if(atual == pl->fim && atual->prox == pl->fim){ // único elemento
                pl->fim = NULL;
            } else {
                ant->prox = atual->prox;
                if(atual == pl->fim) pl->fim = ant;
            }
            free(atual);
            return 1; // sucesso
        }
        ant = atual;
        atual = atual->prox;
    } while(atual != pl->fim->prox);

    return 0; // não encontrado
}

// Lista todas as músicas
void listarMusicas(Playlist* pl){
    if(playlistVazia(pl)){
        printf("Playlist vazia.\n");
        return;
    }
    No* atual = pl->fim->prox;
    int i = 1;
    do{
        printf("%d. %s - %s (%d seg)\n", i, atual->musica.nome, atual->musica.artista, atual->musica.duracao);
        atual = atual->prox;
        i++;
    } while(atual != pl->fim->prox);
}

// Retorna a próxima música (mantém circularidade)
Musica* proximaMusica(Playlist* pl){
    if(playlistVazia(pl)) return NULL;
    pl->fim = pl->fim->prox; // move o ponteiro do fim para o próximo
    return &(pl->fim->musica);
}
