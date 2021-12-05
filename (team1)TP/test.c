#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5000

typedef struct {
	int vn;       //���� ����
	int** matrix; //���� ���
} Graph;

Graph* NewGraph(int max_vertex);//�׷��� ���� ����
void DeleteGraph(Graph* graph);//�׷��� ����
void AddEdge(Graph* graph, int start, int goal);//edge �߰�
void ViewGraph(Graph* graph);//matrix ���
void printBFS(Graph* graph, int startvertex);
void printDFS(Graph* graph, int startvertex);
void DFS(Graph*, int vertex, int* visited);

int main()
{
	FILE* fp;
	fopen_s(&fp, "C:\input.txt", "r");
	int buffer[MAX] = { 0, };
	char str[MAX];
	int bufferindex = 0;

	if (fp == NULL)
	{
		perror("direction error");
		return 0;
	}
	while (fgets(str, sizeof(str), fp) != NULL) {
		str[strlen(str) - 1] = '\0';
		char* ptr = strtok(str, " ");
		while (ptr != NULL) {
			buffer[bufferindex] = atoi(ptr);
			ptr = strtok(NULL, " ");
			bufferindex++;
		}
		buffer[bufferindex] = -1;
		bufferindex++;
	}
	// .txt���� �ҷ�����, endter�� -1�� �����Ͽ����� ������ ���� NULL�� ǥ����.

	buffer[bufferindex] = NULL;

	fclose(fp);

	int buffersize = bufferindex;
	int graphcount = 0;
	for (int i = 0; i < buffersize; i++) {
		if (buffer[i] == NULL) break;

		//�׷�������
		int Msize = buffer[i];
		i++;
		Graph* graph = NewGraph(Msize);
		for (int j = 0; j < Msize; j++) {
			i++;
			int startvertex = buffer[i];
			while (buffer[i] > 0) {
				i++;
				int endvertex = buffer[i];
				AddEdge(graph, startvertex, endvertex);
			}
		}

		graphcount++;
		printf("�׷��� [ %d ] \n", graphcount);
		printf("-----------------------------------\n");
		//���ǥ��
		ViewGraph(graph);
		printf("-----------------------------------\n");
		// print DFS
		printf("DFS\n");
		printDFS(graph, 1);
		printf("\n");

		// print BFS
		printf("BFS\n");
		printBFS(graph, 1);
		printf("\n");

		// �׷�������
		DeleteGraph(graph);
		printf("===================================\n");
		printf("\n\n");

	}


	return 0;
}



Graph* NewGraph(int max_vertex)
{
	int i = 0;
	Graph* graph = (Graph*)malloc(sizeof(Graph));//�׷��� �޸� ���� �Ҵ�
	graph->vn = max_vertex;//�ִ� ���� ���� ����
	graph->matrix = (int**)malloc(sizeof(int*) * max_vertex);//��Ʈ���� �޸� �Ҵ�
	for (i = 0; i < max_vertex; i++)
	{
		graph->matrix[i] = (int*)malloc(sizeof(int) * max_vertex);//��ũ���� [i-row] �޸� �Ҵ�
		memset(graph->matrix[i], 0, sizeof(int) * max_vertex);//�޸� 0���� �ʱ�ȭ
	}
	return graph;
}
void DeleteGraph(Graph* graph)
{
	int i = 0;

	for (i = 0; i < graph->vn; i++)//�ִ� ���� ������ŭ
	{
		free(graph->matrix[i]);//��Ʈ���� [i-row]  �޸� �Ҹ�
	}
	free(graph->matrix);//��Ʈ���� �޸� ����
	free(graph);//�׷��� �޸� ����
}
void AddEdge(Graph* graph, int start, int goal)
{
	graph->matrix[start - 1][goal - 1] = 1;//��������
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
void printBFS(Graph* graph, int startvertex) {
	int* visited = (int*)malloc(sizeof(int) * graph->vn);
	for (int i = 0; i < graph->vn; i++) {
		visited[i] = 0;
	}
	int queue[MAX];
	int front = 0, rear = 0, pop, i;

	printf("%d ", startvertex);

	queue[0] = startvertex;
	rear++;
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
	for (int i = 0; i < graph->vn; i++) {
		visited[i] = 0;
	}

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