#include <stdio.h>

int binarySearch(int arr[], int left, int right, int target){
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if(target == arr[mid]) return mid + 1;   //如果插入元素跟中间元素相等，直接返回后一位
        else if (target < arr[mid])  //如果大于待插入元素，说明插入位置肯定在左边
            right = mid - 1;   //范围划到左边
        else
            left = mid + 1;   //范围划到右边
    }
    return left;   //不断划分范围，left也就是待插入位置了
}

void insertSort(int arr[], int size){
    for (int i = 1; i < size; ++i) {
        int tmp = arr[i];
        int j = binarySearch(arr, 0, i - 1, tmp);   //由二分搜索来确定插入位置
        for (int k = i; k > j; k--) arr[k] = arr[k - 1];   //依然是将后面的元素后移
        arr[j] = tmp;
    }
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    insertSort(arr, size);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}