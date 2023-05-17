#include <cstdio>
#include <cstdlib>
#include <string>
#include <queue>

using namespace std;

//Representa um no da arvore
typedef struct no{
    int dado;
    int altura;
    struct no* direita;
    struct no* esquerda;
}No;

typedef struct bst{
    No* raiz;
    int tamanho;
}BST;

//Representa a arvore
BST* criaArvore(){
    BST* p = (BST*) malloc(sizeof(BST));
    p->raiz = NULL; 
    p->tamanho = 0;

    return p;
}

/**
 * @brief Cria um novo no da arvore
 * 
 * @param dado 
 * @return No* 
 */
No* criaNo(int dado){
    No* n = (No*) malloc(sizeof(No));
    if(n == NULL) exit(1);
    n->dado = dado;
    n->altura = 0;
    n->direita = NULL;
    n->esquerda = NULL;


    return n;
}

/**
 * @brief Retorna o maior valor de a ou b
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int maior(int a, int b){
    return (a>b)? a:b;
}

/**
 * @brief Retorna a altura de um no
 * 
 * @param no 
 * @return int 
 */
int alturaNo(No* no){
    if(no == NULL){
        return -1;
    }else{
        return no->altura;
    }      
}

/**
 * @brief Calcula o fator de balanceamento de um no
 * 
 * @param no 
 * @return int 
 */
int fatorBalanceamento(No *no){
    if(no != NULL){
        return alturaNo(no->esquerda) - alturaNo(no->direita);
    }else{
        return 0;
    }
}

/**
 * @brief Faz a rotação da arvore para a esquerda
 * 
 * @param raiz 
 * @return No* 
 */
No* rotacionarEsquerda(No* raiz){
   
    No* y, *f; 

    y = raiz->direita; // no direita da raiz
    f = y->esquerda;   //no esquerda de y

    //Fazendo a rotacao
    y->esquerda = raiz;
    raiz->direita = f;


    //recalcula as alturas dos nós
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    y->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

    return y;
}

/**
 * @brief Faz a rotação da arvore para a direita
 * 
 * @param raiz 
 * @return No* 
 */
No* rotacionarDireita(No* raiz){
    No* y, *f;

    y = raiz->esquerda; //ó esquerda da raiz
    f = y->direita; //nó direita de y

    //Fazendo a rotacao
    y->direita = raiz;
    raiz->esquerda = f;

    //recalcula as alturas dos nós
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    y->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

    return y;
}

/**
 * @brief Faz a rotação esquerda->direita da arvore
 * 
 * @param raiz 
 * @return No* 
 */
No* rotacionarDireitaEsquerda(No* raiz){
    raiz->direita = rotacionarDireita(raiz->direita); //Faz a rotação a direita
    return rotacionarEsquerda(raiz); //Faz a rotação a esquerda
}

No* rotacionarEsquerdaDireita(No* raiz){
    raiz->esquerda = rotacionarEsquerda(raiz->esquerda);
    return rotacionarDireita(raiz);
}

No* balancear(No* raiz){
    int f = fatorBalanceamento(raiz);//calcula o fator de balanceamento do no

    //Rotaciona para a esquerda
    if(f<-1 && fatorBalanceamento(raiz->direita) <=0){ 
        
        raiz = rotacionarEsquerda(raiz);
    
    
    }
    //rotaciona para a direita->esquerda
    else if(f<-1 && fatorBalanceamento(raiz->direita) >0){
        
        raiz = rotacionarDireitaEsquerda(raiz);
    
    }
    //rotaciona para a direita
    else if(f>1 && fatorBalanceamento(raiz->esquerda) >= 0){
        
        raiz = rotacionarDireita(raiz);
    
    }
    //rotaciona para a esquerda->direita
    else if(f>1 && fatorBalanceamento(raiz->esquerda) < 0){
        
        raiz = rotacionarEsquerdaDireita(raiz);
    
    }

    return raiz;
}

/**
 * @brief Insere um elemento na arvore e balanceia a mesma
 * 
 * @param dado 
 * @param raiz 
 * @param arvore 
 * @return No* 
 */
No* insereArvore(int dado, No* raiz, BST* arvore){
    if(raiz == NULL){
        arvore->tamanho++;
        return criaNo(dado);       
    }

    if(dado < raiz->dado){
        raiz->esquerda = insereArvore(dado, raiz->esquerda, arvore);
    }else if(dado > raiz->dado){
        raiz->direita = insereArvore(dado, raiz->direita, arvore);
    }else{
        printf("O elemento ja existe\n");
    }
    //Recalcula a altura de todos os nos entre a raiz e o no inserido 
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita))+1;
    
    //Balanceia a sub-arvore
    raiz = balancear(raiz);
    
    return raiz;
    
}

/**
 * @brief Encontra o menor elemento em uma arvore
 * 
 * @param raiz 
 * @return No* 
 */
