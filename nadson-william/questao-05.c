#include <stdio.h>
#include <stdlib.h>

const int INF = 1000000;

typedef struct vertice{
	int visitado;
	int in;
	int low;
	struct lista *adj;
}Vertice;

typedef struct lista{
	struct registro *inicio;
	struct registro *final;
	
}Lista;

typedef struct registro{
	int valor;
	int peso;
	struct registro *proximo;
	
}Registro;

typedef struct teste{
	//struct ponte *pontes;
	int *distancias;
}Teste;


typedef struct fila{
	int tamanho;
	struct no *inicio;
}Fila;

typedef struct no{
	int distancia_vertice;
	int vertice;
	struct no *proximo;
}No;

Registro *aloca_registro() {
	Registro *novo = (Registro *) calloc(1, sizeof(Registro));
	return novo;
}

Lista *aloca_lista(){
	Lista *novo = (Lista *) calloc(1, sizeof(Lista));
	return novo;
}
Fila *aloca_fila(){
	Fila *novo = (Fila *) calloc(1, sizeof(Fila));
	return novo;
}

No *aloca_no(){
	No *novo = (No *) calloc(1, sizeof(No));
	return novo;
}

void incluit_vertice_lista(Vertice *vertice, int valor, int peso){
	if(vertice->adj == NULL){
		vertice->adj = aloca_lista();
			}
	Registro *novo = aloca_registro();
	novo->valor = valor;
	novo->peso = peso;
	if(vertice->adj->inicio == NULL){
		vertice->adj->final = novo;
		vertice->adj->inicio = novo;
		
	}
	else{
		vertice->adj->final->proximo = novo;
		vertice->adj->final = novo;
	}
	}
	
	void inserir_fila(Fila *fila, int vertice, int distancia){
		No *novo = aloca_no();
		novo->vertice = vertice;
		novo->distancia_vertice = distancia;
		if(fila->inicio == NULL || distancia < fila->inicio->distancia_vertice){
			novo->proximo = fila->inicio;
			fila->inicio = novo;
			
				}
		else{
			No *aux = fila->inicio;
			while(aux->proximo != NULL && distancia >= aux->proximo->distancia_vertice ){
				aux = aux->proximo;
			}
			novo->proximo = aux->proximo;
			aux->proximo = novo;
		}
		
		fila->tamanho ++;
		
	}
	
	No *remover_fila(Fila *fila){
		No *remover;
		if(fila->inicio){
			remover = fila->inicio;
			fila->inicio = fila->inicio->proximo;
			fila->tamanho --;
		}
		return remover;
	}
	
	void dijskstra(Vertice *vertices, int raiz,int qtd_vertices, int *dist){
		int i;
		for(i = 1; i<=qtd_vertices; i++){
			
			dist[i] = INF;
			vertices[i].visitado = 0;
		}
		Fila *fila = aloca_fila();
		dist[raiz] = 0;
		inserir_fila(fila, raiz, dist[raiz] );
		
		while(fila->tamanho >0){
			No *no_aux = remover_fila(fila);
		if(vertices[no_aux->vertice].adj != NULL){
			Registro *registro_aux =vertices[no_aux->vertice].adj->inicio; 
			while(registro_aux != NULL){
				if(dist[registro_aux->valor] > registro_aux->peso + no_aux->distancia_vertice){
					dist[registro_aux->valor] = registro_aux->peso + no_aux->distancia_vertice;
					inserir_fila(fila, registro_aux->valor, dist[registro_aux->valor]);
				}
				registro_aux = registro_aux->proximo;
			}
		}
		}
	}
		
	
	
int main(int argc, char *argv[]) {
	int qtd_vertices, qtd_arestas, qtd_testes, a, b, t, i, origem, destino, peso;
	int count = 1;
	int num_pontos = 0;
	scanf("%d", &qtd_testes);
	Teste *testes = (Teste *)calloc(qtd_testes, sizeof(Teste));
	
	for(t = 0; t<qtd_testes; t++){
		scanf("%d %d", &qtd_vertices, &qtd_arestas);
		
		Vertice *vertices = (Vertice *)calloc(qtd_vertices+1, sizeof(Vertice));
		int *dist = (int *)calloc(qtd_vertices+1, sizeof(int));
		
		for( i=0; i<qtd_arestas; i++){
			scanf("%d %d %d", &a, &b, &peso);
			
			incluit_vertice_lista(&vertices[a], b, peso);
			incluit_vertice_lista(&vertices[b], a, peso);
		}
		
		
		scanf("%d %d", &origem, &destino);
		dijskstra(vertices, origem, qtd_vertices, dist);
		
			testes[t].distancias = dist[destino];
		
		
	}
	for( t =0; t<qtd_testes; t++){
		
		if(testes[t].distancias == INF){
			printf("No\n");
		}
		else{
			
				printf("%d\n", testes[t].distancias);
			
		}
	}
	
	
	return 0;
}