#pragma once
#include "definitions.h"

class MinHeap
{
private:
	vector<Pair*> data;
	vector<int> indexOfVertexInHeap;
	int heapSize;
	static int Left(int node);
	static int Right(int node);
	static int Parent(int node);

public:
	MinHeap(int numOfVertices);
	void FixHeapUp(int index);
	void FixHeapDown(int node);
	void Build(vector<Pair*> minWeight);
	bool isEmpty();
	void DecreaseKey(int place, int newWeight);
	vector<int> getIndexOfVertexInHeap();
	int getHeapSize()const;
	Pair* DeleteMin();
	~MinHeap();
};