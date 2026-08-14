#include <cstdio>
#include <cstdlib>

#define MAXV 100

typedef struct {
	int numVertices, numEdges;
	char VerticeList[MAXV];
	int Edege[MAXV][MAXV];
} MGraph;


// 判断G是否存在唯一的拓扑序列，是则返回1，否则返回0（未做出）
int uniquely(MGraph G) {
    int n = G.numVertices;
    int indegree[MAXV] = {0};      // 入度数组
    int visited[MAXV] = {0};       // 标记是否已选
    // 1. 计算初始入度
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (G.Edege[i][j] != 0) {   // i→j 有边
                indegree[j]++;
            }
        }
    }
    // 2. 拓扑排序过程
    for (int k = 0; k < n; ++k) {
        int zeroCnt = 0;   // 入度为0且未访问的顶点数
        int idx = -1;      // 记录唯一候选
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && indegree[i] == 0) {
                zeroCnt++;
                idx = i;
                if (zeroCnt > 1) break;   // 已经出现多个，不唯一
            }
        }
        if (zeroCnt == 0 || zeroCnt > 1) return 0;   // 无入度为0的顶点 => 有环，无拓扑序列 ；多个可选顶点 => 拓扑序列不唯一
        // 唯一选择 idx
        visited[idx] = 1;
        // 删除该顶点，更新其所有后继的入度
        for (int j = 0; j < n; ++j) {
            if (G.Edege[idx][j] != 0) {
                indegree[j]--;
            }
        }
    }
    return 1;   // 全部顶点唯一地选取完毕
}