#include <iostream>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <random>
using namespace std;

int countReverse(vector<int> base, vector<int> add);
bool isNumber(string s);
vector<int> arraySlice(vector<int> array, int start, int end);
void addStatsToFile(string filename, vector<pair<int, int>> map, int ID);
vector<pair<int, int>> makeMapOfReversions(vector<vector<int>> matrix, int ID);
vector<vector<int>> getMatrixFromFile(string filename);
vector<int> stringToVectorInt(string s);
int merge(vector<int>* array, vector<int> left, vector<int> right);
int countInverseReinfirced(vector<int>* array);
vector<int> remakeID(vector<int> base, vector<int> add);


void printVector(vector<int> vector);

