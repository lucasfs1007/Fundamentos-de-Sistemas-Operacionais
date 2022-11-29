#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {


    printf("%d\n",argc-1); //para desconsiderar o nome do programa.

    for (int i = 1; i<argc; i++) {
        printf("%s\n", argv[i]); //imprimindo cada elemento da string 
    }

    return 0;
}