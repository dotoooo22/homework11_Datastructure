#include <stdio.h>
#include <stdlib.h>
#define GSIZE 10		//벌텍스최대사이즈
typedef struct Node {
	int vertex;
	struct Node* next;
}node;

typedef struct Graph {
	int numV;		//벌텍스갯수
	node* adj_list[GSIZE];	//인접리스트
	int visited[GSIZE];		//방문저장
}graph;

graph* InitializeGraph(graph* g);		//그래프초기화
void InsertVertex(graph* g);			//정점추가
void InsertEdge(graph* g, int s, int a);	//점두개끼리 다리연결
void printGraph(graph* g);				//그래프 출력
void freeGraph(graph* g);				//메모리해제
void DFS(graph* g, int v);
void Initvisit(graph* g);


int main()
{
	char command;
	int key, key2;
	graph* g = NULL;
	printf("[----- [곽민정] [2021041021] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v           Insert Edge             = e \n");
		printf(" Depth First Search   = d           Breath First Search     = b \n");
		printf(" Print Graph          = p           Quit                    = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			g = InitializeGraph(g);
			break;
		case 'q': case 'Q':
			freeGraph(g);
			break;
		case 'v': case 'V':
			printf("vertex 수 : ");
			scanf("%d", &key);
			for(int i=0; i<key; i++) {
				InsertVertex(g);
			}
			break;
		case 'd': case 'D':
			printf("DFS할 정점 : ");
			scanf("%d", &key);
			DFS(g, key);
			Initvisit(g);	//방문기록초기화
			break;

		case 'e': case 'E':
			printf("Your v1 = ");
			scanf("%d", &key);
			printf("Your v2 = ");
			scanf("%d", &key2);
			InsertEdge(g, key, key2);
			break;
		case 'b': case 'B':
			//BFS
			break;

		case 'p': case 'P':
			printGraph(g);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;
}

graph* InitializeGraph(graph* g){
	if(g != NULL)
		freeGraph(g);		//머있으면 메모리해제
	
	graph* temp = (graph*)malloc(sizeof(graph));		//초기화
	temp->numV = 0;

	for(int v=0; v<GSIZE; v++) {
		temp->adj_list[v] = NULL;
		temp->visited[v] = 0;

	}
	return temp;
}
void InsertVertex(graph* g) {
	g->numV++;		//점갯수늘리기
}

void InsertEdge(graph* g, int s, int a) {
	node* newNode;
	if(s>=g->numV || a>=g->numV) {		//벌텍스범위에없음
		printf("벌텍스 범위 벗어남\n");
		return;
	}
	newNode = (node*)malloc(sizeof(node));
	newNode->vertex = a;
	newNode->next = g->adj_list[s];		//연결
	g->adj_list[s] = newNode;			//인접리스트에 추가
}

void printGraph(graph* g) {
	for(int i=0; i<g->numV; i++){
        node* p = g->adj_list[i];
        printf("Vertex[%d]의 인접 리스트",i);
        while(p!=NULL){
            printf("->%d",p->vertex);
            p=p->next;
        }
        printf("\n");
    }
}
void freeGraph(graph *g) {
	free(g);
}

void DFS(graph* g, int v) {
	
	node* list = g->adj_list[v];
	
	node* temp = list;
	g->visited[v] = 1;		//방문체크
	printf("visited [%d]", v);
	while(temp != NULL) {
		int connectedVertex = temp->vertex;		//연결된 정점을

		if(g->visited[connectedVertex] == 0) {		//방문안했으면 
			printf("->");
			DFS(g, connectedVertex);				//방문하기
		}
		temp = temp->next;
	}
}
void Initvisit(graph* g) {
	for(int i=0; i<GSIZE; i++) {	//방문기록초기화
		g->visited[i] = 0;
	}
}