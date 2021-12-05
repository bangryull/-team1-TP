#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5000

typedef struct {
	int vn;       //정점 개수
	int** matrix; //인접 행렬
} Graph;



Graph* NewGraph(int max_vertex);//그래프 동적 생성
void DeleteGraph(Graph* graph);//그래프 제거
void AddEdge(Graph* graph, int start, int goal);//edge 추가
void ViewGraph(Graph* graph);//matrix 출력
void printBFS(Graph* graph, int startvertex);
void printDFS(Graph* graph, int startvertex);
void DFS(Graph*, int vertex, int* visited);

int main()
{
	printf("\n과제1: 그래프 탐방 알고리즘\n\n");
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
	// .txt파일 불러오기, endter는 -1로 구분하였으며 문장의 끝은 NULL로 표기함.

	buffer[bufferindex] = -2; //파일 마지막 표시

	fclose(fp);
	
	int buffersize = bufferindex;
	int graphcount = 0;
	for (int i = 0; i < buffersize; i++) { //i는 버퍼안의 숫자를 읽을 때 마다 올라감
		if (buffer[i] < -1) break;

		//그래프생성
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
		printf("그래프 [ %d ] \n", graphcount);
		printf("-----------------------------------\n");
		//행렬표시
		ViewGraph(graph);
		printf("-----------------------------------\n");
		// print DFS
		printf("DFS(깊이 우선 탐색)\n");
		printDFS(graph, 1);
		printf("\n");

		// print BFS
		printf("BFS(넓이 우선 탐색)\n");
		printBFS(graph, 1);
		printf("\n");

		// 그래프제거
		DeleteGraph(graph);
		printf("===================================\n");
		printf("\n\n");

	}

	printf("과제2: 최단 거리 구하기 알고리즘\n\n");
	FILE* fp2 = fopen("input2.txt", "r");
	int buffer2[MAX] = { 0, };
	char str2[MAX];
	int bufferindex2 = 0;

	if (fp2 == NULL)
	{
		perror("direction error");
		return 0;
	}
	while (fgets(str2, sizeof(str2), fp2) != NULL) {

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
		int** arr; // 2차원배열 생성
		arr = (int**)malloc(sizeof(int*) * Msize);
		for (int i = 0; i < Msize; i++) {
			arr[i] = (int*)malloc(sizeof(int) * Msize);
		}
		for (int j = 0; j < Msize; j++) {
			for (int k = 0; k < Msize; k++) {
				arr[k][j] = 0;
			}
		}
		i++;
		for (int j = 0; j < Msize; j++) {
			i++;
			int startvertex = buffer2[i]-1;
			i++;
			while (buffer2[i] > 0) {
				int endvertex = buffer2[i]-1;
				i++;
				int distance = buffer2[i];
				arr[startvertex][endvertex] = distance;
				i++;
			}
		}
		graphcount++;
		printf("그래프 [ %d ] \n", graphcount);
		printf("-----------------------------------\n");
		//행렬 표시
		for (int j = 0; j < Msize; j++) {
			for (int k = 0; k < Msize; k++) {
				printf("%3d ", arr[j][k]);
			}
			printf("\n");
		}
		printf("-----------------------------------\n");

		for (int i = 0; i < Msize; i++) { // 2차원배열 해제
			free(arr[i]);
		}
		free(arr);
	}
}



Graph* NewGraph(int max_vertex)
{
	int i = 0;
	Graph* graph = (Graph*)malloc(sizeof(Graph));//그래프 메모리 동적 할당
	graph->vn = max_vertex;//최대 정점 개수 설정
	graph->matrix = (int**)malloc(sizeof(int*) * max_vertex);//매트릭스 메모리 할당
	for (i = 0; i < max_vertex; i++)
	{
		graph->matrix[i] = (int*)malloc(sizeof(int) * max_vertex);//매크릭스 [i-row] 메모리 할당
		memset(graph->matrix[i], 0, sizeof(int) * max_vertex);//메모리 0으로 초기화
	}
	return graph;
}

void DeleteGraph(Graph* graph)
{
	int i = 0;

	for (i = 0; i < graph->vn; i++)//최대 정점 개수만큼
	{
		free(graph->matrix[i]);//매트릭스 [i-row]  메모리 소멸
	}
	free(graph->matrix);//매트릭스 메모리 해제
	free(graph);//그래프 메모리 해제
}

void AddEdge(Graph* graph, int start, int goal)
{
	graph->matrix[start - 1][goal - 1] = 1;//간선설정
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
	memset(visited, 0, sizeof(int) * graph->vn);
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