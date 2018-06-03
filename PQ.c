// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#define INIT_HEAPSIZE 2

typedef struct PQRep {
	ItemPQ *items;
	int nslots;     //how many total slots we have
	int size;       //how many were using rn
} PQRep;

void fixUp(ItemPQ a[], int i);
void swap(ItemPQ a[], int i, int j);
int larger(ItemPQ a, ItemPQ b);
void fixDown(ItemPQ a[], int i, int N);
void arrayCopy(ItemPQ *array1, ItemPQ *array2, int size);
// Creates new priority queue, that can store items of type ItemPQ.

PQ newPQ(){
    PQ new = (PQRep *)malloc(sizeof(PQRep));
    if (new == NULL){
        printf("Malloc Failed");
        exit(1);
    }

    ItemPQ *newItems = malloc(INIT_HEAPSIZE*sizeof(ItemPQ));
    if (newItems == NULL){
        printf("Malloc Failed");
        exit(1);
    }

    new->items = newItems;
    new->size = 0; 
    new->nslots = INIT_HEAPSIZE;
    return new;
}

int PQEmpty(PQ p) {
	if (p->size == 0 || p == NULL){
	    return 1;
	}
	return 0;
}

void  addPQ(PQ pq, ItemPQ item){
    //check if item with key exists
    //if it does then update its value
    int bln = -1;
    for(int i = 1; i <= pq->size; i++){
        if (pq->items[i].key == item.key){
            updatePQ(pq, item);
            bln = 1;
            break; 
        }
    }
    if (bln == -1){         //this indicates that we did not find an item with the existing key
        if (pq->size == pq->nslots -1){
            pq->nslots++;
            ItemPQ *newItems = malloc(pq->nslots*sizeof(ItemPQ));            
            arrayCopy(pq->items, newItems, pq->size);
            pq->items = newItems;
        }
        assert(pq->size < pq->nslots);
        pq->size++;
        pq->items[pq->size] = item;
        fixUp(pq->items, pq->size);
    }
     
}

ItemPQ dequeuePQ(PQ pq) {
    ItemPQ remove = pq->items[1];
    pq->items[1] = pq->items[pq->size];
    pq->size--;
    fixDown(pq->items, 1, pq->size);
	return remove;
}

void updatePQ(PQ pq, ItemPQ element) {
    int i = 0;
    while (i <= pq->size){
        if (pq->items[i].key == element.key){
            pq->items[i].value = element.value;
            fixUp(pq->items, pq->size);
        }
        i++;
    }
}

void  showPQ(PQ pq) {
    int i = 1;
    int j = 0;
    int count = 0;
    while (i < pq->nslots && i <= pq->size){
        double power = pow(2,j);
        printf("%d ", pq->items[i].key);
        count++;
        if (count == power){
            printf("\n");
            count = 0;
            j++;
        }
        i++;
        
    }
    printf("\n");
    printf("\n");
    
    
     i = 1;
     j = 0;
     count = 0;
    while (i < pq->nslots && i <= pq->size){
        double power = pow(2,j);
        printf("%d ", pq->items[i].value);
        count++;
        if (count == power){
            printf("\n");
            count = 0;
            j++;
        }
        i++;
        
    }
    printf("\n");
}

void  freePQ(PQ pq){
    //for (int i = 0; i <= pq->size; i++){
    //    free(pq->items[i]);
    //}
    free(pq->items);
    free(pq);
}
//helper functions fixup, fix down and swap are based off week11 lectures notes from COMP2521
void fixUp(ItemPQ a[], int i){
    while (i > 1 && larger(a[i/2],a[i]) == 1) {
        swap(a, i, i/2);
        i = i/2;
    }
}
void fixDown(ItemPQ a[], int i, int N){
    while (2*i <= N) {
        int j = 2*i;          //j stores the index of the left child
        if (j < N && larger(a[j], a[j+1]) == 1) j++;     //j store index of the smaller of the 2 children
        if (larger(a[i], a[j]) == 0 && a[i].value != a[j].value) break;
        swap(a, i, j);
        i = j;
    }
}
void swap(ItemPQ a[], int i, int j){
    ItemPQ tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
int larger(ItemPQ a, ItemPQ b){
    if (a.value > b.value){
        return 1;
    } else {
        return 0;
    }
}
void arrayCopy(ItemPQ *array1, ItemPQ *array2, int size){     //copy contents of array1 into array2
    int i = 1;
    while (i <= size){
        array2[i] = array1[i];
        i++;
    }
}

