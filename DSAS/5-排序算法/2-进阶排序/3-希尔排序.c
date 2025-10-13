#include <stdio.h>

void shellSort(int arr[], int size){
    int delta = size / 2;
    while (delta >= 1) {
        //这里依然是使用之前的插入排序，不过此时需要考虑分组了
        for (int i = delta; i < size; ++i) {   //我们需要从delta开始，因为前delta个组的第一个元素默认是有序状态
            int j = i, tmp = arr[i];   //这里依然是把待插入的先抽出来
            while (j >= delta && arr[j - delta] > tmp) {
                //注意这里比较需要按步长往回走，所以说是j - delta，此时j必须大于等于delta才可以，如果j - delta小于0说明前面没有元素了
                arr[j] = arr[j - delta];
                j -= delta;
            }
            arr[j] = tmp;
        }
        delta /= 2;    //分组插排完事之后，重新计算步长
    }
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    shellSort(arr, size);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}