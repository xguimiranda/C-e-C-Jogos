#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

    char palavrasecreta[TAMANHOPALAVRA];
    char chutes[26];
    int chutesdados = 0;

void abertura (){
    printf("**************************\n");
    printf("***** Jogo da forca ******\n");
    printf("**************************\n\n");
}

void chuta(){
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);
    chutes[chutesdados] = chute;
    chutesdados++;
}

void desenha_forca(){

    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

  for(int i = 0; i < strlen(palavrasecreta); i++) {

    int achou = acertou_letra(palavrasecreta[i]);

        if (achou) {
        printf("%c ", palavrasecreta[i]);
        } else {
        printf("_ ");
        }
   }
    printf("\n");
}

void escolhe_palavra(){
  FILE* f;

  f= fopen("palavrasLC.txt", "r");
    if (f==0){
        printf("Desculpe! Banco de dados indisponivel\n\n");
        exit(1);
    }
  int qtddepalavras;
  fscanf(f, "%d", &qtddepalavras);

  srand(time(0));
  int randomico = rand() % qtddepalavras;

  for(int i=0; i <= randomico; i++){
    fscanf(f, "%s", palavrasecreta);
  }


  fclose(f);
}

void adicionapalavra() {
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novapalavra[TAMANHOPALAVRA];

        printf("Digite a nova palavra, em letras maiusculas: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras nao disponivel\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

int chuteserrados(){
int erros = 0;

    for (int i=0; i < chutesdados; i++){
        int existe = 0;
        for (int j=0; j < strlen(palavrasecreta); j++){
            if (chutes[i] == palavrasecreta[j]){
                existe=1;
                break;
            }
        }
    if (!existe) erros++;
    }
    return erros;
}

int enforcou(){
    return chuteserrados()>=5;
}

int ganhou(){

    for(int i=0; i < strlen(palavrasecreta); i++){
        if (!acertou_letra(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int acertou_letra(char letra){
    int achou = 0;
    for(int j = 0; j < chutesdados; j++) {
          if(chutes[j] == letra) {
          achou = 1;
          break;
            }
    }
        return achou;
}

int main() {

    escolhe_palavra();

    abertura();

    do {

        desenha_forca();
        chuta();

    } while (!ganhou() && !enforcou());

    if(ganhou()) {
        printf("\nParabens, voce ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

    } else {
        printf("\nPuxa, voce foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionapalavra();

}
