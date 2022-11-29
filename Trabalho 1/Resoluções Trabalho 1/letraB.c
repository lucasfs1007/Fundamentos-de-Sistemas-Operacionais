// https://linux.die.net/man/3/dlsym --> fiz baseado nessa documentação
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h> //biblioteca que vamos consumir

int main(int argc, char const *argv[]) {
  
    int (*imprime) (void);
    int (*calcula) (int,int);
    int (*trigo) (double);

     void *handle = dlopen(argv[1],RTLD_NOW ); //RTLD_NOW é uma flag
     //verificando se há a função dentro da biblioteca
     if (!handle) { //não há a função aqui dentro
        printf("nao disponivel\n"); //frase solicitada no exercicio
        return 0; //encerrando progrma
     } else {
        imprime = dlsym(handle,"imprime"); //verificando na biblioteca se há algum "imprime"
        if (dlerror()) {
            printf("nao implementado\n");
        }else {
          int  write = (*imprime)();
          printf("%d\n",write);
        }
        calcula = dlsym(handle,"calcula"); //verificando na biblioteca se há algum "calcula"
        if (dlerror()) {
            printf("nao implementado\n");
        }else {
          int writeB = (*calcula)(atoi (argv[2]), atoi (argv[3])); //convertendo string para int
            printf("%d\n",writeB);
        }
        trigo = dlsym(handle,"trigo"); //verificando na biblioteca se há algum "trigo"
        if (dlerror()) {
            printf("nao implementado\n");
        }else {
          int writeC = (*trigo)(atof (argv[4])); //convertendo string para int
            printf("%d\n",writeC);
        }
     }
     dlclose(handle);
     return 0;
}