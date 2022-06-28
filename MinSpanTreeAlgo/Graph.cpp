#include "Graph.h"
#include "UnionFind.h"

Edge Graph :: getEdgeToRemove()
{
    return edgeToRemove;
}

void Graph :: MakeEmptyGraph()
{
	for (int i = 0; i < numOfVertices; i++)
	{
		LinkedList* pLinkedList = new LinkedList();
		arrOfAdjacencyLists.push_back(pLinkedList);
	}
    allocated = true;
}

/// check if vertex U is a neighbor of vertex V
bool Graph :: IsAdjacent(int u, int v)
{
	bool isAdjacentResult = false;
	LinkedList* lstToCheck = arrOfAdjacencyLists[u - 1];
	Node* current = lstToCheck->getHead();

	while (current != nullptr)
	{
		if (current->vertex == v)
		{
			isAdjacentResult = true;
			break;
		}
		else
		{
			current = current->next;
		}
	}

	return isAdjacentResult;
}

/// returns the list of vertex U neighbors.
LinkedList* Graph :: GetAdjList(int u)
{
	return arrOfAdjacencyLists[u - 1];
}

// add edge (u,v) with weight C to the graph.
void Graph :: AddEdge(int u, int v, int c)
{
	Edge* edge = new Edge;

	arrOfAdjacencyLists[u - 1]->insertNode(v, c);
	arrOfAdjacencyLists[v - 1]->insertNode(u, c);

	edge->v1 = u; 
	edge->v2 = v; 
	edge->weight = c;

	edgesArr.push_back(edge);
}

void Graph :: removeEdge(int u, int v)
{
	arrOfAdjacencyLists[u - 1]->deleteNode(v);
	arrOfAdjacencyLists[v - 1]->deleteNode(u);
    numOfEdges--;
    removeFromEdgesArr(u, v);
}

void Graph::removeFromEdgesArr(int u, int v)
{
    for (int i = 0; i < edgesArr.size(); i++)
    {
        if ((edgesArr[i]->v1 == u && edgesArr[i]->v2 == v) || (edgesArr[i]->v1 == v && edgesArr[i]->v2 == u))
        {
            edgesArr.erase(edgesArr.begin() + i);
        }
    }
}

int Graph :: partition(vector<Edge*>& edgesArr, int start, int end)
{
    int pivot = edgesArr[start]->weight;
    int count = 0;

    for (int i = start + 1; i <= end; i++)
    {
        if (edgesArr[i]->weight <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    std::swap(edgesArr[pivotIndex], edgesArr[start]);
    
    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (edgesArr[i]->weight <= pivot)
        {
            i++;
        }

        while (edgesArr[j]->weight > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            std :: swap(edgesArr[i++], edgesArr[j--]);
        }
    }

    return pivotIndex;
}

void Graph :: quickSort(vector<Edge*>& edgesArr, int start, int end)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(edgesArr, start, end);

    // Sorting the left part
    quickSort(edgesArr, start, p - 1);

    // Sorting the right part
    quickSort(edgesArr, p + 1, end);
}

// Kruskal algorithm
vector<Edge> Graph :: kruskal()
{
    int arrOfAdjacencyListsSize = arrOfAdjacencyLists.size();
    int edgesArrSize = edgesArr.size();
    vector<Edge> mstEdgesArr;
    UnionFind unionFind(arrOfAdjacencyListsSize); 

    quickSort(edgesArr, 0, edgesArr.size() - 1);//sorting edges array

    for (int i = 1; i <= arrOfAdjacencyListsSize; i++)
    {
        unionFind.MakeSet(i);
    }

    for (int i = 0; i < edgesArrSize; i++)
    {
        int v1Rep = unionFind.Find(edgesArr[i]->v1);
        int v2Rep = unionFind.Find(edgesArr[i]->v2);

        if (v1Rep != v2Rep)
        {
            mstEdgesArr.push_back(*(edgesArr[i]));
        }
        unionFind.Union(v1Rep, v2Rep);
    }

    return mstEdgesArr;
}

