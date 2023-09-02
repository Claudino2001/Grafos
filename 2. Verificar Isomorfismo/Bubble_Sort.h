#ifndef Bubble_Sort
#define Bubble_Sort

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

void bubbleSort(int *v, int n){ 
    if (n < 1)return; 
 
    for (int i=0; i<n; i++) 
        if (v[i] > v[i+1]) 
            swap(&v[i], &v[i+1]);  
    bubbleSort(v, n-1); 
}

#endif