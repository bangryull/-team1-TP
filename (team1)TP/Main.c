#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5000

typedef struct {
	int vn;       //���� ����
	int** matrix; //���� ���
} Graph;



Graph* NewGraph0(int max_vertex);//0���� �ʱ�ȭ�� �׷��� ����
Graph* NewGraphMax(int max_vertex);//MAX�� �ʱ�ȭ�� �׷��� ����

void DeleteGraph(Graph* graph);//�׷��� �޸� ����
void AddEdge(Graph* graph, int startvertex, int endvertex, int weight);//edge �߰�
void ViewGraph(Graph* graph);//����1 matrix ���
void ViewGraph2(Graph* graph);//����2 matrix ���
void printBFS(Graph* graph, int startvertex);//BFS ���
void printDFS(Graph* graph, int startvertex);//DFS ����Լ� ����
void DFS(Graph*, int vertex, int* visited);//DFS����Լ�
void Dijstra(Graph* graph, int startvertex);//Dijstra �˰��� ���

int main()
{
	// ���� 1
	printf("\n����1: �׷��� Ž�� �˰���\n\n");
	FILE* fp = fopen("input.txt", "r");
	int buffer[MAX] = { 0, };
	char str[MAX];
	int bufferindex = 0;

	if (fp == NULL)
	{
		perror("direction error");
		return 0;
	}
	while (fgets(str, sizeof(str), fp) != NULL) {
	
		char* ptr = strtok(str, " ");
		while (ptr != NULL) {
			buffer[bufferindex] = atoi(ptr);
			ptr = strtok(NULL, " ");
			bufferindex++;
		}
		buffer[bufferindex] = -1;
		bufferindex++;
	}
	// .txt���� �ҷ�����, enter�� -1�� ����

	buffer[bufferindex] = -2; //���� ������ ǥ��

	fclose(fp);
	
	int buffersize = bufferindex;
	int graphcount = 0;
	for (int i = 0; i < buffersize; i++) { //i�� ���۾��� ���ڸ� ���� �� ���� �ö�
		if (buffer[i] < -1) break;

		//�׷������� Msize �� �׷����� ũ��
		int Msize = buffer[i];
		i++;
		Graph* graph = NewGraph0(Msize);
		for (int j = 0; j < Msize; j++) {
			i++;
			int startvertex = buffer[i];
			while (buffer[i] > 0) {
				i++;
				int endvertex = buffer[i];
				AddEdge(graph, startvertex, endvertex, 1);
			}
		}

		graphcount++;
		printf("�׷��� [ %d ] \n", graphcount);
		
		printf("-----------------------------------\n");
		//���ǥ��
		ViewGraph(graph);
		
		printf("-----------------------------------\n");
		
		// print DFS
		printf("DFS(���� �켱 Ž��)\n");
		printDFS(graph, 1);
		printf("\n");

		// print BFS
		printf("BFS(���� �켱 Ž��)\n");
		printBFS(graph, 1);
		printf("\n");

		// �׷�������
		DeleteGraph(graph);
		printf("===================================\n");
		printf("\n\n");

	}
	


	// ���� 2
	printf("����2: �ִ� �Ÿ� ���ϱ� �˰���\n\n");
	FILE* fp2 = fopen("input2.txt", "r");
	int buffer2[MAX] = { 0, };
	char str2[MAX];
	int bufferindex2 = 0;

	if (fp2 == NULL)
	{
		perror("direction error");
		return 0;
	}
	while (fgets(str2, MAX, fp2) != NULL) {

		char* ptr2 = strtok(str2, " ");
		while (ptr2 != NULL) {
			buffer2[bufferindex2] = atoi(ptr2);
			ptr2 = strtok(NULL, " ");
			bufferindex2++;
		}
		buffer2[bufferindex2] = -1;
		bufferindex2++;
	}

	buffer2[bufferindex2] = -2;

	fclose(fp2);

	buffersize = bufferindex2;
	graphcount = 0;

	for (int i = 0; i < buffersize; i++)
	{
		if (buffer2[i] < -1) break;
		
		int Msize = buffer2[i];
		Graph* graph = NewGraphMax(Msize);
		
		
		i++;
		for (int j = 0; j < Msize; j++) {
			i++;
			int startvertex = buffer2[i];
			while (buffer2[i + 1] > 0) {
				int endvertex = buffer2[i + 1];
				int weight = buffer2[i + 2];
				AddEdge(graph, startvertex, endvertex, weight);
				i += 2;

			}
			i++;


		}
		graphcount++;
		printf("�׷��� [ %d ] \n", graphcount);
		printf("----------------------------------------------------\n");
		//��� ǥ��
		ViewGraph2(graph);
		printf("----------------------------------------------------\n");
		
		//Dijstra �˰��� ���
		Dijstra(graph, 1);
		printf("====================================================\n\n");

		DeleteGraph(graph);	
	}

}



