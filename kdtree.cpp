#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio2.h>
#include <time.h>
#include <windows.h>



struct infoNodo
{
    int x;
    int y;
};

typedef struct infoNodo Info;

struct tree
{
    struct infoNodo info;
    struct tree *esq;
    struct tree *dir;
};

typedef struct tree Tree;

struct TpLista
{
    struct tree *arvore;
    struct TpLista *prox;
};

typedef struct TpLista Lista;

int gerarRandomico(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int contarNosDaArvore(Tree *arvore)
{
    if (arvore == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + contarNosDaArvore(arvore->esq) + contarNosDaArvore(arvore->dir);
    }
}

void ordenarPelaCoordenada(Lista **lista, int coordenada)
{
    // coordenada = 0 -> x | coordenada = 1 -> y
    Lista *aux = (*lista);
    Lista *aux2 = (*lista);
    Tree *temp;
    while (aux != NULL)
    {
        aux2 = aux->prox;
        while (aux2 != NULL)
        {
            if (coordenada == 0)
            {
                if (aux->arvore->info.x > aux2->arvore->info.x)
                {
                    temp = aux->arvore;
                    aux->arvore = aux2->arvore;
                    aux2->arvore = temp;
                }
            }
            else
            {
                if (aux->arvore->info.y > aux2->arvore->info.y)
                {
                    temp = aux->arvore;
                    aux->arvore = aux2->arvore;
                    aux2->arvore = temp;
                }
            }
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
}

Lista *fimDaLista(Lista *lista)
{
    while (lista->prox != NULL)
    {
        lista = lista->prox;
    }
    return lista;
}


Lista *mediana(Lista *inicio, Lista *fim) {
    int quantidade = 0;
    Lista *aux = inicio;
    while (aux != fim) {
        aux = aux->prox;
        quantidade++;
    }

    int mediana = quantidade % 2 == 0 ? quantidade / 2 : (quantidade + 1) / 2;
    aux = inicio;
    
	int i = 1;
    while(i < mediana){
    	aux = aux -> prox;
    	i++;
    }
    
    // Remover a liga��o com o restante da lista isolando a mediana
    Lista *aux2 = aux;
    aux = aux->prox;
    aux2->prox = NULL;
    return aux;
}


Tree *criarArvore()
{
    Tree *arvore = (Tree *)malloc(sizeof(Tree));
    arvore->info.x = gerarRandomico(10, 50);
    arvore->info.y = gerarRandomico(0, 50);
    arvore->esq = NULL;
    arvore->dir = NULL;
    return arvore;
}

Lista *criarLista(Tree *arvore)
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->arvore = arvore;
    lista->prox = NULL;
    return lista;
}

void inserirLista(Lista **lista, Tree *arvore)
{
    if ((*lista) == NULL)
    {
        (*lista) = criarLista(arvore);
    }
    else
    {
        // inserir ordenado
        Lista *aux = (*lista);
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = criarLista(arvore);
    }
}

Lista *construirListaDinamica()
{
    Lista *lista = NULL;
    int tamanho = gerarRandomico(10, 20);
    for (int i = 0; i < tamanho; i++)
    {
        inserirLista(&lista, criarArvore());
    }

    return lista;
}

Tree *construirArvore(Lista *lista, int nivel)
{
    if (lista == NULL)
    {
        return NULL;
    }
    else if (lista -> prox == NULL){
    	return lista -> arvore;
    } else 
    {
        ordenarPelaCoordenada(&lista, nivel % 2);
        Lista *med = mediana(lista, fimDaLista(lista));
        Tree *arvore = med->arvore;
        arvore->esq = construirArvore(lista, nivel + 1);
        arvore->dir = construirArvore(med->prox, nivel + 1);
        return arvore;
    }
}

void imprimirLista(Lista *lista)
{
    while (lista != NULL) {
    	printf("(%d,%d) ", lista->arvore->info.x, lista->arvore->info.y);
    	lista = lista->prox;
    }
    printf("\n");

}

void imprimirArvoreComGalhos(Tree *tree, int x, int y, int espacoHorizontal) {
    if (tree != NULL) {
        gotoxy(x, y);
        printf("(%d,%d)", tree->info.x, tree->info.y);

        if (tree->esq != NULL) {
            int novoXEsq = x - espacoHorizontal; // Nova coordenada x para o galho esquerdo
            int novoYEsq = y + 1; // Nova coordenada y para o galho esquerdo
            for (int i = x; i > novoXEsq; i--) {
                gotoxy(i, novoYEsq);
                printf("-");
            }

            int novoYFilhoEsq = novoYEsq + 2; // Nova coordenada y para o filho esquerdo
            gotoxy(novoXEsq, novoYFilhoEsq);
            printf("/");
            
            int novoEspacoHorizontalEsq = espacoHorizontal / 2; // Novo espa�amento horizontal para o pr�ximo n�
            imprimirArvoreComGalhos(tree->esq, novoXEsq, novoYFilhoEsq + 1, novoEspacoHorizontalEsq);
        }

        if (tree->dir != NULL) {
            int novoXDir = x + espacoHorizontal; // Nova coordenada x para o galho direito
            int novoYDir = y + 1; // Nova coordenada y para o galho direito
            for (int i = x; i < novoXDir; i++) {
                gotoxy(i, novoYDir);
                printf("-");
            }

            int novoYFilhoDir = novoYDir + 2; // Nova coordenada y para o filho direito
            gotoxy(novoXDir, novoYFilhoDir);
            printf("\\");
            
            int novoEspacoHorizontalDir = espacoHorizontal / 2; // Novo espa�amento horizontal para o pr�ximo n�
            imprimirArvoreComGalhos(tree->dir, novoXDir, novoYFilhoDir + 1, novoEspacoHorizontalDir);
        }
    }
}


double calcularDistancia(Info p1, Info p2) {
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

void buscarPontosProximos(Tree *root, Info coordenada, double raio) {
    if (root == NULL) {
        return;
    }

    double distancia = calcularDistancia(root->info, coordenada);

    if (distancia <= raio) {
        printf("(%d, %d) ", root->info.x, root->info.y);
    }

    // Verifica recursivamente nos filhos
    buscarPontosProximos(root->esq, coordenada, raio);
    buscarPontosProximos(root->dir, coordenada, raio);
}

void maximizarJanelaPrompt(){
	HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}

int main()
{
    srand(time(NULL));
    maximizarJanelaPrompt();
    Lista *listaOriginal = construirListaDinamica();
    printf("Lista original:\n");
    imprimirLista(listaOriginal);
    
    ordenarPelaCoordenada(&listaOriginal, 0);
    printf("\nLista reorganizada:\n");
    imprimirLista(listaOriginal);
    
    Tree *arvore = construirArvore(listaOriginal, 0);
    
    Info coordenada = {20, 30};
    double raio = 10.0;
    printf("\n\n");
    printf("Pontos mais proximos: ");
    buscarPontosProximos(arvore, coordenada, raio);
    
	printf("\n\n");
    printf("\nArvore KDTREE:\n");
    int xInicial = 40; // Coordenada x inicial para a impress�o
    int yInicial = 15;  // Coordenada y inicial para a impress�o
    int nivelEspaco = 20; // Espa�o entre os n�s
    imprimirArvoreComGalhos(arvore, xInicial, yInicial, nivelEspaco);
    
    getch();
    return 0;
}
