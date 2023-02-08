//Bibliotecas que iremos utilizar
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
//permite trabalhar com tempo
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
//permite reportar e retornar erros
#include <errno.h>
#include <sys/types.h>



//funcoes

//pegamos o ponteiro de início e de final para termos o tempo
float getTempo(struct timeval *ini, struct timeval *fim);//recupera o tempo de execução dos processos

float getTempo(struct timeval *ini, struct timeval *fim) {
        return (fim->tv_sec - ini->tv_sec) + (fim->tv_usec - ini->tv_usec) / 1000000.0;//sec = tempo em segundos e usec = tempo em microsegundos
}

//main

int main(void) {

        //a Struct que utilizaremos para pegar esses tempos
        struct timeval inicio, fim, inicio_t, fim_t;

        //As duas primeiras linhas que devemos ler com seus respectivos tamanhos
        char path[50];
        char args[75];

        // Recupera a hora atual com maior precisão possivel
        gettimeofday(&inicio_t, NULL); //pegamos até os millisegundos
        // leremos as duas linhas, sendo primeira a path e a segunda os args
        while (scanf(" %s %s", path, args) == 2) {
                //pegando a hora atual
                gettimeofday(&inicio, NULL);
                //  este pid é um indentificador único para processos
                pid_t pid = fork(); //esse pid vai receber uma modificação do código fonte via fork
                //pid igual a 0 não poderá ser lido
                if (pid == 0) {
                        //função utilizada nas últimas listas
                        fclose(stdin);//fecha arquivo
                        //Função dada no enunciado, vamos ler as duas linhas
                        execl(path, path, args, NULL);//executa o arquivo
                        //Caso o programa não exista ou não possa a vir ser executado
                        printf("> Erro: %s\n", strerror(errno));
                        //limparemos o buffer de saída de fluxo de dados com a função fflush
                        fflush(stdout);
                        //sairemos dessas leituras
                        _exit(errno);//funciona como exit
                //Caso contrário vamos poder utilizar esses outros identificadores --> pid
                } else {
                        int retorno; //utilizaremos essa função para pegar o retorno do tempo 
                        //iremos esperar até termos o código de retorno
                        pid = wait(&retorno);
                        //chegamos no final e agora temos o parametro final pro tempo
                        gettimeofday(&fim, NULL);
                        // printando o tempo total e o código de retorno dele
                        printf("> Demorou %.1f segundos, retornou %d\n", getTempo(&inicio, &fim), WEXITSTATUS(retorno)); //WEXITSTATUS devolve o status de execução do processo filho
                }
                //limpando o buffer
                fflush(stdout);
        }
        //pegamos o tempo total agora
        gettimeofday(&fim_t, NULL); 
        //printando o tempo total
        printf(">> O tempo total foi de %.1f segundos\n", getTempo(&inicio_t, &fim_t));
        //encerrando o programa
        exit(0);
}


