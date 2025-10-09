#include <stdio.h>

void bubbleSort(int arr[], int size){
    for (int i = 0; i < size - 1; ++i) {   //只需要size-1次即可
        _Bool flag = 1;   //这里使用一个标记，默认为1表示数组是有序的
        for (int j = 0; j < size - i - 1; ++j) {
            if(arr[j] > arr[j + 1]) {
                flag = 0;    //如果发生交换，说明不是有序的，把标记变成0
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
        if(flag) break;   //如果没有发生任何交换，flag一定是1，数组已经有序，所以说直接结束
    }
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, size);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}