// Prim algorithm
vector<Pair*> Graph :: prim()
{
    MinHeap heap(numOfVertices);
    vector<bool> InTree(numOfVertices, false);
    vector<Pair*> MinWeight(numOfVertices);
    vector<Pair*> parentsArr(numOfVertices, nullptr);
    int vertex;
    Pair* minWeightedVertex;
    Node* currentNodeOflistToCheck;

    for (int i = 0; i < MinWeight.size(); i++)//allocating and initialaizing MinWeight and ParentsArr arrays.
    {
        MinWeight[i] = new Pair;
        MinWeight[i]->vertex = i + 1;
        MinWeight[i]->weight = INT32_MAX;
    }

    MinWeight[0]->weight = 0;
    heap.Build(MinWeight);

    while (!heap.isEmpty())
    {
        minWeightedVertex = heap.DeleteMin();
        InTree[minWeightedVertex->vertex - 1] = true;
        currentNodeOflistToCheck = arrOfAdjacencyLists[minWeightedVertex->vertex - 1]->getHead();       

        while (currentNodeOflistToCheck != nullptr)
        {
            vertex = currentNodeOflistToCheck->vertex;
            if (!InTree[vertex - 1] && currentNodeOflistToCheck->weight < MinWeight[vertex - 1]->weight)
            {
                MinWeight[vertex - 1]->weight = currentNodeOflistToCheck->weight;
                parentsArr[vertex - 1] = minWeightedVertex;
                heap.DecreaseKey(heap.getIndexOfVertexInHeap()[vertex - 1], MinWeight[vertex - 1]->weight);
            }

            currentNodeOflistToCheck = currentNodeOflistToCheck->next;
        } 
    }

    freeMinWeightArr(MinWeight);
    return parentsArr;
}

void Graph::freeMinWeightArr(vector<Pair*> minWeightArr)
{
    for (int i = 0; i < minWeightArr.size(); i++)
    {
        delete minWeightArr[i];
    }
}

void Graph :: invalidInput(ofstream& FileToWrite)
{
    if (allocated)
    {
        freeGraph();
    }
    cout << "invalid input\n";
    FileToWrite << "invalid input\n";
    exit(1);
}

//check file input validity. 
bool Graph :: tryToCreateEdge(stringstream& s, float& v1, float& v2, float& weight)
{
    string word;
    bool res = true;
    
    s >> word && isNumber(word) ? v1 = stof(word) : res = false;
    s >> word && isNumber(word) ? v2 = stof(word) : res = false;
    s >> word && isNumber(word) ? weight = stof(word) : res = false;

    if (s >> word) // if there is one more number in line, for example  1, 3, 16, 7
        res = false;

    if (res)   
       res = isEdgeValid(v1, v2, weight);  
    
    return res;
}

void Graph :: makeGraphFromFile(string fileName, ofstream& FileToWrite)
{
    fstream file;
    string str;

    file.open(fileName);
    if (!file.good())
    {
        cout << "invalid file name\n"; 
        FileToWrite << "invalid file name\n";
        exit(1);
    }

    getline(file, str);
    if (isNumber(str) && stof(str) > 0)
        numOfVertices = stoi(str);
    else
        invalidInput(FileToWrite);

    getline(file, str);
    if (isNumber(str) && stof(str) > 0)
        numOfEdges = stoi(str);
    else
        invalidInput(FileToWrite);
   
    MakeEmptyGraph();
    getInputFromFileAndUpdateGraph(file, FileToWrite);

    file.close();
}

// try to initialize the graph with edges, and get the edge to remove from file.
void Graph :: getInputFromFileAndUpdateGraph(fstream& file, ofstream& FileToWrite)
{
    int count = 0; 
    string str, word;
    float v1, v2, weight;

    while (!file.eof())
    { 
        count++;
        if (count > numOfEdges)
        {
            getline(file, str);
            stringstream s(str);
            if (!checkIfStrIsEdgeToRemove(s, v1, v2))
            {
                invalidInput(FileToWrite);
            }
            else
            {
                edgeToRemove.v1 = (int)v1;
                edgeToRemove.v2 = (int)v2;
                break;
            }
        }

        getline(file, str);
        stringstream s(str);

        if (tryToCreateEdge(s, v1, v2, weight))
        {
            AddEdge((int)v1, (int)v2, (int)weight);
        }
        else
        {
            invalidInput(FileToWrite);
        }
    }

    if (count < numOfEdges)
    {
        invalidInput(FileToWrite);
    }

}

