#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//https://leetcode.cn/problems/kth-missing-positive-number/

int findKthPositive(int* arr, int arrSize, int k){
    int j = 1, i = 0;   //直接从第一个元素开始挨个找
    while (i < arrSize) {
        if(arr[i] != j) {
            if(--k == 0) return j;   //发现不相等时，相当于找到了一个数，k 自减，如果自减后为 0，那么说明已经找到第 K 个了，直接返回对应的 j
        } else{
            i++;  //相等的话就继续看下一个
        }
        j++;   //每一轮 j 自增，表示下一轮应该按顺序匹配的数
    }
    return j + k - 1;   //如果遍历完了都还没找到，那就按顺序直接算出下一个
}

//二分查找法
//int findKthPositive(int *arr, int arrSize, int k) {
//    if (arr[0] > k) return k;
//
//    int l = 0, r = arrSize;
//    while (l < r) {
//        int mid = (l + r) / 2;
//        if (arr[mid] - mid - 1 >= k) {
//            r = mid;
//        } else {
//            l = mid + 1;
//        }
//    }
//    return k - (arr[l - 1] - (l - 1) - 1) + arr[l - 1];
//}