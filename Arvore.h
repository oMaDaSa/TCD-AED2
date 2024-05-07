#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include "Grafo.h"
#include "Ranking.h"

typedef struct NoArvore *Apontador;

typedef struct NoArvore {
  Grafo *labirinto;
  Apontador Esq, Dir;
} NoArvore;

typedef Apontador Dicionario;
void Inicializa(Apontador *Dicionario);

void Insere(Grafo *x, Apontador *p);

double percursoPos(Apontador *q, int *pontuacao, infoPartida *partida);

void liberarNo(Apontador *no);

#endif
