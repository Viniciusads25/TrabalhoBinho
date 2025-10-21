/*
 * main.c
 *
 *  Created on: 21 de out. de 2025
 *      Author: vn092
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

int main(){
    Playlist pl;
    inicializarPlaylist(&pl);
    int opcao;
    Musica m;

    do {
        printf("\n--- MENU PLAYLIST ---\n");
        printf("1. Inserir música\n");
        printf("2. Remover música\n");
        printf("3. Listar músicas\n");
        printf("4. Próxima música\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        fflush(stdout);
        scanf("%d", &opcao);
        getchar(); // remove \n do buffer

        switch(opcao){
            case 1:
                printf("Nome da música: ");
                fflush(stdout);
                fgets(m.nome, NOME_MAX, stdin);
                m.nome[strcspn(m.nome, "\n")] = 0; // remove \n

                printf("Artista: ");
                fflush(stdout);
                fgets(m.artista, NOME_MAX, stdin);
                m.artista[strcspn(m.artista, "\n")] = 0;

                printf("Duração (segundos): ");
                fflush(stdout);
                scanf("%d", &m.duracao);
                getchar();

                inserirMusica(&pl, m);
                printf("Música inserida!\n");
                fflush(stdout);
                break;

            case 2:
                printf("Nome da música a remover: ");
                fflush(stdout);
                char nome[NOME_MAX];
                fgets(nome, NOME_MAX, stdin);
                nome[strcspn(nome, "\n")] = 0;
                if(removerMusica(&pl, nome)) printf("Música removida!\n");
                else printf("Música não encontrada.\n");
                break;

            case 3:
                listarMusicas(&pl);
                break;

            case 4:
                m = *proximaMusica(&pl);
                if(pl.fim) printf("Tocando: %s - %s\n", m.nome, m.artista);
                else printf("Playlist vazia.\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}

