#include "Grafo.h"
#include <stdio.h>
#include <stdlib.h>

// Create a node
No *criarNo(int v) {
  No *novoNo = (No *)malloc(sizeof(No));
  novoNo->vertice = v;
  novoNo->prox = NULL;
  return novoNo;
}

// criar grafo
Grafo *criarGrafo(int numVertices, int m, int n, char c, int area, int ehPonderado) {
  Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
  grafo->numVertices = m * n;
  grafo->m = m;
  grafo->n = n;
  grafo->c = c;
  grafo->area = area;
  grafo->tempo = 0;

  grafo->listaAdj = (No **)malloc(numVertices * sizeof(No *));
  if (grafo->area == 7) {
    grafo->pesos = (int ***)malloc(grafo->numVertices * sizeof(int **));
    for (int i = 0; i < grafo->numVertices; i++) {
      grafo->pesos[i] = (int **)malloc(4 * sizeof(int *));
      for (int j = 0; j < 4; j++) {
        grafo->pesos[i][j] = (int *)calloc(2, sizeof(int));
      }
    }
  }
  for (int i = 0; i < numVertices; i++)
    grafo->listaAdj[i] = NULL;
  return grafo;
}

void liberarGrafo(Grafo *grafo) {
  if (grafo == NULL) {
    return;
  }
  for (int i = 0; i < grafo->numVertices; i++) {
    No *atual = grafo->listaAdj[i];
    while (atual != NULL) {
      No *temp = atual;
      atual = atual->prox;
      free(temp);
    }
  }
  free(grafo->listaAdj);
  if (grafo->area == 7) {
    free(grafo->pesos);
  }
  free(grafo);
}

// adiciona aresta
void adicionarAresta(Grafo *grafo, int s, int d) {
  // aresta de s para d
  No *novoNo = criarNo(d);
  novoNo->prox = grafo->listaAdj[s];
  grafo->listaAdj[s] = novoNo;
}

// adiciona aresta bidirecional
void adicionarArestaDupla(Grafo *grafo, int s, int d, int p) {
  // aresta de s para d
  No *novoNo = criarNo(d);
  novoNo->prox = grafo->listaAdj[s];
  grafo->listaAdj[s] = novoNo;

  // aresta de s para d
  novoNo = criarNo(s);
  novoNo->prox = grafo->listaAdj[d];
  grafo->listaAdj[d] = novoNo;

  if (s < 0 || s >= grafo->numVertices || d < 0 || d >= grafo->numVertices) {
    return;
  } else {
    if (s + 1 == d) {
      grafo->pesos[s][0][0] = p;  // pra direita
      grafo->pesos[d][1][0] = -1; // pra esquerda
      grafo->pesos[s][0][1] = p;  // pra direita
      grafo->pesos[d][1][1] = -1; // pra esquerda
    } else if (s - 1 == d) {
      grafo->pesos[s][1][0] = p;  // pra esquerda
      grafo->pesos[d][0][0] = -1; // pra direita
      grafo->pesos[s][1][1] = p;  // pra esquerda
      grafo->pesos[d][0][1] = -1; // pra direita
    } else if (s + grafo->n == d) {
      grafo->pesos[s][2][0] = p;  // pra baixo
      grafo->pesos[d][3][0] = -1; // pra cima
      grafo->pesos[s][2][1] = p;  // pra baixo
      grafo->pesos[d][3][1] = -1; // pra cima
    } else if (s - grafo->n == d) {
      grafo->pesos[s][3][0] = p;  // pra cima
      grafo->pesos[d][2][0] = -1; // pra baixo
      grafo->pesos[s][3][1] = p;  // pra cima
      grafo->pesos[d][2][1] = -1; // pra baixo
    }
  }
}

void resetarPesos(Grafo *grafo) {
  int s, d, p;
  FILE *file = fopen("Levels/Level7.txt", "r");
  fscanf(file, "7 x 7 - *\n");
  while (fscanf(file, "aresta %d, %d, %d\n", &s, &d, &p) != EOF) {

    if (s < 0 || s >= grafo->numVertices || d < 0 || d >= grafo->numVertices) {
      return;
    } else {
      if (s + 1 == d) {
        grafo->pesos[s][0][0] = grafo->pesos[s][0][1];
        grafo->pesos[d][1][0] = grafo->pesos[d][1][1];
      } else if (s - 1 == d) {
        grafo->pesos[s][1][0] = grafo->pesos[s][1][1];
        grafo->pesos[d][0][0] = grafo->pesos[d][0][1];
      } else if (s + grafo->n == d) {
        grafo->pesos[s][2][0] = grafo->pesos[s][2][1];
        grafo->pesos[d][3][0] = grafo->pesos[d][3][1];
      } else if (s - grafo->n == d) {
        grafo->pesos[s][3][0] = grafo->pesos[s][3][1];
        grafo->pesos[d][2][0] = grafo->pesos[d][2][1];
      }
    }
  }
}

// verifica se node2 está na lista de adjacencia de node1
int adjacente(Grafo *grafo, int no1, int no2) {
  if (no1 >= grafo->numVertices || no2 >= grafo->numVertices)
    return 0;
  No *temp = grafo->listaAdj[no1];
  while (temp) {
    if (no2 == temp->vertice)
      return 1;
    else
      temp = temp->prox;
  }
  return 0;
}

int listaAdjVazia(Grafo *grafo, int no1) {
  if (grafo->listaAdj[no1] == NULL) {
    return 1;
  } else
    return 0;
}
