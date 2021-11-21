#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

struct _TPonto_ {
    
float x;
float y;

};

typedef struct _TPonto_ TPonto;

void pi_MonteCarlo (int semente, int dardos, FILE * arquivo);
void transfereDeArquivoParaVetor (FILE * arquivo, TPonto v[], int tamanho);
float distancia (TPonto p);
int dardosNoQuartoDeCirculo (TPonto v[], int tamanho, float raio);
void criaLog (FILE * arquivo, TPonto v[], int pontosNoAlvo, int totalDePontos);

main (){
    
FILE * arquivo;
TPonto * pontos;

int totalDeDardos, dardosNoAlvo, semente;

printf ("QUANTIDADE DE DARDOS: ");

scanf ("%d", &totalDeDardos);
 
pontos = (TPonto *) malloc (sizeof (TPonto[totalDeDardos]));

semente = time (NULL);

pi_MonteCarlo (semente, totalDeDardos, arquivo);


transfereDeArquivoParaVetor (arquivo, pontos, totalDeDardos);

dardosNoAlvo = dardosNoQuartoDeCirculo (pontos, totalDeDardos, 1.0);

criaLog (arquivo, pontos, dardosNoAlvo, totalDeDardos);

free (pontos);

}

//Gera pontos em uma area correspondente a um quadrado de lado 1
//com vertices nos pontos (0,0) , (0,1) , (1,1) e (1,0).
//Grava esses pontos em um arquivo binario.
void pi_MonteCarlo (int semente, int dardos, FILE * arquivo){
      
    TPonto p;
    int i;

//Abre um arquivo binario para escrita.
    arquivo = fopen ("pontos.dat", "wb+");
  
//Estabelece uma raiz para a geracao de numeros aleatorios.
    srand (semente);
  
    for (i = 0; i < dardos; i++){

//Sorteia valores de 0 a 1 para x e para y de um ponto.
	    p.x = 1.0 * rand () / RAND_MAX;
        p.y = 1.0 * rand () / RAND_MAX;
//Escreve um registro do tipo TPonto no aqruivo.
	    fwrite (&p, sizeof (TPonto), 1, arquivo);
}
  
//Fecha o arquivo.
    fclose (arquivo);
}

void transfereDeArquivoParaVetor (FILE * arquivo, TPonto v[], int tamanho){
	int i;
	TPonto vet;
	
	arquivo = fopen("pontos.dat", "rb+");
	
	for(i=0; i<tamanho; i++){
    fread(&vet, sizeof (TPonto), 1, arquivo);
    v[i].x = vet.x;
    v[i].y = vet.y;
	}
	fclose(arquivo);

}



float distancia (TPonto p){
	float resultado = sqrt(pow(p.x,2) + pow(p.y,2));
	return resultado;
}

int dardosNoQuartoDeCirculo (TPonto v[], int tamanho, float raio){
	int i;
	int acertos = 0;
	for(i = 0; i < tamanho; i++){
		if(distancia(v[i]) <= raio){
			acertos++;
		}
	}
	return acertos;
}

void criaLog (FILE * arquivo, TPonto v[], int pontosNoAlvo, int totalDePontos){
	int i;
	arquivo = fopen ("pontos.dat", "w");
	fprintf(arquivo,"PONTOS OBITIDOS: ");
	for(i = 0; i < totalDePontos;i++){
		fprintf(arquivo,"\n( %f , %f ) ", v[i].x, v[i].y);
	}
	fprintf(arquivo,"\nTOTAL DE DADOS ARREMESSADOS -------------> %d", totalDePontos);
	fprintf(arquivo,"\nTOTAL DE DADOS NO QUARTO DE CIRCULO -----> %d", pontosNoAlvo);
	fprintf(arquivo,"\nVALOR ESTIMADO PARA PI ------------------> %d", totalDePontos/pontosNoAlvo);
	fclose(arquivo);
}


 
 

