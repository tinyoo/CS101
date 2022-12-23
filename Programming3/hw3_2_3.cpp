#include <iostream>

using namespace std;

class MatrixUDG {
    #define MAX    100
    #define INF    (~(0x1<<31))        // 无穷大(即0X7FFFFFFF)
    private:
        char mVexs[MAX];    // 顶点集合
        int mVexNum;             // 顶点数
        int mEdgNum;             // 边数
        int mMatrix[MAX][MAX];   // 邻接矩阵

    public:
        // 创建图(自己输入数据)
        MatrixUDG();
        // 创建图(用已提供的矩阵)
        //MatrixUDG(char vexs[], int vlen, char edges[][2], int elen);
        MatrixUDG(char vexs[], int vlen, int matrix[][9]);
        ~MatrixUDG();

        // 深度优先搜索遍历图
        void DFS();
        // 广度优先搜索（类似于树的层次遍历）
        void BFS();
        // prim最小生成树(从start开始生成最小生成树)
        void prim(int start);
        // 克鲁斯卡尔（Kruskal)最小生成树
        void kruskal();
        // Dijkstra最短路径
        void dijkstra(int vs, int vexs[], int dist[]);
        // Floyd最短路径
        void floyd(int path[][MAX], int dist[][MAX]);
        // 打印矩阵队列图
        void print();

    private:
        // 读取一个输入字符
        char readChar();
        // 返回ch在mMatrix矩阵中的位置
        int getPosition(char ch);
        // 返回顶点v的第一个邻接顶点的索引，失败则返回-1
        int firstVertex(int v);
        // 返回顶点v相对于w的下一个邻接顶点的索引，失败则返回-1
        int nextVertex(int v, int w);
        // 深度优先搜索遍历图的递归实现
        void DFS(int i, int *visited);
        // 获取图中的边
        EData* getEdges();
        // 对边按照权值大小进行排序(由小到大)
        void sortEdges(EData* edges, int elen);
        // 获取i的终点
        int getEnd(int vends[], int i);
};

/*
 * floyd最短路径。
 * 即，统计图中各个顶点间的最短路径。
 *
 * 参数说明：
 *     path -- 路径。path[i][j]=k表示，"顶点i"到"顶点j"的最短路径会经过顶点k。
 *     dist -- 长度数组。即，dist[i][j]=sum表示，"顶点i"到"顶点j"的最短路径的长度是sum。
 */
void MatrixUDG::floyd(int path[][MAX], int dist[][MAX])
{
    int i,j,k;
    int tmp;

    // 初始化
    for (i = 0; i < mVexNum; i++)
    {
        for (j = 0; j < mVexNum; j++)
        {
            dist[i][j] = mMatrix[i][j];    // "顶点i"到"顶点j"的路径长度为"i到j的权值"。
            path[i][j] = j;                // "顶点i"到"顶点j"的最短路径是经过顶点j。
        }
    }

    // 计算最短路径
    for (k = 0; k < mVexNum; k++)
    {
        for (i = 0; i < mVexNum; i++)
        {
            for (j = 0; j < mVexNum; j++)
            {
                // 如果经过下标为k顶点路径比原两点间路径更短，则更新dist[i][j]和path[i][j]
                tmp = (dist[i][k]==INF || dist[k][j]==INF) ? INF : (dist[i][k] + dist[k][j]);
                if (dist[i][j] > tmp)
                {
                    // "i到j最短路径"对应的值设，为更小的一个(即经过k)
                    dist[i][j] = tmp;
                    // "i到j最短路径"对应的路径，经过k
                    path[i][j] = path[i][k];
                }
            }
        }
    }

    // 打印floyd最短路径的结果
    cout << "floyd: " << endl;
    for (i = 0; i < mVexNum; i++)
    {
        for (j = 0; j < mVexNum; j++)
            cout << setw(2) << dist[i][j] << "  ";
        cout << endl;
    }
}