#include <stdio.h>
#include <stdlib.h>
#define GSIZE 10		//���ؽ��ִ������
typedef struct Node {
	int vertex;
	struct Node* next;
}node;

typedef struct Graph {
	int numV;		//���ؽ�����
	node* adj_list[GSIZE];	//��������Ʈ
	int visited[GSIZE];		//�湮�������
}graph;

typedef struct Queue {
  int items[GSIZE];
  int front;
  int rear;
}queue;


graph* InitializeGraph(graph* g);		//�׷����ʱ�ȭ

void InsertVertex(graph* g);			//�����߰�
void InsertEdge(graph* g, int s, int a);	//���ΰ����� �ٸ�����
void printGraph(graph* g);				//�׷��� ���
void freeGraph(graph* g);				//�޸�����
void DFS(graph* g, int v);				//���̿켱Ž��
void Initvisit(graph* g);				//�湮����ʱ�ȭ
void BFS(graph* g, queue* q, int v);				//�ʺ�켱Ž��
void enqueue(queue* q, int value);		//ť�� �ټ���
int dequeue(queue* q);				//ť�� �հ� ������
queue* InitializeQueue(queue* q);	//ť�ʱ�ȭ
void freeQueue(queue* q);		//�޸�����

int main()
{
	char command;
	int key, key2;
	graph* g = NULL;
	queue* q = NULL;
	printf("[----- [������] [2021041021] -----]\n");
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
			printf("vertex �� : ");
			scanf("%d", &key);
			for(int i=0; i<key; i++) {
				InsertVertex(g);
			}
			break;
		case 'd': case 'D':
			printf("DFS���� �� ���� : ");
			scanf("%d", &key);
			DFS(g, key);
			Initvisit(g);	//�湮����ʱ�ȭ
			break;

		case 'e': case 'E':
			printf("Your v1 = ");
			scanf("%d", &key);
			printf("Your v2 = ");
			scanf("%d", &key2);
			InsertEdge(g, key, key2);
			break;
		case 'b': case 'B':
			printf("BFS���� �� ���� : ");
			scanf("%d", &key);
			BFS(g, q, key);
			Initvisit(g);	//�湮����ʱ�ȭ
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
		freeGraph(g);		//�������� �޸�����
	
	graph* temp = (graph*)malloc(sizeof(graph));		//�ʱ�ȭ
	temp->numV = 0;

	for(int v=0; v<GSIZE; v++) {
		temp->adj_list[v] = NULL;
		temp->visited[v] = 0;

	}
	return temp;
}
void InsertVertex(graph* g) {
	g->numV++;		//�������߰�
}

void InsertEdge(graph* g, int s, int a) {
	if(s>=g->numV || a>=g->numV) {		//���ؽ�����������
		printf("���ؽ� ���� ���\n");
		return;
	}
	node* newNode = (node*)malloc(sizeof(node));
	newNode->vertex = a;
	newNode->next = g->adj_list[s];		//����
	g->adj_list[s] = newNode;			//��������Ʈ�� �߰�
	//�ݴ뿡���� ����
	node* newNode2 = (node*)malloc(sizeof(node));
	newNode2->vertex = s;
	newNode2->next = g->adj_list[a];		//����
	g->adj_list[a] = newNode2;			//��������Ʈ�� �߰�
}

void printGraph(graph* g) {
	for(int i=0; i<g->numV; i++){
        node* p = g->adj_list[i];
        printf("Vertex[%d]�� ���� ����Ʈ",i);
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
	g->visited[v] = 1;		//�湮üũ
	printf("visited [%d]  ", v);
	while(temp != NULL) {
		int connectedVertex = temp->vertex;		//����� ������

		if(g->visited[connectedVertex] == 0) {		//�湮�������� 
			DFS(g, connectedVertex);				//�湮�ϱ�
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
	if (q->rear == GSIZE - 1)		//queue�ڸ�����
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
	if (q->rear==-1) {		//ť �������
		item = -1;
	} else {
		item = q->items[q->front];
		q->front++;
		if (q->front > q->rear) {		//rear�� front�� �����Ǹ� �ǵ�������
		q->front = q->rear = -1;
		}
	}
	return item;
}

void BFS(graph* g, queue* q, int v) {
	g->visited[v] = 1;
	enqueue(q, v);		//������ ť�� �߰�

	while (q->rear!=-1) {		//ť�� ������� ������ ����
		int currentVertex = dequeue(q);		//ť���� �ϳ� ���� �湮�ϱ�
		printf("Visited [%d]  ", currentVertex);

		node* temp = g->adj_list[currentVertex];

		while (temp!=NULL) {		//��������Ʈ������
		int adjVertex = temp->vertex;

		if (g->visited[adjVertex] == 0) {		//�湮��������
			g->visited[adjVertex] = 1;			//�湮üũ�ϰ�
			enqueue(q, adjVertex);					//ť�� �߰�
		}
		temp = temp->next;
		}
	}
}

void Initvisit(graph* g) {
	for(int i=0; i<GSIZE; i++) {	//�湮����ʱ�ȭ
		g->visited[i] = 0;
	}
}