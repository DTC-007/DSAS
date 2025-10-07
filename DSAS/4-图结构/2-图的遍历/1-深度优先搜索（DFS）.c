#include <stdlib.h>
#include <stdio.h>

#define MaxVertex 6

typedef char E;

typedef struct Node {   //结点和头结点分开定义，普通结点记录邻接顶点信息
    int nextVertex;     //邻接顶点编号
    struct Node * next;
} * Node;

struct HeadNode {   //头结点记录元素
    E element;
    struct Node * next;
};

typedef struct AdjacencyGraph {
    int vertexCount;   //顶点数
    int edgeCount;     //边数
    struct HeadNode vertex[MaxVertex];
} * Graph;

Graph create(){   //创建时，我们可以指定图中初始有多少个结点
    Graph graph = malloc(sizeof(struct AdjacencyGraph));
    graph->vertexCount = graph->edgeCount = 0;
    return graph;   //头结点数组一开始可以不用管
}

void addVertex(Graph graph, E element){
    if(graph->vertexCount >= MaxVertex) return;   //跟之前一样
    graph->vertex[graph->vertexCount].element = element;   //添加新结点时，再来修改也行
    graph->vertex[graph->vertexCount].next = NULL;
    graph->vertexCount++;
}

void addEdge(Graph graph, int a, int b){
    Node node = graph->vertex[a].next;
    Node newNode = malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->nextVertex = b;
    if(!node) {    //如果头结点下一个都没有，那么直接连上去
        graph->vertex[a].next = newNode;
    } else {   //否则说明当前顶点已经连接了至少一个其他顶点了，有可能会出现已经连接过的情况，所以说要特别处理一下
        do {
            if(node->nextVertex == b) return free(newNode);   //如果已经连接了对应的顶点，那么直接返回
            if(node->next) node = node->next;   //否则继续向后遍历
            else break;   //如果没有下一个了，那就找到最后一个结点了，直接结束
        } while (1);
        node->next = newNode;
    }
    graph->edgeCount++;   //边数计数+1
}

void printGraph(Graph graph){
    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("%d | %c", i, graph->vertex[i].element);
        Node node = graph->vertex[i].next;
        while (node) {
            printf(" -> %d", node->nextVertex);
            node = node->next;
        }
        putchar('\n');
    }
}

/**
 * 深度优先搜索算法
 * @param graph 图
 * @param startVertex 起点顶点下标
 * @param targetVertex 目标顶点下标
 * @param visited 已到达过的顶点数组
 * @return 搜索结果，如果找到返回 1，没找到返回 0
 */
_Bool dfs(Graph graph, int startVertex, int targetVertex, int * visited){
    visited[startVertex] = 1;   //走过之后一定记得 mark 一下
    printf("%c -> ", graph->vertex[startVertex].element);   //打印当前顶点值
    if(startVertex == targetVertex) return 1;   //打印如果当前顶点值就是要找的顶点，直接返回
    Node node = graph->vertex[startVertex].next;   //遍历当前顶点所有的分支
    while (node) {
        if(!visited[node->nextVertex])   //如果已经到过（有可能是走其他分支到过，或是回头路）那就不继续了
            if(dfs(graph, node->nextVertex, targetVertex, visited))
            //没到过就继续往下走，这里将 startVertex 设定为对于分支的下一个顶点，按照同样的方式去寻找
                return 1;    //如果查找成功，直接返回 1，不用再看其他分支了
        node = node->next;
    }
    return 0;   //while 结束那肯定是没找到了，直接返回 0
}

int main(){
    Graph graph = create();
    for (int c = 'A'; c <= 'F' ; ++c)
        addVertex(graph, (char) c);
    addEdge(graph, 0, 1);   //A -> B
    addEdge(graph, 1, 2);   //B -> C
    addEdge(graph, 1, 3);   //B -> D
    addEdge(graph, 1, 4);   //D -> E
    addEdge(graph, 4, 5);   //E -> F

    printGraph(graph);

    int arr[graph->vertexCount];
    for (int i = 0; i < graph->vertexCount; ++i) arr[i] = 0;
    printf("\n%d", dfs(graph, 0, 5, arr));
}
