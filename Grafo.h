#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct no {
  int vertice;
  struct no *prox;
} No;

typedef struct grafo {
  int numVertices;
  int m, n, area;
  char c;
  struct no **listaAdj;
  int ***pesos;
  float tempo;
} Grafo;

// criar nó
No *criarNo(int v);

// criar grafo
Grafo *criarGrafo(int numVertices, int m, int n, char c, int area, int ehPonderado);

// liberar memoria do grafo
void liberarGrafo(Grafo *grafo);

// resetar pesos da matriz
void resetarPesos(Grafo *grafo);

// adiciona aresta
void adicionarAresta(Grafo *grafo, int s, int d);

//adicionar aresta bidirecional
void adicionarArestaDupla(Grafo *grafo, int s, int d, int p);

// verifica se node2 está na lista de adjacencia de node1
int adjacente(Grafo *grafo, int no1, int no2);


int listaAdjVazia(Grafo *grafo, int no1);

#endif