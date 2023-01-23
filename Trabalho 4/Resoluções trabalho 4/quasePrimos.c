//utilizaremos essas bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//vamos utilizar semafaros neste exercicio
#include <semaphore.h>
#include <math.h>


//variaveis

int primeiraEntrada;
int segundaEntrada;
//primeiro semafaro
sem_t S1; 

//funcoes assinadas

void *QuasePrimoMaluco(void *arg);//agr lida com cada entrada


int main() {

    int T;//casos de teste
    void *retorno1, *retorno2;//retornos das funcoes associadas aos numeros desejados, sao do tipo void pelo fato da funcao ser do tipo void

    //lendo os casos de teste
    scanf("%d", &T);//entrada dos casos de teste
    
    //as threads t1 e t2
    pthread_t t1, t2;

    //validando que o numero é par --> pq a função dada tem problemas com impares
    if (T % 2 != 0) {//trata do caso da entrada T ser impar
        T--;// depois de reduzir T em 1 , ele se torna par e pode ser tratado pela funcao nas threads

        //lendo a primeira entrada
        scanf("%d", &primeiraEntrada);

        sem_init(&S1, 0, 1); //inicializando como 1 em referencia ao numero de threads utilizadas

        //variação da thread dada como  : "cria_thread(calcule_sequaseprimo_maluco(PARAMETRO_A))"
        pthread_create(&t1, NULL, QuasePrimoMaluco, (void *)&primeiraEntrada);
        //fazendo a thread do primeiro processo
        pthread_join(t1, &retorno1);
        //printando o primeiro retorno
        printf("%d\n", (int)retorno1);

        sem_destroy(&S1);
    }


    while (T > 0) {//loop que recebe e trata o restante dos casos

        //lendo a primeira entrada       
        scanf("%d", &primeiraEntrada);
        //lendo a 2 entrada
        scanf("%d", &segundaEntrada);

        T = T - 2;//reduz de dois em dois por tratar as estradas em paralelo, com o uso das threads de tid t1 e t2
        
        sem_init(&S1, 0, 2);//inicializado como 2 em referencia ao numero de de threads utilizadas

        //criando a threada dessa primeira entrada
        pthread_create(&t1, NULL, QuasePrimoMaluco, (void *)&primeiraEntrada);
        //criando thread dessa 2 entrada
        pthread_create(&t2, NULL, QuasePrimoMaluco, (void *)&segundaEntrada);

        //vamos inicializar o processo dessa função e retornar sua saida --> processo 1        
        pthread_join(t1, &retorno1);//valor de retorno da funcao associado ao status de saida do thread fornecida, no caso a resposta desejada
        printf("%d\n", (int)retorno1);//imprime o valor de retorno da funcao associado ao status de saida do thread fornecida

        //vamos inicializar o processo dessa função e retornar sua saida --> processo 2
        pthread_join(t2, &retorno2);//valor de retorno da funcao associado ao status de saida do thread fornecida, no caso a resposta desejada
        printf("%d\n", (int)retorno2);//imprime o valor de retorno da funcao associado ao status de saida do thread fornecida
        
        sem_destroy(&S1);
    }

    return 0;
}

//funcoes

void *QuasePrimoMaluco(void *arg) {
    	
    int *entrada = (int *)arg;
    int n = *entrada++;//incrementa a entrada, busca torna-la impar, afim de iniciar o processo de encontrar o maior nao primo
    int f;
    int quantidadeDivisores = 0;//numero do divisores inicializado com 0 para se evitar lixo de memoria

    if(n <= 508079)
        return 508079;

        //faremos o contrário do que fizemos acima
    if (n % 2 == 0)//verifica se o numero é par, caso sim incrementa mais um para torna-la impar
        n++; //agora é um numero impar
	
	sem_wait(&S1);

	
    while (quantidadeDivisores <= 10) {

        //variaveis para esse tipo de caso
        int quantidadeDivisores = 0;
        int i;

        //com o n tendo sido incrementado duas vezes ou uma mas verificado como impar, entao pula-se um elemento no laço
        //Alem disso com o uso do "floor(sqrt(n))", verifica se os divisores sao menores que o chao, menor numero inteiro associado, da raiz quadrada de n, a respectiva entrada
        for (i = 3, f = floor(sqrt(n)); i < f; i += 2)

            //foge dos casos de exemplo
            if (n % i == 0 && i < 11)//a divisao por i eh inteira, mas o numero eh menor que 10
                break;

            else if (n % i == 0 && i > 10)//a divisao por i eh inteira, e o divisor eh maior que 10, entao eh valido
                quantidadeDivisores++;
        
        //é um caso tratado nos exemplos
        if (quantidadeDivisores >= 10)//encontrou o numero correto
            return (void *)n;//retorna o numero correto como saida da funcao
        
        n+=2;
        //zerando novamente pois já usamos
        quantidadeDivisores = 0; //poderiamos dar um free também
    }

    sem_post(&S1);


}