#include "UnionFind.h"

UnionFind::UnionFind(int numOfVertices)
{
	size = numOfVertices;
	A.resize(size);

	for (int i = 0; i < size; i++)
	{
		A[i].parent = -1;
		A[i].size = 0;
	}
}

void UnionFind::MakeSet(int x)
{
	A[x - 1].parent = x;
	A[x - 1].size = 1;
}

int UnionFind::Find(int x)
{
	if (A[x - 1].parent == x)
	{
		return x; 
	}
	else
	{
		return (A[x - 1].parent = Find(A[x - 1].parent));
	}
}

void UnionFind::Union(int repX, int repY)
{
	if (A[repX - 1].size > A[repY - 1].size)
	{
		A[repY - 1].parent = repX;
		A[repX - 1].size += A[repY - 1].size;
	}
	else
	{
		A[repX - 1].parent = repY;
		A[repY - 1].size += A[repX - 1].size;
	}	
}