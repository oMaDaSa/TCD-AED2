#include "Ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimirRanking(char opcao) {
  infoPartida usuario, *vetorUsuario = NULL;
  char nome[10];
  int pontuacao, tamanho = 0;
  float tempo[8];
  // fscanf(file, "Nome: %[^;]; Tempo: %f; Pontos: %d;\n"
  FILE *file = fopen("Ranking.txt", "r");
  while (fscanf(file,
                "Nome: %[^;]; Tempo Total: %f; Pontos: %d; T1: %f; T2: %f; T3: "
                "%f; T4: %f; T5: %f; T6: %f; TCentral: %f;\n",
                nome, &tempo[0], &pontuacao, &tempo[1], &tempo[2], &tempo[3],
                &tempo[4], &tempo[5], &tempo[6], &tempo[7]) != EOF) {
    vetorUsuario = (infoPartida *)realloc(vetorUsuario,
                                          (tamanho + 1) * sizeof(infoPartida));
    nome[strlen(nome)] = '\0';
    strcpy(usuario.nome, nome);
    for(int i = 0; i < 8; i++) usuario.tempo[i] = tempo[i];
    usuario.pontos = pontuacao;
    vetorUsuario[tamanho] = usuario;
    tamanho++;
  }

  quickSort(vetorUsuario, 0, tamanho - 1, opcao);
  if (tamanho > 10)
    tamanho = 10;
  if(opcao == 'p') printf("Ranking por pontos:\n");
  else printf("Ranking por tempo:\n");
  for (int i = 0; i < tamanho; i++) {
    printf("%s\n - Pontos: %d\n - Tempo Final: %.2fs\n - Tempo area 1: %.2fs\n - Tempo area 2: %.2fs\n - Tempo area 3: %.2fs\n - Tempo area 4: %.2fs\n - Tempo area 5: %.2fs\n - Tempo area 6: %.2fs\n - Tempo area central: %.2fs\n\n", vetorUsuario[i].nome, vetorUsuario[i].pontos, 
           vetorUsuario[i].tempo[0], vetorUsuario[i].tempo[1], vetorUsuario[i].tempo[2], vetorUsuario[i].tempo[3], vetorUsuario[i].tempo[4], vetorUsuario[i].tempo[5], vetorUsuario[i].tempo[6], vetorUsuario[i].tempo[7]);
  }
  printf("Aperte enter para sair ");
  getchar();
  fclose(file);
}

void insereDados(infoPartida usuario) {
  FILE *file = fopen("Ranking.txt", "a");
  fprintf(file,
          "Nome: %s; Tempo Total: %.2f; Pontos: %d; T1: %.2f; T2: %.2f; T3: "
          "%.2f; T4: %.2f; T5: %.2f; T6: %.2f; TCentral: %.2f;\n",
          usuario.nome, usuario.tempo[0], usuario.pontos, usuario.tempo[1],
          usuario.tempo[2], usuario.tempo[3], usuario.tempo[4],
          usuario.tempo[5], usuario.tempo[6], usuario.tempo[7]);
  fclose(file);
}

int particiona(infoPartida V[], int inicio, int fim, char opcao) {
  int esq, dir;
  infoPartida pivo, aux;
  esq = inicio;
  dir = fim;
  pivo = V[inicio];
  while (esq < dir) {
    if (opcao == 'p') {
      while (esq <= fim && V[esq].pontos >= pivo.pontos)
        esq++;

      while (dir >= 0 && V[dir].pontos < pivo.pontos)
        dir--;
    }
    if (opcao == 't') {
      while (esq <= fim && V[esq].tempo[0] <= pivo.tempo[0])
        esq++;

      while (dir >= 0 && V[dir].tempo[0] > pivo.tempo[0])
        dir--;
    }
    if (esq < dir) {
      aux = V[esq];
      V[esq] = V[dir];
      V[dir] = aux;
    }
  }
  V[inicio] = V[dir];
  V[dir] = pivo;
  return dir;
}

void quickSort(infoPartida V[], int inicio, int fim, char opcao) {
  int pivo;
  if (fim > inicio) {
    pivo = particiona(V, inicio, fim, opcao);
    quickSort(V, inicio, pivo - 1, opcao);
    quickSort(V, pivo + 1, fim, opcao);
  }
}

void limparRanking() { FILE *file = fopen("Ranking.txt", "w"); }

int removerUsuario(char *usuario_Nome) {
  infoPartida usuario, *vetorUsuario = NULL;
  char nome[10];
  int pontuacao, tamanho = 0, verifica = 0;
  float tempo[8];
  FILE *file = fopen("Ranking.txt", "r");
  while (fscanf(file,
                "Nome: %[^;]; Tempo Total: %f; Pontos: %d; T1: %f; T2: %f; T3: "
                "%f; T4: %f; T5: %f; T6: %f; TCentral: %f;\n",
                nome, &tempo[0], &pontuacao, &tempo[1], &tempo[2], &tempo[3],
                &tempo[4], &tempo[5], &tempo[6], &tempo[7]) != EOF) {
    vetorUsuario = (infoPartida *)realloc(vetorUsuario,
                                          (tamanho + 1) * sizeof(infoPartida));
    nome[strlen(nome)] = '\0';
    strcpy(usuario.nome, nome);
    for(int i = 0; i < 8; i++) usuario.tempo[i] = tempo[i];
    usuario.pontos = pontuacao;
    vetorUsuario[tamanho] = usuario;
    tamanho++;
  }

  file = fopen("Ranking.txt", "w");
  for (int i = 0; i < tamanho; i++) {
    if (strcmp(vetorUsuario[i].nome, usuario_Nome) != 0) {
      insereDados(vetorUsuario[i]);
    } else {
      verifica = 1;
    }
  }
  return verifica;
}