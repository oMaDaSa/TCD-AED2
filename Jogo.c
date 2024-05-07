#include "Jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Print Maze
void printarLabirintoCompleto(Grafo *grafo, int m, int n, int posJogador,
                              char c) {
  for (int j = 0; j < n; j++) // parede de cima
    if (j == 0)
      printf("%c   ", c);
    else
      printf("%c%c%c%c", c, c, c, c);
  printf("%c\n", c);

  int v = 0;
  for (int i = 0; i < m; i++) {   // imprimir todas as m linhas
    for (int j = 0; j < n; j++) { // linha de vertices
      if (j == 0)                 // parede da esquerda
        printf("%c", c);
      if (posJogador == v) // posicao atual do jogador
        printf(" X ");
      else
        printf(" . "); // vertice livre
      if (adjacente(grafo, v, v + 1) ||
          adjacente(grafo, v + 1,
                    v)) // verifica se é parede ou entrada pro lado
        printf(" ");
      else
        printf("%c", c);
      if (j == n - 1) // parede da direita
        printf("\n");
      v++;
    }
    v -= n; // volta n vertices para criar as paredes abaixo
    for (int j = 0; j < n; j++) { // linha de paredes/entradas
      if (i == m - 1) {           // parede de baixo
        if (j == n - 1) {
          printf("%c   %c", c, c);
        } else
          printf("%c%c%c%c", c, c, c, c);
      } else {
        if (j == 0) // parede da esquerda
          printf("%c", c);
        if (adjacente(grafo, v, v + n) ||
            adjacente(grafo, v + n,
                      v)) // verifica se é parede ou entrada pra baixo
          printf("   %c", c);
        else
          printf("%c%c%c%c", c, c, c, c);
        if (j == n - 1)
          printf("\n");
        v++;
      }
    }
  }
}

void printarLabirintoParcial(Grafo *grafo, int m, int n, int posJogador,
                             char c) {
  for (int j = 0; j < n; j++) { // parede de cima
    if (j == 0 && posJogador == 0)
      printf("%c   ", c);
    else
      printf("%c%c%c%c", c, c, c, c);
  }
  printf("%c\n", c);

  int v = 0;
  for (int i = 0; i < m; i++) {   // imprimir todas as m linhas
    for (int j = 0; j < n; j++) { // linha de vertices
      if (j == 0)                 // parede da esquerda
        printf("%c", c);
      if (posJogador == v) // posicao atual do jogador
        printf(" X ");
      else {
        if (adjacente(grafo, posJogador, v) || adjacente(grafo, v, posJogador))
          printf(" . "); // vertice livre
        else
          printf("%c%c%c", c, c, c); // nao enxerga vertice livre
      }

      if ((v == posJogador || v == posJogador - 1) &&
          (adjacente(grafo, v, v + 1) || adjacente(grafo, v + 1, v)) &&
          (posJogador < (i + 1) * n) &&
          (posJogador >= i * n)) // verifica se é parede ou entrada pro lado e
                                 // se o jogador esta próximo
        printf(" ");
      else
        printf("%c", c);
      if (j == n - 1) // parede da dirita
        printf("\n");
      v++;
    }
    v -= n; // volta n vertices para criar as paredes abaixo
    for (int j = 0; j < n; j++) { // linha de paredes/entradas
      if (i == m - 1) {           // parede de baixo
        if (j == 0)
          printf("%c", c);
        if (j == n - 1 && posJogador == m * n - 1)
          printf("%c   %c", c, c);
        else
          printf("%c%c%c%c", c, c, c, c);
      } else {
        if (j == 0) { // parede da esquerda
          printf("%c", c);
        }
        if ((adjacente(grafo, v, v + n) || adjacente(grafo, v + n, v)) &&
            (v + n == posJogador || v == posJogador))
          printf("   %c", c);
        else
          printf("%c%c%c%c", c, c, c, c);
        if (j == n - 1)
          printf("\n");
        v++;
      }
    }
  }
}

