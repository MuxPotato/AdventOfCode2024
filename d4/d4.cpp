// AOC_D4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

// Part 1: ans: 2571

int get_count(vector<string>& m, int row, int col)
{
    int count = 0;

    // Check forward 
    string temp = "";
    int curr_row = row;
    int curr_col = col;
    while (curr_row >= 0 && curr_row < m.size() && curr_col >= 0 && curr_col < m[0].size() && temp.size() < 4)
    {
        temp.push_back(m[curr_row][curr_col]);
        curr_col++;
    }
    cout << "temp: " << temp << endl;
    if (temp == "XMAS") count++;




    // Check backwards

    temp = "";
    curr_row = row;
    curr_col = col;
    while (curr_row >= 0 && curr_row < m.size() && curr_col >= 0 && curr_col < m[0].size() && temp.size() < 4)
    {
        temp.push_back(m[curr_row][curr_col]);
        curr_col--;
    }
    cout << "temp: " << temp << endl;
    if (temp == "XMAS") count++;

    // Check up

    temp = "";
    curr_row = row;
    curr_col = col;
    while (curr_row >= 0 && curr_row < m.size() && curr_col >= 0 && curr_col < m[0].size() && temp.size() < 4)
    {
        temp.push_back(m[curr_row][curr_col]);
        curr_row--;
    }
    cout << "temp: " << temp << endl;
    if (temp == "XMAS") count++;

    // check down

    temp = "";
    curr_row = row;
    curr_col = col;
    while (curr_row >= 0 && curr_row < m.size() && curr_col >= 0 && curr_col < m[0].size() && temp.size() < 4)
    {
        temp.push_back(m[curr_row][curr_col]);
        curr_row++;
    }
    cout << "temp: " << temp << endl;
    if (temp == "XMAS") count++;


    // Check Top left

    temp = "";
    curr_row = row;
    curr_col = col;
    while (curr_row >= 0 && curr_row < m.size() && curr_col >= 0 && curr_col < m[0].size() && temp.size() < 4)
    {
        temp.push_back(m[curr_row][curr_col]);
        curr_row--;
        curr_col--;
    }
    cout << "temp: " << temp << endl;
    if (temp == "XMAS") count++;


    // Check Top right

    temp = "";
    curr_row = row;
    curr_col = col;
    while (curr_row >= 0 && curr_row < m.size() && curr_col >= 0 && curr_col < m[0].size() && temp.size() < 4)
    {
        temp.push_back(m[curr_row][curr_col]);
        curr_row--;
        curr_col++;
    }
    cout << "temp: " << temp << endl;
    if (temp == "XMAS") count++;


    // Check Btm Right
    temp = "";
    curr_row = row;
    curr_col = col;
    while (curr_row >= 0 && curr_row < m.size() && curr_col >= 0 && curr_col < m[0].size() && temp.size() < 4)
    {
        temp.push_back(m[curr_row][curr_col]);
        curr_row++;
        curr_col++;
    }
    cout << "temp: " << temp << endl;
    if (temp == "XMAS") count++;

    // Check Btm Left
    temp = "";
    curr_row = row;
    curr_col = col;
    while (curr_row >= 0 && curr_row < m.size() && curr_col >= 0 && curr_col < m[0].size() && temp.size() < 4)
    {
        temp.push_back(m[curr_row][curr_col]);
        curr_row++;
        curr_col--;
    }
    cout << "temp: " << temp << endl;
    if (temp == "XMAS") count++;

    return count;
    
}


int main()
{
    vector<string> m;
    string line;
	
	std::ifstream fin("d4_in.txt");

	while(getline(fin, line))
	{
		if(line.empty()) break;
		m.push_back(line);
	}

	
    
    int ans = 0;
    for (int i = 0; i < m.size(); i++)
    {
        string curr_string = m[i];
        for (int j = 0; j < curr_string.size(); j++)
        {
            char c = curr_string[j];
            if (c == 'X') ans += get_count(m, i, j);
        }
    }
    
    cout << "ans: " << ans << endl;
    return 0;


}


