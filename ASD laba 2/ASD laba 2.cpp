#include <iostream>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <random>
#include <string>
#include "Header.h"

using namespace std;



int main(int argc, char** argv)
{
    string inFileName, outFileName;
    int userID;

    
    userID = 6; 
    inFileName = "input.txt"; 
    outFileName = "ip13_honcharov_08_output.txt"; 
    if (argc == 2) {
        string arg(argv[1]);
        if (isNumber(arg)) userID = stoi(arg);
        else inFileName = arg;
    }
    else if (argc > 2) {
        string arg1(argv[1]), arg2(argv[2]);
        if (isNumber(arg1)) {
            userID = stoi(arg1);
            inFileName = arg2;
            }
        else if (isNumber(arg2)) {
             userID = stoi(arg2);
             inFileName = arg1;
        }
        else inFileName = arg1;
    }

    

    vector<vector<int>> matrix = getMatrixFromFile(inFileName);

    vector<pair<int, int>> map = makeMapOfReversions(matrix, userID);

    addStatsToFile(outFileName, map, userID);

}