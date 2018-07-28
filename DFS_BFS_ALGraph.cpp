#include <iostream>
/*邻接矩阵能够快速添加和删除边，但是当顶点的数目较少时会比较浪费空间
邻接表的优点是节约空间，但是关注顶点的度时可能需要遍历整个邻接表 --解决方法 逆邻接表*/
#define MAXVEX 100  /*最大顶点数*/
typedef char VertexType; /*顶点类型*/
typedef int EdgeType;    /*边上的权值类型*/

typedef struct EdgeNode{  //边表节点
	int adjvex;       //邻节点域
	EdgeType weight;  //权值
	struct EdgeNode *next; //下一个邻节点
}EdgeNode;

typedef struct  VextexNode{ //顶点表节点
	VertexType data;
	EdgeNode *firstEdge;
}VextexNode,AdjList[MAXVEX];

typedef struct{
	AdjList adjList;
	int numNodes, numEdges;
}GraphAdjList;

void CreateAdjList(GraphAdjList *Gp){
	int i,j,k;
	EdgeNode *pe = NULL;
	std::cout << "input numNodes and numEdges:" << std::endl;
	std::cin >> Gp->numNodes >>Gp->numEdges;

	for (int i = 0; i < Gp->numNodes; i++){
		std::cout << "input the data of the Nodes:" << std::endl;
		std::cin >> Gp->adjList[i].data;
		Gp->adjList[i].firstEdge = NULL;
	}

	for (int k = 0; k < Gp->numEdges; k++){
		std::cout << "输入边(vi,vj)的顶点序号i,j(空格分隔):" << std::endl;
		std::cin >> i >> j;
		pe = new EdgeNode();
		pe->adjvex= j;
		pe->next = Gp->adjList[i].firstEdge;
		Gp->adjList[i].firstEdge = pe;

		pe = new EdgeNode();
		pe->adjvex = i;
		pe->next = Gp->adjList[j].firstEdge;
		Gp->adjList[j].firstEdge = pe;

	}
}

int length = 10000000;
bool visited[MAXVEX] = {false};

//DFS 记录路径的两种方法
void DFS(GraphAdjList *Gp, int start);//深度优先遍历全部的节点

//如果路径不可达那么length的大小不会发生变化
void DFS_AdjList(GraphAdjList *Gp, int start, int end, int len){
	if(start == end){
		if(len < length){
			length = len;
		}
		return; 
	}
	visited[start] = true;
	EdgeNode *ptmp = Gp->adjList[start].firstEdge;
	while(NULL != ptmp){
		if(false == visited[ptmp->adjvex]){
			DFS_AdjList(Gp, ptmp->adjvex, end, len+1);
		}
		ptmp = ptmp->next;
	}
	return;
}

int DFS_AdjList1(GraphAdjList *Gp, int start, int end){
	if(start == end){
		return 0;
	}
	visited[start] = true;
	EdgeNode *ptmp = Gp->adjList[start].firstEdge;
	int len = 1000000;
	while(NULL != ptmp){
		if(false == visited[ptmp->adjvex]){
			//对于二叉树才能这样写
			int tmp =  DFS_AdjList1(Gp, ptmp->adjvex, end)+1;
			if(tmp < len){
				len = tmp;
			}
		}
		ptmp = ptmp->next;
	}
	return len;
}

void show_AdjList();

int main(){
	GraphAdjList G;
	CreateAdjList(&G);
	//DFS_AdjList(&G, 1, , 0);
	//std::cout << length << std::endl;
	int len = DFS_AdjList1(&G, 1, 3);
	std::cout << len << std::endl;
	return 0;
}