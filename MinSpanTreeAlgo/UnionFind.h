#pragma once
#include "definitions.h"

typedef struct
{
	int parent;
	int size;
}Element;

class UnionFind
{
private:
	vector<Element> A;
	int size;

public:
	UnionFind(int numOfVertices);
	void MakeSet(int x); 
	int Find(int x);
	void Union(int repX, int repY);
};