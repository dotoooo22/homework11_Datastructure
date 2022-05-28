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
	int visited[GSIZE];		//방문기록저장
}graph;

typedef struct Queue {
  int items[GSIZE];
  int front;
  int rear;
}queue;


graph* InitializeGraph(graph* g);		//그래프초기화

void InsertVertex(graph* g);			//정점추가
void InsertEdge(graph* g, int s, int a);	//점두개끼리 다리연결
void printGraph(graph* g);				//그래프 출력
void freeGraph(graph* g);				//메모리해제
void DFS(graph* g, int v);				//깊이우선탐색
void Initvisit(graph* g);				//방문기록초기화
void BFS(graph* g, queue* q, int v);				//너비우선탐색
void enqueue(queue* q, int value);		//큐에 줄서기
int dequeue(queue* q);				//큐에 앞거 나오기
queue* InitializeQueue(queue* q);	//큐초기화
void freeQueue(queue* q);		//메모리해제

int main()
{
	char command;
	int key, key2;
	graph* g = NULL;
	queue* q = NULL;
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
			q = InitializeQueue(q);
			break;
		case 'q': case 'Q':
			freeGraph(g);
			freeQueue(q);
			break;
		case 'v': case 'V':
			printf("vertex 수 : ");
			scanf("%d", &key);
			for(int i=0; i<key; i++) {
				InsertVertex(g);
			}
			break;
		case 'd': case 'D':
			printf("DFS시작 할 정점 : ");
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
			printf("BFS시작 할 정점 : ");
			scanf("%d", &key);
			BFS(g, q, key);
			Initvisit(g);	//방문기록초기화
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
	g->numV++;		//점갯수추가
}

void InsertEdge(graph* g, int s, int a) {
	if(s>=g->numV || a>=g->numV) {		//벌텍스범위에없음
		printf("벌텍스 범위 벗어남\n");
		return;
	}
	node* newNode = (node*)malloc(sizeof(node));
	newNode->vertex = a;
	newNode->next = g->adj_list[s];		//연결
	g->adj_list[s] = newNode;			//인접리스트에 추가
	//반대에서도 연결
	node* newNode2 = (node*)malloc(sizeof(node));
	newNode2->vertex = s;
	newNode2->next = g->adj_list[a];		//연결
	g->adj_list[a] = newNode2;			//인접리스트에 추가
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
void freeGraph(graph* g) {
	if(g!=NULL)
		free(g);
}
void freeQueue(queue* q) {
	if(q!=NULL)
		free(q);
}

void DFS(graph* g, int v) {
	
	node* list = g->adj_list[v];
	
	node* temp = list;
	g->visited[v] = 1;		//방문체크
	printf("visited [%d]  ", v);
	while(temp != NULL) {
		int connectedVertex = temp->vertex;		//연결된 정점을

		if(g->visited[connectedVertex] == 0) {		//방문안했으면 
			DFS(g, connectedVertex);				//방문하기
		}
		temp = temp->next;
	}
}
queue* InitializeQueue(queue* q) {
	if(q!=NULL) {
		free(q);
	}
	queue* temp = malloc(sizeof(queue));
	temp->front = -1;
	temp->rear = -1;
	return temp;
}
void enqueue(queue* q, int value) {
	if (q->rear == GSIZE - 1)		//queue자리없음
		return;
	else {
		if (q->front == -1)
		q->front = 0;
		q->rear++;
		q->items[q->rear] = value;
	}
}

int dequeue(queue* q) {
	int item;
	if (q->rear==-1) {		//큐 비어있음
		item = -1;
	} else {
		item = q->items[q->front];
		q->front++;
		if (q->front > q->rear) {		//rear랑 front랑 역전되면 되돌려놓기
		q->front = q->rear = -1;
		}
	}
	return item;
}

void BFS(graph* g, queue* q, int v) {
	g->visited[v] = 1;
	enqueue(q, v);		//시작점 큐에 추가

	while (q->rear!=-1) {		//큐가 비어있지 않을때 까지
		int currentVertex = dequeue(q);		//큐에서 하나 빼서 방문하기
		printf("Visited [%d]  ", currentVertex);

		node* temp = g->adj_list[currentVertex];

		while (temp!=NULL) {		//인접리스트끝까지
		int adjVertex = temp->vertex;

		if (g->visited[adjVertex] == 0) {		//방문안했으면
			g->visited[adjVertex] = 1;			//방문체크하고
			enqueue(q, adjVertex);					//큐에 추가
		}
		temp = temp->next;
		}
	}
}

void Initvisit(graph* g) {
	for(int i=0; i<GSIZE; i++) {	//방문기록초기화
		g->visited[i] = 0;
	}
}