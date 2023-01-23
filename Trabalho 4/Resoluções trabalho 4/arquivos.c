//utilizaremos apenas essas duas bibliotecas
#include <stdio.h>
#include <stdlib.h>

//função para compilar os arquivos 
int comparaArquivos(FILE *arquivo1, FILE *arquivo2){
    //variaveis auxiliares
    int c1;
    int c2;
    //fgtc serve para ler string em arquivos --> no caso estamos lendo toda a entrada desses dos arquivos
    while ((c1 = fgetc(arquivo1)) == (c2 = fgetc(arquivo2)) && (c1 != EOF) && (c2 != EOF)) {}
    //verificando se são iguais ou não
    if (c1 == c2) {
        return 1;
    } else {
        return 0;
    }
}

//sugestão de como deveria vir a main
int main(int argc, char **argv) {
    //passando por todo o conteudo de argc
    for(int i = 1; i < argc; i++) {
        //fopen --> abre arquivos em c
        FILE *arquivo1 = fopen(argv[i], "r"); //abrindo o arquivo
        for(int j = i+1; j < argc; j++){
            fseek(arquivo1, 0, SEEK_SET); // reiniciar o ponteiro do arquivo 1
            //printf("Compara %s com %s\n", argv[i], argv[j]);
            FILE *arquivo2 = fopen(argv[j], "r");
            //nos comparavamos os conteudos --> linha 13 a 17 nesses ifs
            int igual = comparaArquivos(arquivo1, arquivo2);
            //verificando se os arquivos são iguais
            if(igual){
               printf("%s %s iguais\n", argv[i], argv[j]);
               //nesse caso são diferentes
            }else{
                printf("%s %s diferentes\n", argv[i], argv[j]);
            }
            //fclose --> fecha os arquivos em c
            fclose(arquivo2); //fechando o arquivo 2
        }
        fclose(arquivo1); //fechando o arquivo 1
    }
    //encerrando o programa em linguagem c
    return 0;
}