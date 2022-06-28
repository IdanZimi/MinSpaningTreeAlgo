#pragma once
#include "definitions.h"
#include "LinkedList.h"
#include "MinHeap.h"

typedef struct
{
	int v1;
	int v2;
	int weight;
}Edge;

class Graph
{
private:
	bool allocated = false;
	int numOfVertices;
	int numOfEdges;
	vector<LinkedList*> arrOfAdjacencyLists;
	vector<Edge*> edgesArr;
	int partition(vector<Edge*>& edgesArr, int start, int end);
	Edge edgeToRemove;

public:
	Edge getEdgeToRemove();
	void MakeEmptyGraph();
	bool IsAdjacent(int u, int v); 
	LinkedList* GetAdjList(int u);
	void AddEdge(int u, int v, int c); 
	void removeEdge(int u, int v);
	void quickSort(vector<Edge*>& edgesArr, int start, int end);
	vector<Edge> kruskal();
	vector<Pair*> prim();
	void makeGraphFromFile(string fileName, ofstream& FileToWrite);
	void invalidInput(ofstream& FileToWrite);
	bool tryToCreateEdge(stringstream& s, float& v1, float& v2, float& weight);
	bool isEdgeValid(float v1, float v2, float weight);
	void freeGraph();
	bool isNumber(const string& str);
	void getInputFromFileAndUpdateGraph(fstream& file, ofstream& FileToWrite);
	int calculateWeightKruskal(vector<Edge> minSpanningTree);
	int calculateWeightPrim(vector<Pair*> minSpanningTree);
	bool checkIfGraphIsConnected();
	void visit(int vertex, vector<bool>& visitedVertices, int& numOfVerticesVisited);
	bool checkIfStrIsEdgeToRemove(stringstream& s, float& v1, float& v2);
	bool checkIfEdgeToRemoveValid(float v1, float v2);
	void removeFromEdgesArr(int u, int v);
	void freeMinWeightArr(vector<Pair*> minWeightArr);
	~Graph();
};