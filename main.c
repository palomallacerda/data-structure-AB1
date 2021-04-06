#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(){
    fila *novo = start();

    int id, priori, op, newId, newPriori;

    while (1){
        puts("------------------------- BEM VINDE -----------------------");
        puts(" 0 - sair\n 1 - adicionar\n 2 - remover\n 3 - alterar prioridade\n 4 - mostrar");
        scanf("%d", &op);
        if (op==0) break;
        if (op==1){
            puts("Diz qual é o id e a prioridade:");
            scanf("%d %d", &id, &priori);
            enqueue(id, priori, novo);
            puts("adicionado com sucesso");
            puts("");
        }else if (op==2){
            dequeue(novo);
        }else if (op==3){
            puts("Insira o id e a nova prioridade: ");
            scanf("%d %d", &newId, &newPriori);
            changeweight(novo, newId, newPriori);
        }else if (op==4){
            display(novo, 0);
        }
    }
    return 0;
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
                return;
    
            } 
            i++; 
        }
    
        puts("Substituido com sucesso\n");
    
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

      puts("Topado, já era.");

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
    }
}
   
int getRight (int i){ /*ultimo valor da direita*/
    return (2*i)+2;
}

int getLeft (int i){ /*ultimo valor da esquerda*/
    return (2*1)+1;
}

int dequeue(fila *novo){
    if (novo->last==-1){
        puts("FILA VAZIA");
    }else{
        printf("ID do Removido = %d | Prioridade = %d\n", novo->queue[0]->id, novo->queue[0]->priority);
        int leftRoot = getLeft(0);
        int rightRoot = getRight(0);
        
        if (novo->queue[leftRoot]!=NULL){ // raíz possui filhos a esquerda
            int aux_left = getLeft(leftRoot);
            int aux_right = getRight(leftRoot);

            trocaValores(novo->queue[leftRoot], novo->queue[0]);

            object *rightSon, *leftSon;

            if(aux_left < aux_right){
              
              rightSon = novo->queue[aux_right];
              trocaValores(rightSon, novo->queue[rightRoot]);
            }
            else{
                
               leftSon = novo->queue[aux_left]; 
               trocaValores(leftSon, novo->queue[leftRoot]); 
            }

            
        }else if (novo->queue[rightRoot]!=NULL){  //raiz possui filhos a direita
            
        }else{ // raíz é o único no array
            novo->queue[0]->id = -1;
            novo->queue[0]->priority = -1;
        }
        novo->last--;
    }
}

