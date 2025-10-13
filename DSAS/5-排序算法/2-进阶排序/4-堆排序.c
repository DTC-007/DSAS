#include <stdio.h>

void swap(int * a, int * b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//这个函数就是对start顶点位置的子树进行堆化
void makeHeap(int* arr, int start, int end) {
    while (start * 2 + 1 <= end) {    //如果有子树，就一直往下，因为调整之后有可能子树又不满足性质了
        int child = start * 2 + 1;    //因为下标是从0开始，所以左孩子下标就是i * 2 + 1，右孩子下标就是i * 2 + 2
        if(child + 1 <= end && arr[child] < arr[child + 1])   //如果存在右孩子且右孩子比左孩子大
            child++;    //那就直接看右孩子
        if(arr[child] > arr[start])   //如果上面选出来的孩子，比父结点大，那么就需要交换，大的换上去，小的换下来
            swap(&arr[child], &arr[start]);
        start = child;   //继续按照同样的方式前往孩子结点进行调整
    }
}

void heapSort(int arr[], int size) {
    for(int i= size/2 - 1; i >= 0; i--)   //我们首先需要对所有非叶子结点进行一次堆化操作，需要从最后一个到第一个，这里size/2计算的位置刚好是最后一个非叶子结点
        makeHeap(arr, i, size - 1);
    for (int i = size - 1; i > 0; i--) {   //接着我们需要一个一个把堆顶元素搬到后面，有序排列
        swap(&arr[i], &arr[0]);    //搬运实际上就是直接跟倒数第i个元素交换，这样，每次都能从堆顶取一个最大的过来
        makeHeap(arr, 0, i - 1);   //每次搬运完成后，因为堆底元素被换到堆顶了，所以需要再次对根结点重新进行堆化
    }
}

int main(){
    int arr[] = {3,44,38,5,47,15,36,26,27,2};
    int size = sizeof(arr) / sizeof(arr[0]);
    heapSort(arr, size);
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}