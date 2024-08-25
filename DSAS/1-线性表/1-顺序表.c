#include <stdio.h>
#include <stdlib.h>

typedef int E;  //Ԫ�����;��� int Ϊ���ɣ����������

struct List {
    E * array;   //ָ��˳���ĵײ�����
    int capacity;   //���������
    int size;   //���е�Ԫ������
};
typedef struct List * ArrayList; //��Ϊ������ʵ�֣����Ծͽ� ArrayList������ֱ�ӽ� List ��ָ�������

//��ʼ��˳���
_Bool initList(ArrayList list){  //Ĭ�����е�˳����ʼ��С��Ϊ 10
    list->array = malloc(sizeof(int) * 10);   //ʹ�� malloc �������� 10 �� int ��С���ڴ�ռ䣬��Ϊ�ײ�����ʹ��
    if(list->array == NULL) return 0;  //��Ҫ�ж��������Ľ��Ϊ NULL �Ļ���ʾ�ڴ�ռ�����ʧ��
    list->capacity = 10;    //�����趨Ϊ 10
    list->size = 0;   //Ԫ������Ĭ��Ϊ 0
    return 1;   //��������·��� true Ҳ���� 1
}

//��ӡ������
void printList(ArrayList list){
    for (int i = 0; i < list->size; ++i)   //������ÿ��Ԫ�ض��ó�����ӡһ��
        printf("%d ", list->array[i]);
    printf("\n");
}

//˳������
//list ���Ǵ������ı�element ������Ҫ�����Ԫ�أ�index ���ǲ����λ�ã�ע��˳���� index �ǰ�λ�����ģ��� 1 ��ʼ��һ�㶼�ǵ� index ��Ԫ�أ�
_Bool insertList(ArrayList list, E element, int index){
    if(index < 1 || index > list->size + 1) return 0;   //����ڷǷ�λ�ò��룬���� 0 ��ʾ�������ִ��ʧ��
    if(list->size == list->capacity) {   //��� size �Ѿ��������������ˣ��϶��ǲ岻���ˣ���ô��ʱ����Ҫ������
        int newCapacity = list->capacity + (list->capacity >> 1);   //�����ȼ���һ���µ�������С������ȡ 1.5 ��ԭ����
        E * newArray = realloc(list->array, sizeof(E) * newCapacity);  //ʹ���µĺ��� realloc �������������ڴ�ռ�
        if(newArray == NULL) return 0;   //�������ʧ�ܣ���ô��ȷʵû�취�����ˣ�ֻ�ܷ��� 0 ��ʾ����ʧ����
        list->array = newArray;
        list->capacity = newCapacity;
    }
    for (int i = list->size; i > index - 1; i--)  //��ʹ�� for ѭ����������λ�ú�����Ԫ��ȫ��������һλ
        list->array[i] = list->array[i - 1];
    list->array[index - 1] = element;    //Ų��֮��λ�þ��ڳ����ˣ�ֱ���趨����
    list->size++;   //�����˲���֮���൱�ڶ���һ��Ԫ�أ��ǵ� size + 1
    return 1;   //����������� 1
}

//˳���ɾ��
//list ���Ǵ������ı�index ��Ҫɾ����Ԫ��λ��
_Bool deleteList(ArrayList list, int index){
    if (list->size == 0) return 0;
    if(index < 1 || index > list->size) return 0;
    for (int i = index - 1; i < list->size - 1; ++i)
        list->array[i] = list->array[i + 1];   //ʵ����ֻ��Ҫ���ΰѺ����Ԫ�ظ��ǵ�ǰһ������
    list->size--;   //�������� size - 1
    return 1;  //����������� 1
}

//��λ�û�ȡԪ��
E * getList(ArrayList list, int index){
    //���Ϊ�ձ���߳�����Χ�ͷ��� NULL
    if(list->size == 0 || index < 1 || index > list->size) return NULL;
    return &list->array[index - 1];
}

//����Ԫ��λ��
int findList(ArrayList list, E element){
    for (int i = 0; i < list->size; ++i) {   //һֱ����������ҵ��Ǿͷ���λ��
        if(list->array[i] == element) return i + 1;
    }
    return -1;
}

//˳�����
int sizeList(ArrayList list){
    return list->size;
}

int main() {
    struct List list;   //�����µĽṹ�����
    if(initList(&list)){   //������г�ʼ�������ʧ�ܾ�ֱ�ӽ���
        printf("��ʼ���ɹ���\n");
        //����Ԫ��
        for (int i = 1; i <= 20; ++i)
            insertList(&list, i, i);
        printf("%d\n", list.capacity);
        //ɾ��Ԫ��
        deleteList(&list, 20);
        printList(&list);
        printf("%d\n", * getList(&list, 9));
        printf("%d\n", findList(&list, 10));
        printf("%d", sizeList(&list));
    } else{
        printf("˳����ʼ��ʧ�ܣ��޷���������\n");
    }
}