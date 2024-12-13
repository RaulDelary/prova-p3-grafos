#include <stdio.h>
#include <stdlib.h>

typedef struct registro{
	struct registro *prox;
	int valor;
}registro;

typedef struct lista{
	
	struct registro *inicio;
	struct registro *final;
	
}lista;

typedef struct vertice{
	
	struct lista *adj;
	int visitado;
	int lower;
	int in;
	
}vertice;

int count = 0;
int pontes = 0;

registro *aloca_registro(){
	registro *novo = (registro*)calloc(1,sizeof(registro));
	novo -> prox = NULL;
	
	return novo;
}

lista *aloca_lista(){
	lista *novo = (lista*)calloc(1,sizeof(lista));
	novo -> inicio = NULL;
	novo -> final = NULL;
	
	return novo; 
}


void incluir_vertice_adj(vertice *v, int valor){
	if(v->adj == NULL){
		v->adj = aloca_lista();
	}
	
	registro *novo = aloca_registro();
	novo -> valor = valor;
	
	if(v->adj->inicio == NULL){
		v->adj->inicio = novo;
		v->adj->final = novo;
	}
	else{
		v->adj->final->prox = novo;
		v->adj->final = novo;
	}
}


int menor(int a, int b){
	int menor;
	if(a < b){
		menor = a;
	}
	if(b < a){
		menor = b; 
	}
	return menor;
}

void dfs(int raiz, vertice *vertices, int pai){
	int filho;
	
	
	vertices[raiz].visitado = 1;
	vertices[raiz].in = count;
	vertices[raiz].lower = count;
	
	count++;

	registro *aux; 
	aux = vertices[raiz].adj->inicio;
	
	while(aux != NULL){
		
		filho = aux -> valor;
		
		if(filho == pai){
			aux = aux -> prox;
			continue;
		}else{
			
			if(vertices[filho].visitado){
				vertices[raiz].lower = menor(vertices[filho].in, vertices[raiz].lower);
				
			}else{
				
			 	dfs(filho, vertices, raiz);
			}
			
			if(vertices[filho].lower > vertices[raiz].lower){
				printf("%d %d\n", raiz, filho);
				pontes++;	
			}
		
			vertices[raiz].lower = menor(vertices[raiz].lower, vertices[filho].lower);
			
			
					
		}
		aux = aux -> prox;
	}
	
}


int main(){
	int i, j, a, b, casos, qtd_v, qtd_a;
	
	scanf("%d", &casos);
	
	for(j= 1; j <= casos; j++){
		
		
		scanf("%d %d", &qtd_v, &qtd_a);
		
		vertice *vertices = (vertice*)calloc(sizeof(vertice), qtd_v+1);
		
		
		for(i = 0; i < qtd_a; i++){
			scanf("%d %d", &a, &b);
			incluir_vertice_adj(&vertices[a], b);
			incluir_vertice_adj(&vertices[b], a);
		}
		
		printf("Caso #%d\n", j);
	
		for(i= 1; i<=qtd_v; i++){
			dfs(1, vertices, 0);
		}
		if(pontes ==0){
			printf("Sin bloqueos");
		}else{
			printf("%d\n", pontes);
		}
		pontes = 0;
		count = 0;
	}
	
	return 0;
}