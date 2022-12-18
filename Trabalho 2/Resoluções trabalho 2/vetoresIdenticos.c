//Vamos ter de ler dois conjuntos de números e saber se serão iguais ou não.

//bibliotecas
#include <stdio.h>
#include <stdlib.h>
//biblioteca de onde vem as threads --> ordem de execução das coisas
#include <pthread.h>

//variaveis
int tam; //abriremos o tamanho necessario com malloc 

// validando se é menor
#define LESS(A, B) (A < B) //usaremos esse formato dentro de less para ver se o primeiro é menor

//Troca
#define EXCH(A, B) \
    {              \ 
        int t = B; \
        B = A;     \
        A = t;     \
    } //usaremos EXCH para trocar

 //caso B seja menor que A iremos troca-los
#define CMPEXCH(A, B)   \
    {                   \
        if (LESS(B, A)) \
            EXCH(A, B); \
    }

// teremos de fazer uma ordenacao destes elementos.
//primeiramente iremos fazer uma separação do vetor e vindo ordenando ele a cada posição
int separa(int *v, int l, int r) {

    int c = v[r]; // posição base para se iniciar a ordenação
    int t, j = l;

    for (int k = l; k < r; ++k)
        if (v[k] <= c) {
            t = v[j], v[j] = v[k], v[k] = t;
            ++j;
        }

    t = v[j], v[j] = v[r], v[r] = t;
    return j;
}

//Faremos a ordenação pelo algoritmo de quickSort
void quickSort(int *v, int l, int r) {
    if (r <= l)
        return;

    CMPEXCH(v[(l + r) / 2], v[r]);
    CMPEXCH(v[l], v[(l + r) / 2]);
    CMPEXCH(v[r], v[(l + r) / 2]);

    int j = separa(v, l, r);
    quickSort(v, l, j - 1);
    quickSort(v, j + 1, r);
}

// fazendo a ordenação do vetor
void *ordena(void *args) {
    quickSort((int *)args, 0, tam - 1);
    return;
}

int main() {

    //pegando o endereço dos dois vetores para se iniciar o processo de threads
    int *v1, *v2;

    //ao comparar as saidas a flag definira a frase a se aparecer
    int flag = 0, saida;
    //definirei a ordem dos processos por aqui
    pthread_t t1, t2;
    //recebendo o tamanho
    saida = scanf(" %d", &tam);

    //alocando memoria suficente para os dois vetores
    v1 = malloc(sizeof(int) * tam);
    v2 = malloc(sizeof(int) * tam);

    //prenchendo o primeiro vetor com o dado tamanho de entrada
    for (int i = 0; i < tam; i++)
        saida = scanf(" %d", &v1[i]);

    //preenchendo o segundo vetor com o seu tamanho de entrada
    for (int i = 0; i < tam; i++)
        saida = scanf(" %d", &v2[i]);

    //ordenando os dois vetores --> garantindo que esse seja o processo seguinte da thread
    saida = pthread_create(&t1, NULL, ordena, (void *)v1);
    saida = pthread_create(&t2, NULL, ordena, (void *)v2);

//irei zerar as threads para poder se trabalhar com outro processo
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

//caso após ordenados os vetores não sejam iguais
    for (int i = 0; i < tam; i++) {
        if (v1[i] != v2[i]) {
            flag = 1;
            break;
        }
    }

    //caso os vetores ordenados sejam iguais recebem a flag 0
    if (flag == 0) {

        printf("Mesmos elementos\n");
    
    //situação da flag 1
    } else {

        printf("Diferentes\n");
    }

    //encerramento do programa
    return 0;
}
