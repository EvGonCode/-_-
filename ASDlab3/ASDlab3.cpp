#include <iostream>
#include <vector>
#include <Map>
#include <string>
#include "Header.h"

using namespace std;

int main()
{
	vector<vector<int>> matrix = getMatrixFromConsole();
	printMatrix(matrix);
	vector<Edge> edges = matrixToEdgeVector(matrix);

	vector<Edge> edgesOfMinTree = getMinWeightTree(edges);
	vector<vector<int>> matrixOfMinWeight = convertEdgesVectorToMatrix(edgesOfMinTree);
	printMatrix(matrixOfMinWeight);
}
