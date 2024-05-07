#include "Arvore.h"
#include "Jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// cria a arvore 
void Inicializa(Apontador *Dicionario) { *Dicionario = NULL; }

int Vazio(Apontador *Dicionario) { return (Dicionario == NULL); }

void Insere(Grafo *x, Apontador *p) {
  if ((*p) == NULL) {
    (*p) = (NoArvore *)malloc(sizeof(NoArvore));
    (*p)->labirinto = x;
    (*p)->Esq = NULL;
    (*p)->Dir = NULL;
    return;
  } else if ((*p)->Esq == NULL) {
    (*p)->Esq = (NoArvore *)malloc(sizeof(NoArvore));
    (*p)->Esq->labirinto = x;
    (*p)->Esq->Esq = NULL;
    (*p)->Esq->Dir = NULL;
    return;
  } else if ((*p)->Dir == NULL) {
    (*p)->Dir = (NoArvore *)malloc(sizeof(NoArvore));
    (*p)->Dir->labirinto = x;
    (*p)->Dir->Esq = NULL;
    (*p)->Dir->Dir = NULL;
    return;
  } else {
    if((*p)->Dir->Dir != NULL){
      Insere(x, &(*p)->Esq);
    }
    else if((*p)->Esq->Dir != NULL)
      Insere(x, &(*p)->Dir);
    else
      Insere(x, &(*p)->Esq);
  }
  return;
}

double percursoPos(Dicionario *q, int *pontuacao, infoPartida *partida) {
  double tempo_total = 0;
  double tempo_aux = 0;
  if (*q == NULL) {
    return 0;
  } else {
    tempo_total += percursoPos(&((*q)->Esq), pontuacao, partida);
    tempo_total += percursoPos(&((*q)->Dir), pontuacao, partida);
    tempo_aux = andarLabirinto((*q)->labirinto, (*q)->labirinto->m, (*q)->labirinto->n, 0, (*q)->labirinto->c, pontuacao);
    partida->tempo[(*q)->labirinto->area] = tempo_aux;
    (*q)->labirinto->tempo += tempo_aux;
  }
  return tempo_total + tempo_aux;
}

void liberarNo(Apontador *no){
    if(*no == NULL)
        return;
    liberarNo(&((*no)->Esq));
    liberarNo(&((*no)->Dir));
    liberarGrafo(((*no)->labirinto));
    free(*no);
    *no = NULL;
}