bool Graph::checkIfStrIsEdgeToRemove(stringstream& s, float& v1, float& v2)
{
    string word;
    bool res = true;
    
    s >> word && isNumber(word) ? v1 = stof(word) : res = false;
    s >> word && isNumber(word) ? v2 = stof(word) : res = false;

    if (s >> word)
    {
        res = false;
    }

    if (res)
    {
        res = checkIfEdgeToRemoveValid(v1, v2);
    }
   
    return res;
}

bool Graph::checkIfEdgeToRemoveValid(float v1, float v2)
{
    bool res = true;

    if (v1 != (int)v1 || v2 != (int)v2) // check if v1, v2, weight are whole numbers
    {
        res = false;
    }
    if (v1 > numOfVertices || v1 < 1 || v2 > numOfVertices || v2 < 1 || !IsAdjacent(v1, v2))// check if edge exists and weight is positive 
    {
        res = false;
    }

    return res;
}

bool Graph :: isEdgeValid(float v1, float v2, float weight)
{
    bool res = true; 

    if (v1 != (int)v1 || v2 != (int)v2 || weight != (int)weight) // check if v1, v2, weight are whole numbers
    {
        res = false;
    }
    if (v1 > numOfVertices || v1 < 1 || v2 > numOfVertices || v2 < 1 || weight < 0)// check if edge exists and weight is positive 
    {
        res = false;
    }

    return res;
}

void Graph :: freeGraph()
{
    for (int i = 0; i < arrOfAdjacencyLists.size(); i++)
    {
        delete arrOfAdjacencyLists[i];
    }
}

bool Graph :: isNumber(const string& str)
{
    for (char const& c : str)
    {
        if (std::isdigit(c) == 0)
        {
            return false;
        }
    }

    return true;
}

// sums all edges weight of MST kruskal
int Graph :: calculateWeightKruskal(vector<Edge> minSpanningTree)
{
    int weight = 0;

    for (int i = 0; i < minSpanningTree.size(); i++)
    {
        weight += minSpanningTree[i].weight;
    }

    return weight;
}

//sums all edges weight of MST prim
int Graph :: calculateWeightPrim(vector<Pair*> minSpanningTree)
{
    int weight = 0;
    Node* currNodeToCheck = nullptr;

    for (int i = 1; i < minSpanningTree.size(); i++)
    {
        currNodeToCheck = arrOfAdjacencyLists[i]->getHead();

        while (currNodeToCheck->vertex != minSpanningTree[i]->vertex)
        {
          currNodeToCheck = currNodeToCheck->next;
        }

        weight += currNodeToCheck->weight;   
    }

    return weight;
}

bool Graph :: checkIfGraphIsConnected()
{
    vector<bool> visitedVertices(numOfVertices, false);
    int numOfVerticesVisited = 1;

    visitedVertices[0] = true;
    visit(1, visitedVertices, numOfVerticesVisited);

    return numOfVertices == numOfVerticesVisited;
}

// helper to check if graph is connected
void Graph :: visit(int vertex, vector<bool>& visitedVertices, int& numOfVerticesVisited)
{
    Node* nodeToVisit = nullptr; 
    nodeToVisit = arrOfAdjacencyLists[vertex - 1]->getHead();

    while (nodeToVisit != nullptr)
    {
        if (!visitedVertices[nodeToVisit->vertex - 1])
        {
            visitedVertices[nodeToVisit->vertex - 1] = true;
            numOfVerticesVisited++;
            visit(nodeToVisit->vertex, visitedVertices, numOfVerticesVisited); 
        }

        nodeToVisit = nodeToVisit->next;
    }
}

Graph::~Graph()
{
    freeGraph();

    for (int i = 0; i < edgesArr.size(); i++)
    {
        delete edgesArr[i];  
    }
}
