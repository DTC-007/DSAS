#include <stdio.h>

void quickSort(int arr[], int start, int end){
    if(start >= end) return;    //范围不可能无限制的划分下去，要是范围划得都没了，肯定要结束了
    int left = start, right = end, pivot = arr[left];   //这里我们定义两个指向左右两个端点的指针，以及取出基准
    while (left < right) {     //只要两个指针没相遇，就一直循环进行下面的操作
        while (left < right && arr[right] >= pivot) right--;   //从右向左看，直到遇到比基准小的
        arr[left] = arr[right];    //遇到比基准小的，就丢到左边去
        while (left < right && arr[left] <= pivot) left++;   //从左往右看，直到遇到比基准大的
        arr[right] = arr[left];    //遇到比基准大的，就丢到右边去
    }
    arr[left] = pivot;    //最后相遇的位置就是基准存放的位置了
    quickSort(arr, start, left - 1);   //不包含基准，划分左右两边，再次进行快速排序
    quickSort(arr, left + 1, end);
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0,size-1);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}