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
	int visited[GSIZE];		//�湮����
}graph;

graph* InitializeGraph(graph* g);		//�׷����ʱ�ȭ
void InsertVertex(graph* g);			//�����߰�
void InsertEdge(graph* g, int s, int a);	//���ΰ����� �ٸ�����
void printGraph(graph* g);				//�׷��� ���
void freeGraph(graph* g);				//�޸�����
void DFS(graph* g, int v);
void Initvisit(graph* g);


int main()
{
	char command;
	int key, key2;
	graph* g = NULL;
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
			break;
		case 'q': case 'Q':
			freeGraph(g);
			break;
		case 'v': case 'V':
			printf("vertex �� : ");
			scanf("%d", &key);
			for(int i=0; i<key; i++) {
				InsertVertex(g);
			}
			break;
		case 'd': case 'D':
			printf("DFS�� ���� : ");
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
	g->numV++;		//�������ø���
}

void InsertEdge(graph* g, int s, int a) {
	node* newNode;
	if(s>=g->numV || a>=g->numV) {		//���ؽ�����������
		printf("���ؽ� ���� ���\n");
		return;
	}
	newNode = (node*)malloc(sizeof(node));
	newNode->vertex = a;
	newNode->next = g->adj_list[s];		//����
	g->adj_list[s] = newNode;			//��������Ʈ�� �߰�
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
void freeGraph(graph *g) {
	free(g);
}

void DFS(graph* g, int v) {
	
	node* list = g->adj_list[v];
	
	node* temp = list;
	g->visited[v] = 1;		//�湮üũ
	printf("visited [%d]", v);
	while(temp != NULL) {
		int connectedVertex = temp->vertex;		//����� ������

		if(g->visited[connectedVertex] == 0) {		//�湮�������� 
			printf("->");
			DFS(g, connectedVertex);				//�湮�ϱ�
		}
		temp = temp->next;
	}
}
void Initvisit(graph* g) {
	for(int i=0; i<GSIZE; i++) {	//�湮����ʱ�ȭ
		g->visited[i] = 0;
	}
}