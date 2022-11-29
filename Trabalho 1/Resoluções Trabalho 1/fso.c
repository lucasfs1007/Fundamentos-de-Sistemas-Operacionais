
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h> //biblioteca que vamos consumir

// https://linux.die.net/man/3/dlsym --> fiz baseado nessa documentação
int main(int argc, char const *argv[]) { //mesma estrutura do primeiro exercicio
    
    //iremos procurar essas 3 funções dentro da biblioteca
    int (*imprime) (void);
    int (*calcula) (int,int);
    int (*trigo) (double);

     void *global = dlopen(argv[1],RTLD_NOW ); //RTLD_NOW é uma flag que teremos de usar
     //verificando se há a função dentro da biblioteca
     if (!global) { //não há a função aqui dentro
        printf("nao disponivel\n"); //frase solicitada no exercicio
        return 0; //encerrando progrma
     } else {
        imprime = dlsym(global,"imprime"); //verificando na biblioteca se há algum "imprime"
        if (dlerror()) {
            printf("nao implementado\n");
        }else {
          int  a = (*imprime)();
          printf("%d\n",a);
        }
        calcula = dlsym(global,"calcula"); //verificando na biblioteca se há algum "calcula"
        if (dlerror()) {
            printf("nao implementado\n");
        }else {
          int B = (*calcula)(atoi (argv[2]), atoi (argv[3])); //convertendo string para int
            printf("%d\n",B);
        }
        trigo = dlsym(global,"trigo"); //verificando na biblioteca se há algum "trigo"
        if (dlerror()) {
            printf("nao implementado\n");
        }else {
          int C = (*trigo)(atof (argv[4])); //convertendo string para int
            printf("%d\n",C);
        }
     }
     dlclose(global);
     return 0;
}