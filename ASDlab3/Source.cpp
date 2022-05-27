#include <iostream>
#include <vector>
#include <Map>
#include <string>
#include "Header.h"

using namespace std;


vector<Edge> matrixToEdgeVector(vector<vector<int>> matrix) {
	vector<Edge> result;

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			if (j > i and matrix[i][j] !=0) {
				result.push_back(Edge(i + 1, j + 1, matrix[i][j]));
			}
		}
	}

	return result;
}

vector<Edge> sortEdgesByWeight(vector<Edge> edges) {
	bool ischanged = false;

	while (1) {
		ischanged = false;

		for (int i = 0; i < edges.size()-1; i++) {
			if (edges[i].weight > edges[i + 1].weight) {
				Edge buffer = edges[i];
				edges[i] = edges[i + 1];
				edges[i + 1] = buffer;
				ischanged = true;
			}
		}


		if (ischanged == false) {
			break;
		}
	}

	return edges;
}

bool isVertexGained(int vertex, vector<int> vector) {
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] == vertex) {
			return true;
		}
	}
	return false;
}


bool isVertexInGroup(int vertex, map<int, vector<int>> map, int key) {
	for (int i = 0; i < map[key].size(); i++) {
		if (map[key][i] == vertex) {
			return true;
		}
	}

	return false;
}

vector<int> uniteVectors(vector<int> v1, vector<int> v2) {
	for (int i = 0; i < v2.size(); i++) {
		v1.push_back(v2[i]);
	}
	return v1;
}

vector<Edge> getMinWeightTree(vector<Edge> edges) {
	vector<int> gainedVertex;						//Вершини що з'єднані ребром
	map<int , vector<int>> isolatedGroupsAndVertex; //Ізольовані вершини та групи
	vector<Edge> result;							//Ребра кістякового дерева(мінімального)
	edges = sortEdgesByWeight(edges);

	for (auto edge : edges) {
		if (!isVertexGained(edge.vertex1, gainedVertex) or !isVertexGained(edge.vertex2, gainedVertex)) {
			if (!isVertexGained(edge.vertex1, gainedVertex) and !isVertexGained(edge.vertex2, gainedVertex)) {
				vector<int> group = { edge.vertex1, edge.vertex2 };

				isolatedGroupsAndVertex.insert(make_pair(edge.vertex1, group));
				isolatedGroupsAndVertex.insert(make_pair(edge.vertex2, group));
			}
			else {
				if (isolatedGroupsAndVertex.count(edge.vertex1) == 0) {
					isolatedGroupsAndVertex[edge.vertex2].push_back(edge.vertex1);
					isolatedGroupsAndVertex.insert(make_pair(edge.vertex1, isolatedGroupsAndVertex[edge.vertex2]));
				}
				else {
					isolatedGroupsAndVertex[edge.vertex1].push_back(edge.vertex2);
					isolatedGroupsAndVertex.insert(make_pair(edge.vertex2, isolatedGroupsAndVertex[edge.vertex1]));
				}
			}
			result.push_back(edge);
			gainedVertex.push_back(edge.vertex1);
			gainedVertex.push_back(edge.vertex2);
		}
	}
	for (auto edge : edges) {
		if (!isVertexInGroup(edge.vertex1, isolatedGroupsAndVertex, edge.vertex2) and
			!isVertexInGroup(edge.vertex2, isolatedGroupsAndVertex, edge.vertex1)) {

			result.push_back(edge);

			vector<int> group = uniteVectors(isolatedGroupsAndVertex[edge.vertex1], isolatedGroupsAndVertex[edge.vertex2]);
			isolatedGroupsAndVertex[edge.vertex1] = group;
			isolatedGroupsAndVertex[edge.vertex2] = group;

			for (int i = 0; i < group.size(); i++) {
				isolatedGroupsAndVertex[group[i]] = group;
			}

		}
	}

	return result;
}

vector<int> stringToVector(string str) {
	vector<int> vector;
	string buffer;
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == ' ') {
			vector.push_back(stoi(buffer));
			buffer = "";
			continue;
		}
		if (i + 1 == str.size()) {
			buffer += str.at(i);
			vector.push_back(stoi(buffer));
			break;
		}
		buffer += str.at(i);
	}

	return vector;
}


bool isMatrixSquared(vector<vector<int>> matrix) {
	int size = matrix.size();
	for (int i = 0; i < matrix.size(); i++) {
		if (matrix[i].size() != size) {
			return false;
		}
	}
	return true;
}

vector<vector<int>> getMatrixFromConsole() {
	vector<vector<int>> matrix;
	vector<int> line;

	cout << "Enter graph connections matrix(show example? y/n):";
	string answer;
	cin >> answer; cout << endl;

	if (answer == "y" or answer == "Y" or answer == "+") {
		cout << "0 1 1\n1 0 1\n1 1 0\n\n";
	}
	cin.ignore();

	while (1) {

		string s;
		while (1) {
			getline(cin, s);
			if (s.size() == 0) {
				break;
			}

			line = stringToVector(s);
			matrix.push_back(line);
		}

		if (isMatrixSquared(matrix)) {
			break;
		}
		else {
			cout << "Square matrix needed, try one more time\n";
			matrix = vector<vector<int>>{};
			line = vector<int>{};
		}

	}

	return matrix;

}

vector<vector<int>> convertEdgesVectorToMatrix(vector<Edge> edges) {
	vector<vector<int>> matrix;
	vector<int> line;

	for (int i = 0; i < edges.size()+1; i++) {
		line.push_back(0);
	}
	for (int i = 0; i < edges.size()+1; i++) {
		matrix.push_back(line);
	}

	for (int i = 0; i < edges.size(); i++) {
		Edge edge = edges[i];
		matrix[edge.vertex1-1][edge.vertex2-1] = edge.weight;
		matrix[edge.vertex2-1][edge.vertex1-1] = edge.weight;
	}

	return matrix;
}

void printMatrix(vector<vector<int>> matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void printEdge(Edge edge) {
	cout << edge.vertex1 << " " << edge.vertex2 << "  " << edge.weight << endl;
}