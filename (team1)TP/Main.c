#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5000

typedef struct {
	int vn;       //정점 개수
	int** matrix; //인접 행렬
} Graph;

Graph* NewGraph0(int max_vertex);//0으로 초기화된 그래프 생성
Graph* NewGraphMax(int max_vertex);//MAX로 초기화된 그래프 생성

void DeleteGraph(Graph* graph);//그래프 메모리 해제
void AddEdge(Graph* graph, int startvertex, int endvertex, int weight);//edge 추가
void ViewGraph(Graph* graph);//과제1 matrix 출력
void ViewGraph2(Graph* graph);//과제2 matrix 출력
void printBFS(Graph* graph, int startvertex);//BFS 출력
void printDFS(Graph* graph, int startvertex);//DFS 재귀함수 세팅
void DFS(Graph*, int vertex, int* visited);//DFS재귀함수
void Dijstra(Graph* graph, int startvertex);//Dijstra 알고리즘 출력

int main()
{
	// 과제 1
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
	// .txt파일 불러오기, enter는 -1로 구분

	buffer[bufferindex] = -2; //파일 마지막 표시

	fclose(fp);
	
	int buffersize = bufferindex;
	int graphcount = 0;
	for (int i = 0; i < buffersize; i++) { //i는 버퍼안의 숫자를 읽을 때 마다 올라감
		if (buffer[i] < -1) break;

		
		int Msize = buffer[i];
		i++;
		//Msize크기 만큼의 0으로 초기화된 그래프 생성
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
	


	// 과제 2
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
	// .txt파일 불러오기, enter는 -1로 구분

	buffer2[bufferindex2] = -2; //파일 마지막 표시

	fclose(fp2);

	buffersize = bufferindex2;
	graphcount = 0;

	for (int i = 0; i < buffersize; i++)  //i는 버퍼안의 숫자를 읽을 때 마다 올라감
	{
		if (buffer2[i] < -1) break;
		//
		int Msize = buffer2[i];
		i++;
		//Msize크기 만큼의 MAX로 초기화된 그래프 생성
		Graph* graph = NewGraphMax(Msize);

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
		printf("그래프 [ %d ] \n", graphcount);
		printf("----------------------------------------------------\n");
		//행렬 표시
		ViewGraph2(graph);
		printf("----------------------------------------------------\n");
		
		//Dijstra 알고리즘 출력
		Dijstra(graph, 1);
		printf("====================================================\n\n");

		DeleteGraph(graph);	
	}

}



Graph* NewGraph0(int max_vertex)
{
	int i = 0;
	Graph* graph = (Graph*)malloc(sizeof(Graph));//그래프 메모리 동적 할당
	graph->vn = max_vertex;//정점 개수 설정
	graph->matrix = (int**)malloc(sizeof(int*) * max_vertex);//매트릭스 메모리 할당
	for (i = 0; i < max_vertex; i++)
	{
		graph->matrix[i] = (int*)malloc(sizeof(int) * max_vertex);// row 메모리 할당
		memset(graph->matrix[i], 0, sizeof(int) * max_vertex);// 0으로 초기화
	}
	return graph;
}
Graph* NewGraphMax(int max_vertex)
{
	int i = 0;
	Graph* graph = (Graph*)malloc(sizeof(Graph));//그래프 메모리 동적 할당
	graph->vn = max_vertex;//최대 정점 개수 설정
	graph->matrix = (int**)malloc(sizeof(int*) * max_vertex);//매트릭스 메모리 할당
	for (i = 0; i < max_vertex; i++)
	{
		graph->matrix[i] = (int*)malloc(sizeof(int) * max_vertex);//그래프 row메모리 할당
		memset(graph->matrix[i], 0x3f, sizeof(int) * max_vertex);//메모리 최댓값(MAX)으로 초기화

	}
	return graph;
}

void DeleteGraph(Graph* graph)
{
	int i = 0;

	for (i = 0; i < graph->vn; i++)
	{
		free(graph->matrix[i]);// row 메모리 해제
	}
	free(graph->matrix);//그래프의 인접행렬 메모리 해제
	free(graph);//그래프 메모리 해제
}

void AddEdge(Graph* graph, int startvertex, int endvertex ,int weight)
{
	graph->matrix[startvertex - 1][endvertex - 1] = weight; //간선설정 txt의 vertex는 1부터 시작하지만 배열은 0부터시작하기때문에 -1을 하였음.
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
	int* visited = (int*)malloc(sizeof(int) * graph->vn); //최대 vn만큼 visited 배열 생성
	memset(visited, 0, sizeof(int) * graph->vn);
	int queue[MAX];										  // queue 공간 생성
	int front = 0, rear = 0, pop, i;

	printf("%d ", startvertex);

	queue[0] = startvertex;
	rear++;												
	visited[startvertex - 1] = 1;

	while (front < rear)								//queue의 front값이 rear값을 추월할때 까지 반복
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
	int* visited = (int*)malloc(sizeof(int) * graph->vn); //DFS가 확인할 visited 배열 생성
	memset(visited, 0, sizeof(int) * graph->vn);		  //visited 배열 0으로 초기화

	DFS(graph, startvertex - 1, visited);
	free(visited);

}

void DFS(Graph* graph, int vertex, int* visited) {
	visited[vertex] = 1;							//방문표시
	printf("%d ", vertex + 1);						//방문vertex 출력
	for (int i = 0; i <= graph->vn; i++) {
		if (graph->matrix[vertex][i] == 1 && visited[i] == 0) {	// 재귀적으로 탐색
			DFS(graph, i, visited);
		}
	}
}

void Dijstra(Graph* graph, int startvertex) {
	int* dist = (int*)malloc(sizeof(int) * graph->vn);			//거리를 저장하는 배열공간 생성
	int* index = (int*)malloc(sizeof(int) * graph->vn);			//부모index를 저장하는 배열공간 생성
	int* select = (int*)malloc(sizeof(int) * graph->vn);		//최단거리가 고정된 vertex를 표시하는 배열생성
	int min, pos;

	memset(index, 0, sizeof(int) * graph->vn);					//배열 초기화
	memset(select, 0, sizeof(int) * graph->vn);

	pos = startvertex - 1;										//startvertex부터 시작
	select[pos] = 1;											

	for (int i = 0; i < graph->vn; i++) {						//startvertex기준으로 모든 vertex에 대한 거리갱신
		dist[i] = graph->matrix[pos][i];
	}


	for (int i = 0; i < graph->vn -1; i++) {					//dist의 갱신이 최대vertex숫자 -1 만큼 이루어짐 
		
		min = MAX;
		
		for (int j = 0; j < graph->vn; j++) {					//다음 vertex 선택 (선택되지 않은 vertex중에서 가장 작은 dist를 가진 vertex )
			if (!select[j] && min > dist[j]) {
				min = dist[j];
				pos = j;
			}
		}
		select[pos] = 1;										//선택된 vertex의 select 갱신
		
		for (int j = 0; j < graph->vn; j++) {
			if (dist[j] > dist[pos] + graph->matrix[pos][j] && !select[j]) {  // dist 갱신 ( select 되지 않고 거리가 더 짧으면 기존 dist 초기화)
				dist[j] = dist[pos] + graph->matrix[pos][j];
				index[j] = pos;												  // 부모 index를 저장
			}
		}

	}



	printf("시작정점 : [%d]\n", startvertex);

	for (int i = 0; i < graph->vn; i++) {
		if (i != startvertex - 1) {
			printf("정점 [%d] :", i + 1);							// 경로는 부모 index를 따라가기 때문에 출력이 역순으로 출력됨
			pos = i;												// 따라서 출력들을 배열에 담아 다시 역순으로 출력하여 제대로된 순서를 출력하는 코드.
			int flag = 1;											// while문 탈출 변수
			int* temp = (int*)malloc(sizeof(int) * graph->vn);		// 각 vertex들의 부모 index 저장공간
			int count = 0;											// 배열의 index변수
			while (flag) {
				if (index[pos] == startvertex-1) {					// startvertex의 부모는 없으므로 while문종료 flag 갱신
					temp[count] = startvertex;
					flag = 0;
				}
				else {												// count index를 늘려가며 경로저장
					temp[count] = index[pos] + 1;
					pos = index[pos];
				}
				count++;
			}
			for (int j = count - 1; j >= 0; j--) {					// 역순으로된 경로를 정방향으로 출력
				printf("%d - ", temp[j]);
			}
			printf("%d" ,i + 1);									// end vertex
			printf("   길이 : %d", dist[i]);						// 갱신된 dist배열출력
			printf("\n");
			free(temp);


		}

	}
	free(dist);
	free(select);
	free(index);
}
