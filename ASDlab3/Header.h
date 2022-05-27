#include <iostream>
#include <vector>
#include <Map>
#include <string>
using namespace std;


struct Edge {
	int vertex1;
	int vertex2;
	int weight;

	Edge(int vertex1, int vertex2, int weight){
		this->vertex1 = vertex1;
		this->vertex2 = vertex2;
		this->weight = weight;
	}

	bool operator==(Edge edge1) {
		if (this->vertex1 == edge1.vertex1 and this->vertex2 == edge1.vertex2 and this->weight == edge1.weight) {
			return true;
		}
		return false;
	}
};



vector<vector<int>> getMatrixFromConsole();
vector<Edge> matrixToEdgeVector(vector<vector<int>> matrix);
vector<Edge> getMinWeightTree(vector<Edge> edges);
vector<vector<int>> convertEdgesVectorToMatrix(vector<Edge> edges);
void printMatrix(vector<vector<int>> matrix);

vector<Edge> sortEdgesByWeight(vector<Edge> edges);
bool isVertexGained(int vertex, vector<int> vector);
bool isVertexInGroup(int vertex, map<int, vector<int>> map, int key);
vector<int> uniteVectors(vector<int> v1, vector<int> v2);
vector<int> stringToVector(string str);
bool isMatrixSquared(vector<vector<int>> matrix);
void printEdge(Edge edge);