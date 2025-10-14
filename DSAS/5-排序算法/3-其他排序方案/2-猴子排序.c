#include <stdio.h>
#include <stdlib.h>

void swap(int * a, int * b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

_Bool checkOrder(int arr[], int size){
    for (int i = 0; i < size - 1; ++i)
        if(arr[i] > arr[i + 1]) return 0;
    return 1;
}

int main(){
    int arr[] = {3,5, 7,2, 9, 0, 6,1, 8, 4}, size = 10;

    int counter = 0;
    while (1) {
        int a = rand() % size, b = rand() % size;
        swap(&arr[a], &arr[b]);
        if(checkOrder(arr, size)) break;
        counter++;
    }
    printf("在第 %d 次排序完成！", counter);
}