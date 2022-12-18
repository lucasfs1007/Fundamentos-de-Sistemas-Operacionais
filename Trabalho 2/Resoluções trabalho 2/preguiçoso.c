//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
//essa biblioteca vai trazer as funções : 
//SIGUSR1 --> eh para aproveitar mais um pouco
//SIGALRM --> na primeira vez deve imprimir "Ai que sono, quero dormir mais um pouco" e parar cpu
//SIGALRM --> na segunda vez deve imprimir "Ai que sono, quero dormir mais um pouco" e parar cpu
//SIGALRM --> na terceira vez deve imprimir "Os incomodados que se mudem, tchau" e encerrar.
#include <signal.h>

//utilizaremos essa variavel para contar quantas vezes a função apareceu.
int count;

//função para variar qual dos dois sinais vai aparecer e a quantidade
void trataSinal(int sig) {

    //frase do primeiro sinal é padrão, sempre será essa.
    if (sig == SIGUSR1) {
        printf("SIGUSR1 eh para aproveitar mais um pouco\n");
    }

    // frase do segundo sinal depende de quantas vezes aparecer
    if (sig == SIGALRM) {

        //validando se apareceu uma ou duas vezes --> msm frase
        if (count < 2) {
            printf("Ai que sono, quero dormir mais um pouco\n");
            count++;  //incrementamos apenas depois de printar, senão ele iria imprimir a frase da repetição acima
            // frase da terceira repetição
        }else {
            printf("Os incomodados que se mudem, tchau\n");
            exit(0); //finalizando
        }
    }
}

//na função main vamos chamar a função de tratamento de sinais e seus sinais
int main() {
    count = 0; //inicializando o count como zero
    //os procedimentos de tratamento para cada função
    signal(SIGALRM, trataSinal);
    signal(SIGUSR1, trataSinal);

    // deixando a cpu sem fazer nada com esse while
    while (1) {
    }
    return 0; //encerrando o programa
}