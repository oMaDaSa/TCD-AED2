#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

#include "Arvore.h"

// Print Maze
void printarLabirintoParcial(Grafo *labirinto, int m, int n, int posJogador, char c);

void printarLabirintoCompleto(Grafo *labirinto, int m, int n, int posJogador, char c);

// verifica se o jogador pode andar naquela direção e o move se possível
void moverJogador(Grafo *labirinto, int m, int n, int *posJogador, char dir, int *pontuacao);

int verificaPontos(Grafo *labirinto, int m, int n, int posJogador, int *pontuacao);

//andar pelo labirinto
double andarLabirinto(Grafo *labirinto, int m, int n, int posJogador, char c, int *pontuacao);

//carregar fase do arquivo
void carregarLevel(Grafo *labirinto, int area, Dicionario *mapa);

// Print Maze
void printarLabirintoTotal(Grafo *grafo, int m, int n, int posJogador, char c);

void printarLabirintoParcial(Grafo *grafo, int m, int n, int posJogador, char c);

void carregarJogo(Dicionario *mapa);

#endif