// verifica se o jogador pode andar naquela direção e o move se possível
void moverJogador(Grafo *labirinto, int m, int n, int *posJogador, char dir,
                  int *pontuacao) {
  int direcao = 0, aux;
  if (dir == 's' && adjacente(labirinto, *posJogador, *posJogador + n)) {
    direcao = n;
    aux = 2; // pra baixo na matriz de peso
  }

  else if (dir == 'd' && adjacente(labirinto, *posJogador, *posJogador + 1)) {
    direcao = 1;
    aux = 0; // pra direita na matriz de peso
  }

  else if (dir == 'w' && adjacente(labirinto, *posJogador, *posJogador - n)) {
    direcao = -n;
    aux = 3; // pra cima na matriz de peso
  }

  else if (dir == 'a' && adjacente(labirinto, *posJogador, *posJogador - 1)) {
    direcao = -1;
    aux = 1; // pra esquerda na matriz de peso
  }

  if (labirinto->area == 7) {
    *pontuacao += labirinto->pesos[*posJogador][aux][0];
    getchar();
    if (labirinto->pesos[*posJogador][aux][0] == 1) {
      labirinto->pesos[*posJogador][aux][0] = 0;
      
    }
  }
  *posJogador += direcao;
}

// jogando o labirinto atual
double andarLabirinto(Grafo *labirinto, int m, int n, int posJogador, char c,
                      int *pontuacao) {
  char direcao; // direcao que usuario escolhe
  time_t inicio, fim;
  inicio = clock(); // inicio do temporizador
  while (1) {
    if (labirinto->area == 7)
      printf("Pontuacao: %d\n", *pontuacao);
    printarLabirintoParcial(labirinto, m, n, posJogador,c); 
    printf("\ninput [wasd]: ");
    direcao = getchar();
    printf("\n");
    moverJogador(labirinto, m, n, &posJogador, direcao, pontuacao);
    system("clear");
    if (posJogador == (m * n) - 1) {
      // jogador chegou no ultimo vertice desse labirinto
      printf("Você conseguiu sair da area!\n");
      printarLabirintoCompleto(labirinto, m, n, posJogador, c);
      printf("\nAperte enter para continuar ");
      getchar();
      if(labirinto->area != 7)
        getchar();
      system("clear");
      break;
    }
    if (*pontuacao < 0 || listaAdjVazia(labirinto, posJogador) == 1) {
      // jogador caiu em uma sala sem saida ou nao tem mais pontos para continuar na area central
      printf("Tente novamente!\n");
      printarLabirintoParcial(labirinto, m, n, posJogador, c);
      posJogador = 0;
      *pontuacao = 0;
      printf("\nAperte enter para continuar ");
      getchar();
      if(labirinto->area != 7)
        getchar();
      system("clear");
      if(labirinto->area == 7)
        resetarPesos(labirinto);
    }
  }
  fim = clock();
  return (double)(fim - inicio) / (CLOCKS_PER_SEC / 1000);
}

void carregarLevel(Grafo *labirinto, int area, Dicionario *mapa) {
  int aux1, aux2, peso;
  char level[3], c;
  char fileName[30] = "Levels/Level";
  sprintf(level, "%d", area); // int pra string
  strcat(fileName, level);
  strcat(fileName, ".txt");
  FILE *file = fopen(fileName, "r");
  int m, n;
  fscanf(file, "%d x %d - %c\n", &m, &n, &c);

  if (area == 7) {
    labirinto = criarGrafo(m * n, m, n, c, area, 1);
    while (fscanf(file, "aresta %d, %d, %d\n", &aux1, &aux2, &peso) != EOF)
      adicionarArestaDupla(labirinto, aux1, aux2, peso);
  } else {
    labirinto = criarGrafo(m * n, m, n, c, area, 0);
    while (fscanf(file, "aresta %d, %d\n", &aux1, &aux2) != EOF)
      adicionarAresta(labirinto, aux1, aux2);
  }

  fclose(file);
  Insere(labirinto, mapa);
}

// carrega todos os niveis do arquivo texto na memoria, sendo que cada labirinto sera um grafo
void carregarJogo(Dicionario *mapa) {
  Grafo *labirinto;
  carregarLevel(labirinto, 7, mapa);
  //carregarLevel(labirinto, 3, mapa);
  //carregarLevel(labirinto, 6, mapa);
  //carregarLevel(labirinto, 1, mapa);
  //carregarLevel(labirinto, 2, mapa);
  //carregarLevel(labirinto, 4, mapa);
  //carregarLevel(labirinto, 5, mapa);
}