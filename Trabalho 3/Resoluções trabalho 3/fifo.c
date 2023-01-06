#include <stdio.h>
#include <stdlib.h>

//faremos incialmente uma função para procurar pelas páginas
int busca(int entrada,int *guardaDado, int auxiliar1){
    // caso não se encontrar páginas disponíveis
    int resultado = 1; //teremos page faults

    //criaremos um laço de repetição para verificar cada página se há ou não espaços
    for(int i=0; i<auxiliar1;i++){
        //caso a entrada for correspondente a uma página que caiba um dado
        if(entrada == guardaDado[i]){
            resultado=0; //não teremos page faults pois o dado foi acomodado em uma página
            return resultado;
        }
    }

    return resultado;
}

int main(){
    
    //variaveis --> inicializando com zero para garantir que não se tenha lixo de memória
    int auxiliar1=0;
    int auxiliar2=0;
    int entrada=0;
    int pageFault=0;
    int posicao=0;
    int encontra=0;

//lendo a quantidade de quadros disponíveis na Ram
    scanf("%d",&auxiliar1);
    //lendo a quantidade de referências por página
    scanf("%d",&auxiliar2);

    //caso houver páginas disponíveis vamos guardar o dado na posição do quadro disponível
    int guardaDado[auxiliar1];

    //vamos preenchendo o vetor de quadros disponíveis na RAM
    for(int i=0;i<auxiliar1;i++)
        guardaDado[i] = -1; //não vai nos interessar

    //faremos agora relacionado com os processos
    for(int i=0; i < auxiliar2;i++) {
        
        //lendo a entrada
        scanf("%d",&entrada);

        //encontra vai receber a função que procura por page faults
        encontra=busca(entrada,guardaDado, auxiliar1);
        
        //caso encontrarmos uma page fault
        if (encontra == 1) {
                //vamos guardar a posicação em que foi encontrada
                guardaDado[posicao] = entrada;
                //vamos pegar o resto da divisão para termos o mapeamento do endereço de memória
                posicao = (posicao + 1) % auxiliar1;
                pageFault++; //incrementamos a page fault
                encontra = 0; //zeramos a variavel
        }
    }

    printf("%d\n",pageFault); //printamos o número de page faults
    
    return 0; //encerramento do programa
}