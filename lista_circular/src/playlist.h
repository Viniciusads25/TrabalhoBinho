/*
 * playlist.h
 *
 *  Created on: 21 de out. de 2025
 *      Author: vn092
 */

#ifndef SRC_PLAYLIST_H_
#define SRC_PLAYLIST_H_

#define NOME_MAX 50

typedef struct Musica {
    char nome[NOME_MAX];
    char artista[NOME_MAX];
    int duracao; // em segundos
} Musica;

typedef struct No {
    Musica musica;
    struct No* prox;
} No;

typedef struct {
    No* fim; // aponta para o último nó
} Playlist;

// Funções
void inicializarPlaylist(Playlist* pl);
int playlistVazia(Playlist* pl);
void inserirMusica(Playlist* pl, Musica m);
int removerMusica(Playlist* pl, char* nome);
void listarMusicas(Playlist* pl);
Musica* proximaMusica(Playlist* pl);




#endif /* SRC_PLAYLIST_H_ */
