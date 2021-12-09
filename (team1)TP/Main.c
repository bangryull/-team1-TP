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

		
		int Msize = buffer[i];
		i++;
		//Msizeũ�� ��ŭ�� 0���� �ʱ�ȭ�� �׷��� ����
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
	// .txt���� �ҷ�����, enter�� -1�� ����

	buffer2[bufferindex2] = -2; //���� ������ ǥ��

	fclose(fp2);

	buffersize = bufferindex2;
	graphcount = 0;

	for (int i = 0; i < buffersize; i++)  //i�� ���۾��� ���ڸ� ���� �� ���� �ö�
	{
		if (buffer2[i] < -1) break;
		//
		int Msize = buffer2[i];
		i++;
		//Msizeũ�� ��ŭ�� MAX�� �ʱ�ȭ�� �׷��� ����
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

	for (i = 0; i < graph->vn; i++)
	{
		free(graph->matrix[i]);// row �޸� ����
	}
	free(graph->matrix);//�׷����� ������� �޸� ����
	free(graph);//�׷��� �޸� ����
}

void AddEdge(Graph* graph, int startvertex, int endvertex ,int weight)
{
	graph->matrix[startvertex - 1][endvertex - 1] = weight; //�������� txt�� vertex�� 1���� ���������� �迭�� 0���ͽ����ϱ⶧���� -1�� �Ͽ���.
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
	rear++;												
	visited[startvertex - 1] = 1;

	while (front < rear)								//queue�� front���� rear���� �߿��Ҷ� ���� �ݺ�
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
	int* visited = (int*)malloc(sizeof(int) * graph->vn); //DFS�� Ȯ���� visited �迭 ����
	memset(visited, 0, sizeof(int) * graph->vn);		  //visited �迭 0���� �ʱ�ȭ

	DFS(graph, startvertex - 1, visited);
	free(visited);

}

void DFS(Graph* graph, int vertex, int* visited) {
	visited[vertex] = 1;							//�湮ǥ��
	printf("%d ", vertex + 1);						//�湮vertex ���
	for (int i = 0; i <= graph->vn; i++) {
		if (graph->matrix[vertex][i] == 1 && visited[i] == 0) {	// ��������� Ž��
			DFS(graph, i, visited);
		}
	}
}

void Dijstra(Graph* graph, int startvertex) {
	int* dist = (int*)malloc(sizeof(int) * graph->vn);			//�Ÿ��� �����ϴ� �迭���� ����
	int* index = (int*)malloc(sizeof(int) * graph->vn);			//�θ�index�� �����ϴ� �迭���� ����
	int* select = (int*)malloc(sizeof(int) * graph->vn);		//�ִܰŸ��� ������ vertex�� ǥ���ϴ� �迭����
	int min, pos;

	memset(index, 0, sizeof(int) * graph->vn);					//�迭 �ʱ�ȭ
	memset(select, 0, sizeof(int) * graph->vn);

	pos = startvertex - 1;										//startvertex���� ����
	select[pos] = 1;											

	for (int i = 0; i < graph->vn; i++) {						//startvertex�������� ��� vertex�� ���� �Ÿ�����
		dist[i] = graph->matrix[pos][i];
	}


	for (int i = 0; i < graph->vn -1; i++) {					//dist�� ������ �ִ�vertex���� -1 ��ŭ �̷���� 
		
		min = MAX;
		
		for (int j = 0; j < graph->vn; j++) {					//���� vertex ���� (���õ��� ���� vertex�߿��� ���� ���� dist�� ���� vertex )
			if (!select[j] && min > dist[j]) {
				min = dist[j];
				pos = j;
			}
		}
		select[pos] = 1;										//���õ� vertex�� select ����
		
		for (int j = 0; j < graph->vn; j++) {
			if (dist[j] > dist[pos] + graph->matrix[pos][j] && !select[j]) {  // dist ���� ( select ���� �ʰ� �Ÿ��� �� ª���� ���� dist �ʱ�ȭ)
				dist[j] = dist[pos] + graph->matrix[pos][j];
				index[j] = pos;												  // �θ� index�� ����
			}
		}

	}



	printf("�������� : [%d]\n", startvertex);

	for (int i = 0; i < graph->vn; i++) {
		if (i != startvertex - 1) {
			printf("���� [%d] :", i + 1);							// ��δ� �θ� index�� ���󰡱� ������ ����� �������� ��µ�
			pos = i;												// ���� ��µ��� �迭�� ��� �ٽ� �������� ����Ͽ� ����ε� ������ ����ϴ� �ڵ�.
			int flag = 1;											// while�� Ż�� ����
			int* temp = (int*)malloc(sizeof(int) * graph->vn);		// �� vertex���� �θ� index �������
			int count = 0;											// �迭�� index����
			while (flag) {
				if (index[pos] == startvertex-1) {					// startvertex�� �θ�� �����Ƿ� while������ flag ����
					temp[count] = startvertex;
					flag = 0;
				}
				else {												// count index�� �÷����� �������
					temp[count] = index[pos] + 1;
					pos = index[pos];
				}
				count++;
			}
			for (int j = count - 1; j >= 0; j--) {					// �������ε� ��θ� ���������� ���
				printf("%d - ", temp[j]);
			}
			printf("%d" ,i + 1);									// end vertex
			printf("   ���� : %d", dist[i]);						// ���ŵ� dist�迭���
			printf("\n");
			free(temp);


		}

	}
	free(dist);
	free(select);
	free(index);
}
