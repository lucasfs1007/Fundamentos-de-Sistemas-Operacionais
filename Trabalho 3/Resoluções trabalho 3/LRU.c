#include<stdio.h>
#include<stdlib.h>
 
 //utilizaremos essa função para achar as page fault
int busca(int tempo[], int n){
	int i;
    int menor = tempo[0];
    int posicao = 0;
 
	for(i = 1; i < n; ++i){
		if(tempo[i] < menor){
			menor = tempo[i];
			posicao = i;
		}
	}
	return posicao;
}

int main() {
    
    //variaveis
    int nenhumQuadro;
    int nenhumaPagina;
    int contador = 0;
    int tempo[1000];
    int flag1;
    int flag2;
    int i, j;
    int posicao;
    int faults = 0;
    
    //fazendo a leitura das duas primeiras linhas
	scanf("%d", &nenhumQuadro);
	scanf("%d", &nenhumaPagina);
	
    //alocando memória
	int *paginas = calloc(nenhumaPagina,sizeof(int));
	int *quadros = calloc(nenhumQuadro,sizeof(int));
	
    for(i = 0; i < nenhumaPagina; ++i) {
    	scanf("%d", &paginas[i]);
    }
    
	for(i = 0; i < nenhumQuadro; ++i) {
    	quadros[i] = -1;
    }
    
    for(i = 0; i < nenhumaPagina; ++i){
    	flag1 = flag2 = 0;
    	
    	for(j = 0; j < nenhumQuadro; ++j){
    		if(quadros[j] == paginas[i]) {
	    		contador++;
	    		tempo[j] = contador;
	   			flag1 = flag2 = 1;
	   			break;
   			}
    	}
    	
    	if(flag1 == 0){

			for(j = 0; j < nenhumQuadro; ++j){
	    		if(quadros[j] == -1){
	    			contador++;
	    			faults++;
	    			quadros[j] = paginas[i];
	    			tempo[j] = contador;
	    			flag2 = 1;
	    			break;
	    		}
    		}	
    	}
    	
    	if(flag2 == 0){
    		posicao = busca(tempo, nenhumQuadro);
    		contador++;
    		faults++;
    		quadros[posicao] = paginas[i];
    		tempo[posicao] = contador;
    	}
	}
	
	printf("%d\n", faults);
    
    free(paginas);
    free(quadros);
    return EXIT_SUCCESS;
}

