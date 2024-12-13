#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
	int vertice;
	struct No *proximo;
}No;

typedef struct Lista
{
	No *inicio;
}Lista;


void inicializa(Lista *lista, int *visitados, int *ancestrais, int *in, int *lower, int qtdVertices);
void preencheGrafo(Lista *lista, int qtdArestas);
void insereNaLista(Lista *lista, int valor);
void imprimeLista(Lista *lista);
void imprimeGrafo(Lista *lista, int qtdVertices);
void identificaPonte(Lista *lista, int *visitados, int *ancestrais, int *in, int *lower, int *tempo, int raiz, int *pontes);

int main()
{
	
	int casosTeste, tempo = 0, pontes;
	int i = 0;
	//printf("\nIsira os casos de teste ");
	scanf("%d", &casosTeste);
	int c = 0;
	
	
	
	for(i; i < casosTeste; i++)
	{
		c++;
		pontes = 0;
		//printf("\nVertices e arestas: ");
		int qtdVertices, qtdArestas;
		
		scanf("%d %d", &qtdVertices, &qtdArestas);
		qtdVertices +=1;
		
		int visitados[qtdVertices], ancestrais[qtdVertices], in[qtdVertices], lower[qtdVertices];
		Lista lista[qtdVertices];
		
		
		
		inicializa(lista, visitados, ancestrais, in, lower, qtdVertices);
		preencheGrafo(lista, qtdArestas);
		
		//imprimeGrafo(lista, qtdVertices);
		
		printf("\nCaso #%d", c);
		
		identificaPonte(lista, visitados, ancestrais, in, lower, &tempo, 1, &pontes);
		printf("\n%d", pontes);
		
		if(pontes == 0)
		{
			printf("\nSin bloqueos");
		}
		printf("\n");
		
	}
	
	return 0;
}

void inicializa(Lista *lista, int *visitados, int *ancestrais, int *in, int *lower, int qtdVertices)
{
	int i = 0;
	for(i; i < qtdVertices; i++)
	{
		lista[i].inicio = NULL;
		visitados[i] = 0;
		ancestrais[i] = 0;
		in[i] = 0;
		lower[i] = 0;
	}
}
void preencheGrafo(Lista *lista, int qtdArestas)
{
	int a, b, i = 0;

	for(i; i < qtdArestas; i++)
	{
		//printf("\nIforme arestas a e b: ");
		scanf("%d %d", &a, &b);
		
		insereNaLista(&lista[a], b);
		insereNaLista(&lista[b], a);
	}
}
void insereNaLista(Lista *lista, int valor)
{
	No *novo = (No*)calloc(1, sizeof(No));
	
	if(novo == NULL)
	{
		printf("\nFalha na alocacao!");
	}
	else
	{
		novo->vertice = valor;
		
		if(lista->inicio == NULL || lista->inicio->vertice > novo->vertice)
		{
			novo->proximo = lista->inicio;
			lista->inicio = novo;
		}
		else
		{
			No *aux = lista->inicio;
			
			while(aux->proximo != NULL && aux->proximo->vertice < novo->vertice)
			{
				aux = aux->proximo;
			}
			novo->proximo = aux->proximo;
			aux->proximo = novo;
		}
	}
}
void imprimeLista(Lista *lista)
{
	if(lista->inicio == NULL)
	{
		printf(" ");
	}
	else
	{
		No *aux = lista->inicio;
		
		while(aux)
		{
			printf("%d ", aux->vertice);
			aux = aux->proximo;
		}
	}
}
void imprimeGrafo(Lista *lista, int qtdVertices)
{
	
	int i = 0;
	for(i; i < qtdVertices; i++)
	{
		printf("\n%d - ", i);
		imprimeLista(&lista[i]);
	}
}
void identificaPonte(Lista *lista, int *visitados, int *ancestrais, int *in, int *lower, int *tempo, int raiz, int *pontes)
{
	*tempo +=1;
	visitados[raiz] = 1;
	in[raiz] = lower[raiz] = *(tempo);
	
	//printf("%d ", raiz);
	
	No *adj = lista[raiz].inicio;
	
	while(adj)
	{
		int filho = adj->vertice;
		
		if(visitados[filho] == 0)
		{
			ancestrais[filho] = raiz;
			identificaPonte(lista, visitados, ancestrais, in, lower, tempo, filho, pontes);
			
			if(lower[filho] > in[raiz])
			{
				printf("\n%d %d", raiz, filho);
				*(pontes) += 1;
				
			}
			if(lower[filho] < lower[raiz])
			{
				lower[raiz] = lower[filho];
			}
		}
		else if(visitados[filho] == 1 && ancestrais[raiz] != filho)
		{
			//printf("\nAresta de retorno: %d %d", filho, raiz);
			
			if(lower[raiz] > in[filho])
			{
				lower[raiz] = in[filho];
			}
		}
		
		adj = adj->proximo;
	}
}