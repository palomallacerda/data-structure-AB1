#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(){
    fila *novo = start();

    int id, priori, op, newId, newPriori;

    while (1){
        handleMenu();
        scanf("%d", &op);
        if (op==0) break;
        if (op==1){
            puts("Insira [ID] [PRIORIDADE]:");
            scanf("%d %d", &id, &priori);
            enqueue(id, priori, novo);
        }else if (op==2){
            dequeue(novo);
        }else if (op==3){
            puts("Insira o [ID] e a nova [PRIORIDADE]:");
            scanf("%d %d", &newId, &newPriori);
            changeweight(novo, newId, newPriori);
        }else if (op==4){
            display(novo, 0);
        }
    }
    return 0;
}

void handleMenu (){
    puts("+------------------------+");
    puts("|  Escolha uma opção     |");
    puts("+------------------------+");
    puts("| 0 - sair               |");
    puts("| 1 - adicionar          |");
    puts("| 2 - remover            |");
    puts("| 3 - alterar prioridade |");
    puts("| 4 - mostrar            |");
    puts("+------------------------+");
    printf("|-> ");
}

void changeweight(fila *q, int id, int priority)
{
    if (q == NULL)
    {
        puts("Não existe elemento com esse ID.\n");

        return;
        
    } else{
        
        int i = 0;

        while(i < q->last + 1)
        {
            if (q->queue[i]->id == id)
            {
                printf("Prioridade %d será substituida por %d\n", q->queue[i]->priority, priority);
                q->queue[i]->priority = priority;
                buildHeap(q, q->last+1);
                puts("-------------- Substituído com sucesso!\n");
                return;
    
            } 
            i++; 
        }
        
    }
    
}

void display(fila  *q, int i)
{
    if (i!=q->last+1)
    {
        printf("ID: %d ", q->queue[i]->id);
        printf("Priority: %d\n", q->queue[i]->priority); 
        return display(q, i+1);
    }
}

fila *start() /*inicializando a fila*/
{
    fila *aux = (fila*)malloc(sizeof(fila));
    if(aux == NULL) printf("Não foi possivel alocar memória\n");
    aux->last = -1;
    int i = 0;
    while(i < TAM)
    {   
        aux->queue[i] = (object*) malloc(sizeof(object));
        if(aux->queue[i] == NULL) printf("Não foi possivel alocar memória\n");
        aux->queue[i]->id = 0;
        aux->queue[i]->priority = 0;
        i++;
    }
    return aux;
}

void trocaValores(object *a, object *b){

    object aux = *a;
    *a = *b;
    *b = aux;

}

int indexPai(int ultimo){

    return (ultimo - 1) / 2;
}

void enqueue(int id, int priority, fila *novo){

    if(novo->last + 1 == TAM){

        puts("-------------- ! FILA CHEIA !");

    } else {

        novo->last += 1;
        int ultimo = novo->last;

        novo->queue[ultimo]->id = id;
        novo->queue[ultimo]->priority = priority;

        int father = indexPai(ultimo);
        
        while(father>=0 && (novo->queue[ultimo]->priority > novo->queue[father]->priority) ){
            trocaValores(novo->queue[ultimo], novo->queue[father]);
            ultimo = father;
            father = indexPai(ultimo);

        }
        buildHeap(novo, novo->last);
        puts("-------------- Adicionado com sucesso!");
    }
}
   
int getRight (int i){ /*ultimo valor da direita*/
    return (2*i)+2;
}

int getLeft (int i){ /*ultimo valor da esquerda*/
    return (2*1)+1;
}

void dequeue (fila *novo){
    if (novo->last==-1){
        puts("-------------- ! FILA VAZIA !");
    }else{
        printf("ID do Removido = %d | Prioridade = %d\n", novo->queue[0]->id, novo->queue[0]->priority);
        trocaValores(novo->queue[0], novo->queue[novo->last]);
        novo->last--;
        if (novo->last>0){
            novo = max_heapify(novo, 0);
            display(novo, 0);
        }else{
            novo->queue[0]->id = 0;
            novo->queue[0]->priority = 0;
        }
    }
}
 
void buildHeap (fila *f, int sz){
    int lastNode = sz/2;
    int j;
    for (j=lastNode; j>=0; j--){
        max_heapify(f, j);
    }
}

fila * max_heapify (fila *f, int i){
    int largest = i, left = getLeft(i), right = getRight(i);
    if (left<f->last+1 && f->queue[left]->priority > f->queue[largest]->priority){
        largest = left;
    }else if (right<f->last+1 && f->queue[right]->priority > f->queue[largest]->priority){
        largest = right;
    }
    if (largest!=i){
        //printf("===== Menor %d Maior %d\n", f->queue[i]->priority, f->queue[largest]->priority);
        trocaValores(f->queue[i], f->queue[largest]); 
        max_heapify(f, largest);
    }
    else return f;
}
