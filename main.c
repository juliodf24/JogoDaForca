#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"


//variaveis globais
char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;

void abertura(){
    printf("++++++++++ forca ++++++++++++++\n\n");
}

int jaChutou(char letra){
    int achou = 0;
    for(int j = 0; j< chutesDados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

void adicionaPalavra(){
    char quer;

    printf("Você deseja adicionar uma nova palavra? (S/N)");
    scanf(" %c", &quer);

    if(quer == 'S'){
        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? ");
        scanf("%s", novapalavra);

        FILE* f;
        f = fopen("palavras.txt", "r+"); // leitura E ESCRITA
        if(!f){
            printf("Desculpe, banco de dados não disponivel\n\n");
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


void chuta(){
    char chute;
    scanf(" %c", &chute);
    chutes[chutesDados] = chute;
    chutesDados++;
}
void desenharForca(){
    for(int i= 0; i< strlen(palavraSecreta); i++){
        int achou = jaChutou(palavraSecreta[i]);
        if(achou){
            printf("%c", palavraSecreta[i]);
        } else{
            printf("_ ");
        }
    }
    printf("\n");
}
void escolhePalavra(){
    FILE* f;
    f = fopen("palavras.txt", "r"); // abrir só para leitura
    if(!f){
        printf("Desculpe, banco de dados não disponivel\n\n");
        exit(1);
    }

    int qtdDePalavras;
    fscanf(f, "%d", &qtdDePalavras);

    srand(time(0));
    int randomico = rand()%qtdDePalavras;
    for(int i =0; i<=randomico; i++){
        fscanf(f, "%s", palavraSecreta);
    }

    fclose(f);
}

int acertou(){
    for(int i = 0; i< strlen(palavraSecreta); i++){
        if(!jaChutou(palavraSecreta[i])){
            return 0;
        }
    }
    return 1;
}

int enforcou(){
    int erros = 0;

    for(int i=0; i < chutesDados; i++ ){
        int existe = 0;
        for(int j=0; j<strlen(palavraSecreta); j++){
            if(chutes[i] == palavraSecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros ++;
    }
    return erros >= 5;
}

int main(){

    // adicionaPalavra();
    escolhePalavra();
    abertura();
    do{
        desenharForca();
        chuta(chutes);

    } while (!acertou() && !enforcou());
    if(acertou()){
        printf("Parabens, Voce ganhou");
    } else {
        printf("Puxa, você perdeu!\n");
        printf("A palavra era **%s**\n\n", palavraSecreta);
    }

    return 0;
}