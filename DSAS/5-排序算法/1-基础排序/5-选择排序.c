#include <stdio.h>

void selectSort(int arr[], int size){
    for (int i = 0; i < size - 1; ++i) {   //因为最后一个元素一定是在对应位置上的，所以只需要进行N - 1轮排序
        int min = i;   //记录一下当前最小的元素，默认是剩余元素中的第一个元素
        for (int j = i + 1; j < size; ++j)   //挨个遍历剩余的元素，如果遇到比当前记录的最小元素还小的元素，就更新
            if(arr[min] > arr[j])
                min = j;
        int tmp = arr[i];    //找出最小的元素之后，开始交换
        arr[i] = arr[min];
        arr[min] = tmp;
    }
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    selectSort(arr, size);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}