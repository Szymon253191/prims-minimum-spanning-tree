// TO DO
// Doesn'n counts from 0 so V = 10 checks 9 connections
// Its for maximal value not minimal

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define V 10

long long int readQPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return ((long long int)count.QuadPart);
}

int minKey(int key[], bool mstSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

int printMST(int parent[], int graph[V][V])
{
	printf("Edge\t \tWeight\n");
	for (int i = 1; i < V; i++)
		printf("%2d - %2d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

void primMST(int graph[V][V])
{
	int parent[V];
	int key[V];
	bool mstSet[V];

	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	key[0] = 0;
	parent[0] = -1;

	for (int count = 0; count < V - 1; count++)
	{

		int u = minKey(key, mstSet);

		mstSet[u] = true;

		for (int v = 0; v < V; v++)

			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	printMST(parent, graph);
}

int main()
{

	int *numberArray = malloc(1000000 * sizeof(int));

	printf("---------- Wczytanie liczb -----------\n");

	FILE *myFile;
	myFile = fopen("generated_matrix.txt", "r");

	// int graph[V][V];
	int(*graph)[V];
	graph = malloc(sizeof(*graph) * V);
	graph = malloc(sizeof(int[V][V]));

	for (int i = 0; i < V * V; i++)
	{
		fscanf(myFile, "%d\t", &numberArray[i]);
	}

	int k = 0;
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			graph[i][j] = abs(numberArray[k]);
			k++;
		}
	}

	// Print the solution
	long long int elapsed, frequency, start;
	elapsed = 0;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	start = readQPC();
	primMST(graph);
	elapsed = (readQPC() - start);

	float elapsedInSec = floor(frequency * elapsed) / frequency / frequency;

	printf("------------ Czas wykonania ----------\n");
	free(numberArray);
	printf("\t     Czas: %lf. \n \n", elapsedInSec);

	return 0;
}
