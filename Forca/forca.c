#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

void abertura () {
    printf("**********************************\n");
    printf("**********Jogo da Forca***********\n");
    printf("**********************************\n\n");
}

char password [TAMANHO_PALAVRA];
char chutes [26];
int chutesdados = 0;


void chuta () {
    char chute;
    scanf(" %c", &chute);

    chutes [chutesdados] = chute;
    (chutesdados)++;
}

int jachutou(char letra){
    int achou = 0;

    for(int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca() {
    for(int i = 0; i < strlen(password); i++) {

        int achou = jachutou(password[i]);

        if (achou) {
            printf("%c ", password[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void adicionapalavra() {
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
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

void escolhepalavra() {
    FILE* f;

    f = fopen("palavras.txt", "r");
    if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", password);
    }

    fclose(f);
}    

int enforcou () {
    int erros = 0;

    for (int i = 0; i < chutesdados; i++) {
        int existe = 0;

        for (int j = 0; j < strlen(password); j++) {
            if (chutes [i] == password[j]) {

                existe = 1;
                break;
            }
        }
        if (!existe) erros ++;

    }

    return erros >=5;
}

int acertou() {
    for(int i = 0; i < strlen(password); i++) {
        if(!jachutou(password[i])) {
            return 0;
        }
    }

    return 1;
}

int main () {

    escolhepalavra();
    abertura();


    do {

        desenhaforca ();
        chuta();

    } while (!acertou() && !enforcou());

    if (acertou()) {
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
    printf("        '-------'       \n");
    } else {
        printf("\nPoxa, voce foi enforcado!");
    printf("A palavra era **%s**\n\n", password);

    printf("    _______________            \n");
    printf("   /               \\          \n");
    printf("  /                 \\         \n");
    printf("//                   \\/\\     \n");
    printf("\\|   XXXX     XXXX   | /      \n");
    printf(" |   XXX       XXX   |         \n");
    printf(" |                   |         \n");
    printf(" \\__      XXX      __/        \n");
    printf("   |\\     XXX     /|          \n");
    printf("   | |           | |           \n");
    printf("   | I I I I I I I |           \n");
    printf("   |  I I I I I I  |           \n");
    printf("   \\_             _/          \n");
    printf("     \\_         _/            \n");
    printf("       \\_______/            \n\n");
    }

    adicionapalavra();
}

