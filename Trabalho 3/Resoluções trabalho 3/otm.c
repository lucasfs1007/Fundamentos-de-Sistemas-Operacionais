#include<stdio.h>
#include<stdlib.h>

 //utilizaremos essa função para achar as page fault
int busca (int tempo[], int n) {
//variaveis
  int i;
  int menor = tempo[0];
  int posicao = 0;

  for (i = 1; i < n; ++i) {

      if (tempo[i] < menor) {

	      menor= tempo[i];
	    posicao = i;
	    }
    }
  return posicao;
}

int main () {
//variaveis
  int nenhumQuadro;
  int nenhumaPagina;
  int flag1;
  int flag2;
  int flag3;
  int i, j,k;
  int posicao;
  int faults = 0;
  int tempo[1000];
  int maximo;

  //fazendo a leitura das duas primeiras linhas
  scanf ("%d", &nenhumQuadro);
  scanf ("%d", &nenhumaPagina);

//alocando memória
  int *paginas = calloc (nenhumaPagina, sizeof (int));
  int *quadros = calloc (nenhumQuadro, sizeof (int));

  for (i = 0; i < nenhumaPagina; ++i) {

      scanf ("%d", &paginas[i]);
    }

  for (i = 0; i < nenhumQuadro; ++i) {
      quadros[i] = -1;
    }


  for (i = 0; i < nenhumaPagina; ++i) {

        flag1 = flag2 = 0;
      for (j = 0; j < nenhumQuadro; ++j) {

		if (quadros[j] == paginas[i]) {

	      flag1 = flag2 = 1;
	      break;
	    }
	}
	    if (flag1 == 0) {

	    for (j = 0; j < nenhumQuadro; ++j) {

	      if(quadros[j] == -1) {

		    faults++;
		    quadros[j] = paginas[i];
		    flag2 = 1;
		    break;
		  }
		}
	}
    if(flag2 == 0) {

		flag3 = 0;

		for (j = 0;j < nenhumQuadro; ++j) {

	      tempo[j] = -1;

			for (k = i + 1; k < nenhumaPagina; ++k) {

				if (quadros[j] == paginas[k]) {
				  tempo[j] = k;
				  break;
				}
			}
		}
		for(j= 0;j < nenhumQuadro;++j) {
	      if (tempo[j] == -1) {

			  posicao = j;
			  flag3 = 1;
			  break;
			}
		}
		if (flag3 == 0) {

			maximo = tempo[0];
			posicao = 0;
			for (j = 1; j < nenhumQuadro; ++j) {

			  if (tempo[j] > maximo) {

				  maximo = tempo[j];
				  posicao = j;
				}
			}
		}
		  quadros[posicao] = paginas[i];
		  faults++;
		}
	}
  printf ("%d\n", faults);
  free (paginas);
  free (quadros);
  return EXIT_SUCCESS;
}

