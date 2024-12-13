#include <stdio.h>
#include <stdlib.h>

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
	struct registro *proximo;
	
}Registro;

typedef struct teste{
	struct ponte *pontes;
	int num_pontes;
}Teste;

typedef struct ponte{
	int u;
	int v;
	
}Ponte;

Registro *aloca_registro(){
	Registro *novo = (Registro *) calloc(1, sizeof(Registro));
	return novo;
}

Lista *aloca_lista(){
	Lista *novo = (Lista *) calloc(1, sizeof(Lista));
	return novo;
}

void incluit_vertice_lista(Vertice *vertice, int valor){
	if(vertice->adj == NULL){
		vertice->adj = aloca_lista();
			}
	Registro *novo = aloca_registro();
	novo->valor = valor;
	if(vertice->adj->inicio == NULL){
		vertice->adj->final = novo;
		vertice->adj->inicio = novo;
		
	}
	else{
		vertice->adj->final->proximo = novo;
		vertice->adj->final = novo;
	}
	}
	
void dfs(Vertice *vertices, int raiz, int pai, int *count, Ponte *pontes, int *num_pontes){
		vertices[raiz].visitado = 1;
		vertices[raiz].in = vertices[raiz].low = (*count)++;
		
		if(vertices[raiz].adj != NULL){
			Registro *aux = vertices[raiz].adj->inicio;
			while(aux != NULL){
				if(vertices[aux->valor].visitado == 0){
					dfs(vertices, aux->valor, raiz, count, pontes, num_pontes);
					if(vertices[aux->valor].low > vertices[raiz].in){
						pontes[*num_pontes].u = aux->valor;
						pontes[*num_pontes].v = raiz;
						(*num_pontes)++;
						
					}
					
					if(vertices[raiz].low > vertices[aux->valor].low){
						vertices[raiz].low = vertices[aux->valor].low;
					}
				}
				else if(aux->valor != pai){
					if(vertices[raiz].low > vertices[aux->valor].in){
						vertices[raiz].low = vertices[aux->valor].in;
					}
				}
				aux = aux->proximo;
			}
		}
}
	
int main(int argc, char *argv[]) {
	int qtd_vertices, qtd_arestas, qtd_testes, a, b, t, i;
	int count = 1;
	int num_pontes = 0;
	scanf("%d", &qtd_testes);
	Teste *testes = (Teste *)calloc(qtd_testes, sizeof(Teste));
	
	for(t = 0; t<qtd_testes; t++){
		scanf("%d %d", &qtd_vertices, &qtd_arestas);
		
		Vertice *vertices = (Vertice *)calloc(qtd_vertices+1, sizeof(Vertice));
		Ponte *pontes = (Ponte *)calloc(qtd_arestas, sizeof(Ponte));
		
		for( i=0; i<qtd_arestas; i++){
			scanf("%d %d", &a, &b);
			
			incluit_vertice_lista(&vertices[a], b);
			incluit_vertice_lista(&vertices[b], a);
		}
		
		for( i=1; i<=qtd_vertices; i++){
			if(vertices[i].visitado == 0){
				dfs(vertices, i, -1, &count, pontes, &num_pontes);
				
			}
			
			
		}
		testes[t].num_pontes = num_pontes;
			testes[t].pontes = pontes;
			
			count = 1;
			num_pontes = 0;
		
	}
	for( t =0; t<qtd_testes; t++){
		printf("Caso #%d\n", t+1);
		if(testes[t].num_pontes == 0){
			printf("sin bloqueos\n");
		}
		else{
			printf("%d\n", testes[t].num_pontes);
			for( i=0; i<testes[t].num_pontes; i++){
				printf("%d %d\n", testes[t].pontes[i].u, testes[t].pontes[i].v);
			}
		}
	}
	
	
	return 0;
}