No* encontraMenor(No* raiz){
    No* aux = raiz;
    while(aux != NULL && aux->esquerda!=NULL){
        aux = aux->esquerda;
    }
    return aux;
}

/**
 * @brief Encontra o maior elemento em uma arvore
 * 
 * @param raiz 
 * @return No* 
 */
No* encontraMaior(No* raiz){
    No* aux = raiz;
    while(aux != NULL && aux->direita!=NULL){
        aux = aux->direita;
    }
    return aux;
}

/**
 * @brief Remove o no de uma arvore e balanceia a mesma
 * 
 * @param dado 
 * @param raiz 
 * @param arvore 
 * @return No* 
 */
No* removeNo(int dado, No* raiz, BST* arvore) {
    if (raiz == NULL) {
        printf("O elemento nao existe na arvore\n");
        return NULL;
    }

    if (raiz->dado == dado) {
        if (raiz->direita == NULL && raiz->esquerda == NULL) {
            free(raiz);
            arvore->tamanho--;
            return NULL;
        }
        else if (raiz->esquerda == NULL || raiz->direita == NULL) {
            No* aux;
            if (raiz->esquerda == NULL) {
                aux = raiz->direita;
            }
            else {
                aux = raiz->esquerda;
            }
            free(raiz);
            arvore->tamanho--;
            return aux;
        }
        else {
            No* aux = encontraMaior(raiz->esquerda);
            raiz->dado = aux->dado;
            raiz->esquerda = removeNo(aux->dado, raiz->esquerda, arvore);
            raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
            raiz = balancear(raiz);
            return raiz;
        }
    }
    else if (dado < raiz->dado) {
        raiz->esquerda = removeNo(dado, raiz->esquerda, arvore);
    }
    else {
        raiz->direita = removeNo(dado, raiz->direita, arvore);
    }

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    raiz = balancear(raiz);
    return raiz;
}



/**
 * @brief Encontra a altura total da arvore
 * 
 * @param raiz 
 * @return int 
 */
int alturaArvore(No* raiz){
    if(raiz == NULL){
        return -1;
    }else{
        int esq = alturaArvore(raiz->esquerda);
        int dir = alturaArvore(raiz->direita);
        if(esq > dir){
            return esq + 1;
        }else{
            return dir + 1;
        }
    }
}

/**
 * @brief Libera a memoria da arvore
 * 
 * @param raiz 
 */
void liberaArvore(No* raiz){
    if(raiz != NULL){
        liberaArvore(raiz->esquerda);
        liberaArvore(raiz->direita);
        free(raiz);
    }
}

/**
 * @brief Imprime a arvore
 * 
 * @param raiz 
 * @param nivel 
 */
void imprimir(No* raiz, int nivel){
    int i;
    if(raiz != NULL){
        imprimir(raiz->direita, nivel+1);
        printf("\n\n");

        for(i=0; i<nivel; i++)
            printf("\t");

        printf("%d", raiz->dado);
        imprimir(raiz->esquerda, nivel +1);  
    }
}

/**
 * @brief Cria um arquivo txt que representa a arvore e vai ser lido pelo graphviz
 * 
 * @param arvore 
 */
void gerarGrafo(BST* arvore) {
    FILE* file = fopen("tree.dot", "w");

    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [shape=circle];\n");

    queue<No*> nodeQueue;
    nodeQueue.push(arvore->raiz);

    while (!nodeQueue.empty()) {
        No* current = nodeQueue.front();
        nodeQueue.pop();

        fprintf(file, "    %d;\n", current->dado);

        if (current->esquerda != NULL) {
            fprintf(file, "    %d -> %d;\n", current->dado, current->esquerda->dado);
            nodeQueue.push(current->esquerda);
        }

        if (current->direita != NULL) {
            fprintf(file, "    %d -> %d;\n", current->dado, current->direita->dado);
            nodeQueue.push(current->direita);
        }
    }

    fprintf(file, "}\n");

    fclose(file);
}



int main(){
    BST* arvore = criaArvore();
    int op;
    
    do{
        
        printf("Digite a opercao desejada:\n");
        printf("1- Inserir arvore\n");
        printf("2- Remover arvore\n");
        printf("3- Printar arvore\n");
        printf("4- Encerrar programa\n");
        scanf("%d", &op);
        
        switch (op){
            case 1:{
                int n;
                printf("Digite um inteiro: \n");
                scanf("%d", &n);
                arvore->raiz = insereArvore(n,arvore->raiz, arvore);
                break;
            }
            case 2:{
                int n;
                printf("Digite um inteiro: \n");
                scanf("%d", &n);
                arvore->raiz = removeNo(n,arvore->raiz, arvore);
                
                break;
            } 
            case 3:{
                
                imprimir(arvore->raiz, 1);
                break;
            } 
        }

        printf("\n");
    }while(op != 4);
    
    gerarGrafo(arvore);

    liberaArvore(arvore->raiz);
    free(arvore);
    
    return 0;
    
}
