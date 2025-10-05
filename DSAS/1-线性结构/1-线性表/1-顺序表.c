#include <stdio.h>
#include <stdlib.h>

typedef int E;  //元素类型就用 int 为例吧，先起个别名

struct List {
    E * array;   //指向顺序表的底层数组
    int capacity;   //数组的容量
    int size;   //表中的元素数量
};
typedef struct List * ArrayList; //因为是数组实现，所以就叫 ArrayList，这里直接将 List 的指针起别名

//初始化顺序表
_Bool initList(ArrayList list){  //默认所有的顺序表初始大小都为 10
    list->array = malloc(sizeof(int) * 10);   //使用 malloc 函数申请 10 个 int 大小的内存空间，作为底层数组使用
    if(list->array == NULL) return 0;  //需要判断如果申请的结果为 NULL 的话表示内存空间申请失败
    list->capacity = 10;    //容量设定为 10
    list->size = 0;   //元素数量默认为 0
    return 1;   //正常情况下返回 true 也就是 1
}

//打印表数据
void printList(ArrayList list){
    for (int i = 0; i < list->size; ++i)   //表里面每个元素都拿出来打印一次
        printf("%d ", list->array[i]);
    printf("\n");
}

//顺序表插入
//list 就是待操作的表，element 就是需要插入的元素，index 就是插入的位置（注意顺序表的 index 是按位序计算的，从 1 开始，一般都是第 index 个元素）
_Bool insertList(ArrayList list, E element, int index){
    if(index < 1 || index > list->size + 1) return 0;   //如果在非法位置插入，返回 0 表示插入操作执行失败
    if(list->size == list->capacity) {   //如果 size 已经到达最大的容量了，肯定是插不进了，那么此时就需要扩容了
        int newCapacity = list->capacity + (list->capacity >> 1);   //我们先计算一下新的容量大小，这里取 1.5 倍原长度
        E * newArray = realloc(list->array, sizeof(E) * newCapacity);  //使用新的函数 realloc 重新申请更大的内存空间
        if(newArray == NULL) return 0;   //如果申请失败，那么就确实没办法插入了，只能返回 0 表示插入失败了
        list->array = newArray;
        list->capacity = newCapacity;
    }
    for (int i = list->size; i > index - 1; i--)  //先使用 for 循环将待插入位置后续的元素全部丢到后一位
        list->array[i] = list->array[i - 1];
    list->array[index - 1] = element;    //挪完之后，位置就腾出来了，直接设定即可
    list->size++;   //别忘了插入之后相当于多了一个元素，记得 size + 1
    return 1;   //正常情况返回 1
}

//顺序表删除
//list 就是待操作的表，index 是要删除的元素位序
_Bool deleteList(ArrayList list, int index){
    if (list->size == 0) return 0;
    if(index < 1 || index > list->size) return 0;
    for (int i = index - 1; i < list->size - 1; ++i)
        list->array[i] = list->array[i + 1];   //实际上只需要依次把后面的元素覆盖到前一个即可
    list->size--;   //最后别忘了 size - 1
    return 1;  //正常情况返回 1
}

//按位置获取元素
E * getList(ArrayList list, int index){
    //如果为空表或者超出范围就返回 NULL
    if(list->size == 0 || index < 1 || index > list->size) return NULL;
    return &list->array[index - 1];
}

//查找元素位置
int findList(ArrayList list, E element){
    for (int i = 0; i < list->size; ++i) {   //一直遍历，如果找到那就返回位序
        if(list->array[i] == element) return i + 1;
    }
    return -1;
}

//顺序表长度
int sizeList(ArrayList list){
    return list->size;
}

int main() {
    struct List list;   //创建新的结构体变量
    if(initList(&list)){   //对其进行初始化，如果失败就直接结束
        printf("初始化成功！\n");
        //插入元素
        for (int i = 1; i <= 20; ++i)
            insertList(&list, i, i);
        printf("%d\n", list.capacity);
        //删除元素
        deleteList(&list, 20);
        printList(&list);
        printf("%d\n", * getList(&list, 9));
        printf("%d\n", findList(&list, 10));
        printf("%d", sizeList(&list));
    } else{
        printf("顺序表初始化失败，无法启动程序！\n");
    }
}