Graph* NewGraph0(int max_vertex)
{
	int i = 0;
	Graph* graph = (Graph*)malloc(sizeof(Graph));//�׷��� �޸� ���� �Ҵ�
	graph->vn = max_vertex;//���� ���� ����
	graph->matrix = (int**)malloc(sizeof(int*) * max_vertex);//��Ʈ���� �޸� �Ҵ�
	for (i = 0; i < max_vertex; i++)
	{
		graph->matrix[i] = (int*)malloc(sizeof(int) * max_vertex);// row �޸� �Ҵ�
		memset(graph->matrix[i], 0, sizeof(int) * max_vertex);// 0���� �ʱ�ȭ
	}
	return graph;
}
Graph* NewGraphMax(int max_vertex)
{
	int i = 0;
	Graph* graph = (Graph*)malloc(sizeof(Graph));//�׷��� �޸� ���� �Ҵ�
	graph->vn = max_vertex;//�ִ� ���� ���� ����
	graph->matrix = (int**)malloc(sizeof(int*) * max_vertex);//��Ʈ���� �޸� �Ҵ�
	for (i = 0; i < max_vertex; i++)
	{
		graph->matrix[i] = (int*)malloc(sizeof(int) * max_vertex);//�׷��� row�޸� �Ҵ�
		memset(graph->matrix[i], 0x3f, sizeof(int) * max_vertex);//�޸� �ִ�(MAX)���� �ʱ�ȭ

	}
	return graph;
}

void DeleteGraph(Graph* graph)
{
	int i = 0;

	for (i = 0; i < graph->vn; i++)/
	{
		free(graph->matrix[i]);// row �޸� ����
	}
	free(graph->matrix);//�׷����� ������� �޸� ����
	free(graph);//�׷��� �޸� ����
}

void AddEdge(Graph* graph, int startvertex, int endvertex ,int weight)
{
	graph->matrix[start - 1][end - 1] = weight; //�������� txt�� vertex�� 1���� ���������� �迭�� 0���ͽ����ϱ⶧���� -1�� �Ͽ���.
}

void ViewGraph(Graph* graph)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < graph->vn; i++)
	{
		for (j = 0; j < graph->vn; j++)
		{
			printf("%2d ", graph->matrix[i][j]);
		}
		printf("\n");
	}
}
void ViewGraph2(Graph* graph)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < graph->vn; i++)
	{
		for (j = 0; j < graph->vn; j++)
		{
			printf("%10d ", graph->matrix[i][j]); 
		}
		printf("\n");
	}
}

void printBFS(Graph* graph, int startvertex) {
	int* visited = (int*)malloc(sizeof(int) * graph->vn); //�ִ� vn��ŭ visited �迭 ����
	memset(visited, 0, sizeof(int) * graph->vn);
	int queue[MAX];										  // queue ���� ����
	int front = 0, rear = 0, pop, i;

	printf("%d ", startvertex);

	queue[0] = startvertex;
	rear++;												//rear = queue�� ���ϳ�, front�� queue�迭�� ���� ��.
	visited[startvertex - 1] = 1;

	while (front < rear)
	{
		pop = queue[front];
		front++;
		for (i = 0; i < graph->vn; i++) {
			if (graph->matrix[pop - 1][i] == 1 && visited[i] == 0) {
				printf("%d ", i + 1);
				queue[rear] = i + 1;
				rear++;
				visited[i] = 1;
			}
		}
	}
	free(visited);
}

void printDFS(Graph* graph, int startvertex) {
	int* visited = (int*)malloc(sizeof(int) * graph->vn);
	memset(visited, 0, sizeof(int) * graph->vn);

	DFS(graph, startvertex - 1, visited);
	free(visited);

}

void DFS(Graph* graph, int vertex, int* visited) {
	visited[vertex] = 1;
	printf("%d ", vertex + 1);
	for (int i = 0; i <= graph->vn; i++) {
		if (graph->matrix[vertex][i] == 1 && visited[i] == 0) {
			DFS(graph, i, visited);
		}
	}
}

void Dijstra(Graph* graph, int startvertex) {
	int* dist = (int*)malloc(sizeof(int) * graph->vn);
	int* index = (int*)malloc(sizeof(int) * graph->vn);
	int* select = (int*)malloc(sizeof(int) * graph->vn);
	int min, p;

	memset(index, 0, sizeof(int) * graph->vn);
	memset(select, 0, sizeof(int) * graph->vn);

	p = startvertex - 1;
	select[p] = 1;

	for (int i = 0; i < graph->vn; i++) {
		dist[i] = graph->matrix[p][i];
	}

	// dist���� ����
	for (int i = 0; i < graph->vn - 1; i++) {
		// select next vertex (min ���� ���� index )
		min = MAX;
		for (int j = 0; j < graph->vn; j++) {
			if (!select[j] && min > dist[j]) {
				min = dist[j];
				p = j;
			}
		}
		select[p] = 1;
		// dist ����
		for (int j = 0; j < graph->vn; j++) {
			if (dist[j] > dist[p] + graph->matrix[p][j] && !select[j]) {
				dist[j] = dist[p] + graph->matrix[p][j];
				index[j] = p;
			}
		}

	}



	printf("�������� : [%d]\n", startvertex);

	for (int i = 0; i < graph->vn; i++) {
		if (i != startvertex - 1) {
			printf("���� [%d] :", i + 1);
			p = i;
			int flag = 1;
			int* temp = (int*)malloc(sizeof(int) * graph->vn);
			int count = 0;
			while (flag) {
				if (index[p] == 0) {
					temp[count] = 1;
					flag = 0;
				}
				else {
					temp[count] = index[p] + 1;
					p = index[p];
				}
				count++;
			}
			for (int j = count - 1; j >= 0; j--) {
				printf("%d - ", temp[j]);
			}
			printf("%d" ,i + 1);
			printf("   ���� : %d", dist[i]);
			printf("\n");
			free(temp);


		}

	}
	free(dist);
	free(select);
	free(index);
}
