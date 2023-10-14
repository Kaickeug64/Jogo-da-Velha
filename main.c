#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 3
int vez;
int numero_de_players;
char jogadores[2][30];

void jogadaPlayer(int *linha, int *coluna);
void jogadaMaquina(int *linha, int *coluna);
void registrarJogadores();
int checarVitoria(int tabuleiro[][DIM]);
int checarPosicao(int tabuleiro[][DIM],int linha , int coluna);
int menu(void);
void clear(void);
int jogar(int tabuleiro[][DIM]);
void zeraTabuleiro(int tabuleiro[][DIM]);
void exibeTabuleiro(int tabuleiro[][DIM]);
void jogada(int tabuleiro[][DIM]);

int main(void)
{
    int tabuleiro[DIM][DIM], continuar;
    int vitorias_jogador1 = 0;
    int vitorias_jogador2 = 0;
    int vitorias_IA = 0;

    int vitoriaRound = 0;
    do
    {
        vez=1;
        continuar = menu();
        numero_de_players = continuar;
        if(continuar == 1 || continuar == 2){
            registrarJogadores();
            vitoriaRound = jogar(tabuleiro);

          if (vitoriaRound == 1) 
            vitorias_jogador1++;
          else if (vitoriaRound == -1 || numero_de_players == 2)
              vitorias_jogador2++;
          else 
            vitorias_IA++;
        }
 
    }while(continuar != 0);
    printf("O jogador : %s ganhou %d vezes\nO jogador : %s ganhou %d vezes\nA maquina ganhou %d vezes",jogadores[0],vitorias_jogador1,jogadores[1],vitorias_jogador2,vitorias_IA);
    putchar('\n'); 
    system("pause");
}
 
int menu(void)
{
    int opcao;
 
        printf("\t\tNosso Primeiro Jogo -- Jogo da Velha\n");
        printf("\n1.\tJogar uma partida \n");
        printf("0.\tSair\n");
        printf("\nOpcao: ");
 
        scanf("%d", &opcao);
 
        switch(opcao)
        {
           case 1:
          printf("1.\t1 player\n");
          printf("\n2.\t2 players \n");   
          printf("\nOpcao: ");
          scanf("%d", &opcao);
           case 0:
                break;
           default:
                clear();
                printf("Opcao invalida. Tente de novo!\n");
        }
 
    return opcao;
}
void registrarJogadores(){
  clear();
  if (strlen(jogadores[0]) == 0 ){
    printf("Digite o nome do jogador 1 : ");
    scanf("%s",jogadores[0]);
  }
  if (numero_de_players == 2 && strlen(jogadores[1]) == 0){
    printf("Digite o nome do jogador 2 : ");
    scanf("%s",jogadores[1]);
  }
}
 
void clear(void)
{
    int count=0;
 
    while(count != 100)
    {
        putchar('\n');
        count++;
    }
}

int jogar(int tabuleiro[][DIM])
{
    int continua;
    int resultado;
    zeraTabuleiro(tabuleiro);
 
    do
    {
        clear();
        exibeTabuleiro(tabuleiro);
        jogada(tabuleiro);
        resultado = checarVitoria(tabuleiro);
 
    }while(resultado == 0);
  printf("\nVitoria !");
  exibeTabuleiro(tabuleiro);

  if (resultado == 1)
    printf("\nParábens player %s!\n",jogadores[0]);
  else if (resultado == -1 || numero_de_players == 1)
    printf("\nVitória da Maquina\n");
  else
    printf("\nParábens player %s!\n",jogadores[1]);
  
  return resultado;
}

void zeraTabuleiro(int tabuleiro[][DIM])
{
    int linha, coluna;
    for(linha = 0 ; linha < DIM ; linha++)
        for(coluna = 0 ; coluna < DIM ; coluna++)
            tabuleiro[linha][coluna] = 0;
}
 
void exibeTabuleiro(int tabuleiro[DIM][DIM])
{
    int linha, coluna;
    putchar('\n');
 
    for(linha = 0 ; linha < DIM ; linha++)
    {
        for(coluna = 0 ; coluna < DIM ; coluna++)
        {
            if(tabuleiro[linha][coluna] == 0)
                printf("    ");
            else
                if(tabuleiro[linha][coluna] == 1)
                    printf("  X ");
                else
                    printf("  O ");
 
            if(coluna != (DIM-1))
                printf("|");
        }
        putchar('\n');
    }
    putchar('\n');
}
 
void jogada(int tabuleiro[][DIM])
{
    int linha, coluna;
    vez++;
    printf("\n--> %s \n", jogadores[vez % 2]);
 
    do
    {
        if (vez % 2 == 0)
          jogadaPlayer(&linha, &coluna);
        else if (vez % 2 != 0 && numero_de_players == 2)
          jogadaPlayer(&linha, &coluna);
        else
          jogadaMaquina(&linha, &coluna);
        
    } while(checarPosicao(tabuleiro,linha,coluna) == 0);
    
    if(vez%2)
        tabuleiro[linha][coluna] = -1;
    else
        tabuleiro[linha][coluna] = 1;
}
void jogadaMaquina(int *linha, int *coluna){
  (*linha) = rand() % 3;
  (*coluna) = rand() % 3;
}
void jogadaPlayer(int *linha, int *coluna){
  printf("\nLinha: ");
  scanf("%d", linha);
  (*linha)--;

  printf("Coluna: ");
  scanf("%d", coluna);
  (*coluna)--;
}
int checarVitoria(int tabuleiro[][DIM]){
  //teste é variavel que recebe o valor abstrato de uma posição , se ele receber 3 ou -3 alguém ganhou
  int teste =0;

  // esse loop testa se ouvi uma vitoria nas na vertical
  for (int i = 0;i < DIM; i++){
    for (int j = 0;j < DIM; j++){
      teste += tabuleiro[i][j];
    }
    if (teste == 3)
        return 1;
      else if (teste == -3)
        return -1;
    teste = 0;
  }

  // esse loop testa se ouvi uma vitoria nas na horizontal
  for (int i = 0;i < DIM; i++){
    for (int j = 0;j < DIM; j++){
      teste += tabuleiro[j][i];
    }
    if (teste == 3)
        return 1;
      else if (teste == -3)
        return -1;
      teste = 0;
  }

  // testando se ouve uma vitória na diagonal principal
  for (int i = 0; i < 3; i++){
    teste += tabuleiro[i][i];
  }
  if (teste == 3)
    return 1;
   else if (teste == -3)
     return -1;
   teste = 0;

  // testando se ouve uma vitória na diagonal secundaria
  for (int i = 0; i < 3; i++){
    teste += tabuleiro[i][3-i-1];
  }
  if (teste == 3)
    return 1;
   else if (teste == -3)
     return -1;
   return 0;
}
int checarPosicao(int tabuleiro[][DIM],int linha , int coluna){
  if (linha > 2 || linha < 0 || coluna > 2 || coluna < 0){
    if (numero_de_players == 2 || vez % 2 == 0){
      printf("\nPosição Invalida !\n");
    }
    return 0;
  }
  if(tabuleiro[linha][coluna] == 0)
  return 1;
  if (numero_de_players == 2 || vez % 2 == 0){
    printf("Posição Ocupada!");
  }
  return 0;
}