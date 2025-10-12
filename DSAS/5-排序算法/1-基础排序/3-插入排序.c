#include <stdio.h>

void insertSort(int arr[], int size){
    for (int i = 1; i < size; ++i) {   //从第二个元素开始看
        int j = i, tmp = arr[i];   //j直接变成i，因为前面的都是有序的了，tmp相当于是抽出来的牌暂存一下
        while (j > 0 && arr[j - 1] > tmp) {   //只要j>0并且前一个还大于当前待插入元素，就一直往前找
            arr[j] = arr[j - 1];   //找的过程中需要不断进行后移操作，把位置腾出来
            j--;
        }
        arr[j] = tmp;  //j最后在哪个位置，就是是哪个位置插入
    }
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    insertSort(arr, size);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}