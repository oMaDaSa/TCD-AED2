typedef struct infoPartida {
  char nome[10];
  float tempo[8];
  int pontos;
} infoPartida;

void imprimirRanking(char opcao);

void insereDados(infoPartida usuario);

int particiona(infoPartida V[], int inicio, int fim, char opcao);

void quickSort(infoPartida V[], int inicio, int fim, char opcao);

void insereVetor(infoPartida vetor[], int n, infoPartida usuario);

void limparRanking();

int removerUsuario(char *usuario_Nome);