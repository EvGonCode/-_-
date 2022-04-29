#include <iostream>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <random>
#include <fstream>
#include <string>
#include <map>
#include "Header.h"

using namespace std;

vector<int> arraySlice(vector<int> array, int start, int end) {
	if (end < array.size() - 1) array.erase(array.begin() + end + 1, array.end());
	if (start > 0) array.erase(array.begin(), array.begin() + start);
	return array;
}


void addStatsToFile(string filename, vector<pair<int, int>> map, int ID) {
	fstream write;
	try {
		write.open(filename, ios_base::out);
		write << ID << endl;

		for (int i = 0; i < map.size(); i++) {
			write << map[i].second << " " << map[i].first << endl;

		}

		write << ID;

		write.close();
	}
	catch (exception e) {
		cout << "Помилка при записі тексту в файл: " << e.what();
		write.close();
	}
}

vector<pair<int, int>> makeMapOfReversions(vector<vector<int>> matrix, int ID) {
	vector<pair<int, int>> map;
	
	for (int i = 0; i < matrix.size(); i++) {
		if (i != ID - 1) {
			vector<int> reID = remakeID(matrix[ID-1], matrix[i]);
			map.push_back(make_pair(countInverseReinfirced(&reID), i+1));

			//map.push_back(make_pair(countReverse(matrix[ID-1], matrix[i]), i + 1));
		}
	}


	sort(map.begin(), map.end());

	return map;
}

vector<vector<int>> getMatrixFromFile(string filename) {
	vector<vector<int>> result;
	fstream read;
	string s;
	try {
		read.open(filename);
		while (!read.eof()) {
			getline(read, s);
			result.push_back(stringToVectorInt(s));
		}

		read.close();
	}
	catch (exception e) {
		cout << "Помилка при зчитуванні тексу з файлу: " << e.what();
		read.close();
	}

	return result;

}

vector<int> stringToVectorInt(string s) {
	vector<int> result;
	string buffer = "";
	for (int i = 0; i < s.length(); i++) {
		if (s.at(i) == ' ') {
			if (buffer.length() != 0) {
				result.push_back(stoi(buffer));
				buffer = "";
			}
		}
		else if (i + 1 == s.length()) {
			buffer.push_back(s.at(i));
			result.push_back(stoi(buffer));
			buffer = "";
		}
		else {
			buffer.push_back(s.at(i));
		}
	}
	return result;
}

bool isNumber(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s.at(i)) == 0) return false;
	}
	return true;
}

int merge(vector<int>* array, vector<int> left, vector<int> right) {
	int inversionCount = 0;
	left.push_back(INT_MAX);
	right.push_back(INT_MAX);
	int i = 0, j = 0;
	for (size_t k = 0; k < array->size(); k++)
	{
		if (left[i] <= right[j]) {
			(*array)[k] = left[i];
			i++;
		}
		else {
			(*array)[k] = right[j];
			j++;
			inversionCount += left.size() - 1 - i;
		}
	}
	return inversionCount;
}

int countInverseReinfirced(vector<int>* array) {
	if (array->size() > 1) {
		int leftCounter, rightCounter, splitCounter;
		vector<int> left = arraySlice(*array, 0, array->size() / 2 - 1);
		vector<int> right = arraySlice(*array, array->size() / 2, array->size() - 1);
		leftCounter = countInverseReinfirced(&left);
		rightCounter = countInverseReinfirced(&right);
		splitCounter = merge(array, left, right);
		return leftCounter + rightCounter + splitCounter;
	}
	else return 0;
}

int countReverse(vector<int> base, vector<int> add) {
	int counter = 0;
	vector<int> sorted = remakeID(base, add);

	for (int i = 0; i < sorted.size(); i++) {
		for (int j = i + 1; j < sorted.size(); j++) {
			if (sorted[i] > sorted[j]) { counter++; }
		}
	}

	return counter;
}

vector<int> remakeID(vector<int> base, vector<int> add) {
	vector<int> reID;
	for (int i = 0; i < base.size() - 1; i++) {
		for (int j = 1; j < base.size(); j++) {
			if (base[j] == i + 1) {
				reID.push_back(add[j]);
				break;
			}
		}
	}
	return reID;
}

void printVector(vector<int> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i] << " ";
	}
	cout << endl;
}
