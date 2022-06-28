#include "MinHeap.h"

int MinHeap::getHeapSize() const
{
	return heapSize;
}

int MinHeap::Left(int node)
{
	return (2 * node + 1);
}

int MinHeap::Right(int node)
{
	return (2 * node + 2);
}

int MinHeap::Parent(int node)
{
	return (node - 1) / 2;
}

MinHeap::MinHeap(int numOfVertices)
{
	for (int i = 0; i < numOfVertices; i++)
	{
		indexOfVertexInHeap.push_back(i);
	}
	
	heapSize = numOfVertices;
}

void MinHeap::FixHeapUp(int index)
{
	// check if the node at index and its parent violate the heap property
	if (index && data[Parent(index)]->weight > data[index]->weight)
	{
		//swap at the indexes array.
		swap(indexOfVertexInHeap[data[index]->vertex - 1], indexOfVertexInHeap[data[Parent(index)]->vertex - 1]);
		// swap the two if heap property is violated
		swap(data[index], data[Parent(index)]);

		// call FixHeapUp on the parent
		FixHeapUp(Parent(index));
	}
}

void MinHeap::FixHeapDown(int node)
{
	int max;
	int left = Left(node);
	int right = Right(node);
	if ((left < heapSize) && (data[left]->weight < data[node]->weight))
	{
		max = left;
	}
	else
		max = node;
	if ((right < heapSize) && (data[right]->weight < data[max]->weight))
	{
		max = right;
	}
	if (max != node)
	{
		swap(data[node], data[max]);//swap at the data array (the heap)
		swap(indexOfVertexInHeap[data[node]->vertex - 1], indexOfVertexInHeap[data[max]->vertex - 1]);//swap at the indexes array

		FixHeapDown(max);
	}
}

Pair* MinHeap::DeleteMin()
{
	Pair* min;

	if (heapSize < 1)
	{
		cout << "error";
		exit(-1);
	}

	min = data[0];
	data[0] = data[heapSize - 1];
	indexOfVertexInHeap[data[heapSize - 1]->vertex - 1] = 0;
	heapSize--;
	data.resize(heapSize);
	FixHeapDown(0);

	return min;
}

void MinHeap::Build(vector<Pair*> minWeight)//build the heap with floyd algorithm
{ 
	for (int i = 0; i < minWeight.size(); i++)
	{
		Pair* pair = new Pair;
		pair->vertex = minWeight[i]->vertex;
		pair->weight = minWeight[i]->weight;
		data.push_back(pair); 
	}

	for (int i = (data.size() / 2) - 1; i >= 0; i--)
	{
		FixHeapDown(i);
	}
}

bool MinHeap::isEmpty()
{
	return (heapSize == 0);
}

void MinHeap::DecreaseKey(int index, int newWeight)
{
	data[index]->weight = newWeight;
	FixHeapUp(index);
}

vector<int> MinHeap::getIndexOfVertexInHeap()
{
	return indexOfVertexInHeap;
}

MinHeap::~MinHeap()
{
	for (int i = 0; i < data.size(); i++)
	{
		delete data[i];
	}
}