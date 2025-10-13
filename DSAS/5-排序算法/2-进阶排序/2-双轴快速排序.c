#include <stdio.h>

void swap(int * a, int * b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void dualPivotQuickSort(int arr[], int start, int end) {
    if(start >= end) return;     //首先结束条件还是跟之前快速排序一样，因为不可能无限制地分下去，分到只剩一个或零个元素时该停止了
    if(arr[start] > arr[end])    //先把首尾两个基准进行比较，看看谁更大
        swap(&arr[start], &arr[end]);    //把大的换到后面去
    int pivot1 = arr[start], pivot2 = arr[end];    //取出两个基准元素
    int left = start, right = end, mid = left + 1;   //因为分了三块区域，此时需要三个指针来存放
    while (mid < right) {    //因为左边冲在最前面的是mid指针，所以说跟之前一样，只要小于right说明mid到right之间还有没排序的元素
        if(arr[mid] < pivot1)     //如果mid所指向的元素小于基准1，说明需要放到最左边
            swap(&arr[++left], &arr[mid++]);   //直接跟最左边交换，然后left和mid都向前移动
        else if (arr[mid] <= pivot2) {    //如果不小于基准1但是小于等于基准2，说明在中间
            mid++;   //因为mid本身就是在中间的，所以说只需要向前缩小范围就行
        } else {    //最后就是在右边的情况了
            while (arr[--right] > pivot2 && right > mid);  //此时我们需要找一个右边的位置来存放需要换过来的元素，注意先移动右边指针
            if(mid >= right) break;   //要是把剩余元素找完了都还没找到一个比基准2小的，那么就直接结束，本轮排序已经完成了
            swap(&arr[mid], &arr[right]);   //如果还有剩余元素，说明找到了，直接交换right指针和mid指针所指元素
        }
    }
    swap(&arr[start], &arr[left]);    //最后基准1跟left交换位置，正好左边的全部比基准1小
    swap(&arr[end], &arr[right]);     //最后基准2跟right交换位置，正好右边的全部比基准2大
    dualPivotQuickSort(arr, start, left - 1);    //继续对三个区域再次进行双轴快速排序
    dualPivotQuickSort(arr, left + 1, right - 1);
    dualPivotQuickSort(arr, right + 1, end);
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    dualPivotQuickSort(arr, 0,size-1);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}