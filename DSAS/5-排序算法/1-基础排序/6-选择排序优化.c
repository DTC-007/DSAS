#include <stdio.h>

void swap(int * a, int * b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selectSort(int arr[], int size){
    int left = 0, right = size - 1;   //相当于左端和右端都是已经排好序的，中间是待排序的，所以说范围不断缩小
    while (left < right) {
        int min = left, max = right;
        for (int i = left; i <= right; i++) {
            if (arr[i] < arr[min]) min = i;   //同时找最小的和最大的
            if (arr[i] > arr[max]) max = i;
        }
        swap(&arr[max], &arr[right]);   //这里先把大的换到右边
        //注意大的换到右边之后，有可能被换出来的这个就是最小的，所以说需要判断一下
        //如果遍历完发现最小的就是当前右边排序的第一个元素
        //此时因为已经被换出来了，所以说需要将min改到换出来的那个位置
        if (min == right) min = max;
        swap(&arr[min], &arr[left]);   //接着把小的换到左边
        left++;    //这一轮完事之后，缩小范围
        right--;
    }
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    selectSort(arr, size);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}