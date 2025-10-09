#include <stdio.h>

void bubbleSort(int arr[], int size){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {    //减 i 是因为前 i 轮已经排好了i个数
            //注意需要到N-1的位置就停止，因为要比较j和j+1
            //这里减去的i也就是已经排好的不需要考虑了
            if(arr[j] > arr[j + 1]) {   //如果后面比前面的小，那么就交换
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, size);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}