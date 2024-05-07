// Matheus Dantas Santana 12221BCC009
// Vanessa Dias Ferreira 12221BCC017

#include "Arvore.h"
#include "Jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// https://www.programiz.com/dsa/graph-adjacency-list tad de grafo base

// https://www.xefer.com/maze-generator gerar labirintos

int menu() {
  int op;
  printf("0- Iniciar jogo\n");
  printf("1- Ranking por tempo\n");
  printf("2- Ranking por pontuacao\n");
  printf("3- Limpar historico\n");
  printf("4- Apagar pontuacao\n");
  printf("5- Sair\n");
  printf("Digite uma opcao: ");
  scanf("%d", &op);
  getchar();
  return op;
}

int main() {
  // menu, ranking, terminar areas e area central
  int n, m, tamanhoVetor = 0, opcao, confirmacao, pontuacao;
  char direcao, nome[10];
  Grafo *labirinto;
  double tempoPartida;
  infoPartida partida;
  Dicionario mapa;
  while (1) {
    pontuacao = 0;
    opcao = menu();
    switch (opcao) {
    case 0:
      system("clear");
      Inicializa(&mapa);   // inicializa o mapa
      carregarJogo(&mapa); // carrega os niveis no mapa
      printf("Digite seu nome de usuario: ");
      fgets(nome, 10, stdin);
      nome[strlen(nome)] = '\n'; // a linha de baixo da pau se nao achar nenhum \n
      *strchr(nome, 10) = '\0'; // substitui o primeiro \n (codigo ascii 10, se
                                // não da erro) que achar por \0
      system("clear");
      partida.tempo[0] =
          percursoPos(&mapa, &pontuacao, &partida); // inicia jogo
      partida.pontos = pontuacao;
      strcpy(partida.nome, nome);
      
      insereDados(partida);
      printf("Voce concluiu em %.2fs com %d pontos!\n", partida.tempo[0],
             partida.pontos);
      liberarNo(&mapa);
      break;
    case 1:
      system("clear");
      imprimirRanking('t');
      system("clear");
      break;
    case 2:
      system("clear");
      imprimirRanking('p');
      system("clear");
      break;
    case 3:
      system("clear");
      printf(
          "Tem certeza que deseja limpar o historico? [1 - sim | 2 - nao]: \n");
      scanf("%d", &confirmacao);
      getchar();
      if (confirmacao == 1) {
        limparRanking();
        printf("Ranking apagado\n");
        getchar();
      }
      system("clear");
      break;
    case 4:
      system("clear");
      printf("Digite o usuario a apagar: ");
      fgets(nome, 10, stdin);
      nome[strlen(nome)] =
          '\n'; // a linha de baixo da pau se nao achar nenhum \n
      *strchr(nome, 10) = '\0'; // substitui o primeiro \n (codigo ascii 10, se
                                // não da erro) que achar por \0
      if (removerUsuario(nome)) {
        printf("Usuario apagado com sucesso!\n");
        getchar();
      } else {
        printf("Usuario nao encontrado!\n");
        getchar();
      }
      system("clear");
      break;
    case 5:
      break;
    default:
      system("clear");
      printf("Digite uma opcao valida\n");
    }
    if (opcao == 5)
      break;
  }

  return 0;
}