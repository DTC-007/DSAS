#include <stdlib.h>
#include <stdio.h>

#define MaxVertex 5     //图中最大结点数

typedef char E;   //顶点存放的数据类型

typedef struct MatrixGraph {
    int vertexCount;   //顶点数
    int edgeCount;     //边数
    int matrix[MaxVertex][MaxVertex];   //邻接矩阵
    E data[MaxVertex];    //各个顶点对应的数据
} * Graph;

Graph create(){   //创建时，我们可以指定图中初始有多少个结点
    Graph graph = malloc(sizeof(struct MatrixGraph));
    graph->vertexCount = 0;    //顶点和边数肯定一开始是 0
    graph->edgeCount = 0;
    for (int i = 0; i < MaxVertex; ++i)    //记得把矩阵每个位置都置为 0
        for (int j = 0; j < MaxVertex; ++j)
            graph->matrix[i][j] = 0;
    return graph;
}

void addVertex(Graph graph, E element){
    if(graph->vertexCount >= MaxVertex) return;
    graph->data[graph->vertexCount++] = element;   //添加新元素
}

void addEdge(Graph graph, int a, int b){   //添加几号顶点到几号顶点的边
    if(graph->matrix[a][b] == 0) {
        graph->matrix[a][b] = 1;  //注意如果是无向图的话，需要 [a][b] 和 [b][a] 都置为 1
        graph->edgeCount++;
    }
}

void printGraph(Graph graph){
    for (int i = -1; i < graph->vertexCount; ++i) {
        for (int j = -1; j < graph->vertexCount; ++j) {
            if(j == -1)
                printf("%c", 'A' + i);
            else if(i == -1)
                printf("%3c", 'A' + j);
            else
                printf("%3d", graph->matrix[i][j]);
        }
        putchar('\n');
    }
}

int main(){
    Graph graph = create();   //创建一个图
    for (int c = 'A'; c <= 'D' ; ++c)
        addVertex(graph, (char) c);
    addEdge(graph, 0, 1);   //A -> B
    addEdge(graph, 1, 2);   //B -> C
    addEdge(graph, 2, 3);   //C -> D
    addEdge(graph, 3, 0);   //D -> A
    addEdge(graph, 2, 0);   //C -> A

    printGraph(graph);
}