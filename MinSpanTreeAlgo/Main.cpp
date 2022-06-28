#include "definitions.h"
#include "Graph.h"

void main(int argc, char* argv[])
{
	if (argc != 3)//check if there are input and output files names as command arguments, and if not exit.
	{
		cout << "missing arguments\n";
		exit(1);
	}

	Graph graph;
	ofstream FileToWrite(argv[2]);

	if (!FileToWrite.good())
	{
		cout << "can not open file\n";
		exit(1);
	}

	graph.makeGraphFromFile(argv[1], FileToWrite);
	if (!graph.checkIfGraphIsConnected())
	{
		cout << "No MST\n";
		FileToWrite << "No MST\n";
		graph.freeGraph();
		exit(1);
	}
	int KruskalMstWeight = graph.calculateWeightKruskal(graph.kruskal());
	int primMstWeight = graph.calculateWeightPrim(graph.prim());

	FileToWrite << "Kruskal <" << KruskalMstWeight << ">\n";
	FileToWrite << "Prim <" << primMstWeight << ">\n";

	cout << "Kruskal <" << KruskalMstWeight << ">\n";
	cout << "Prim <" << primMstWeight << ">\n";
	
	graph.removeEdge(graph.getEdgeToRemove().v1, graph.getEdgeToRemove().v2);
	if (!graph.checkIfGraphIsConnected())
	{
		cout << "No MST\n";
		FileToWrite << "No MST\n";
	}
	else
	{
		KruskalMstWeight = graph.calculateWeightKruskal(graph.kruskal());
		cout << "Kruskal <" << KruskalMstWeight << "'>\n";
		FileToWrite << "Kruskal <" << KruskalMstWeight << "'>\n";
	}

	FileToWrite.close();
}
