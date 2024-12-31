// AOC_D4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

// Part 2 ANSWER: 1992

int get_count(vector<string>& m, int row, int col)
{
    //cout << "row: " << row << " col: " << col << endl;

    // Top left 
    int curr_row = row;
    int curr_col = col;
    curr_row--;
    curr_col--;

    if(curr_row < 0 || curr_row >= m.size() || curr_col < 0 || curr_col >= m[0].size()) return 0;
    char top_left = m[curr_row][curr_col];


    // Btm right
    curr_row = row;
    curr_col = col;
    curr_row++;
    curr_col++;

    
    if(curr_row < 0 || curr_row >= m.size() || curr_col < 0 || curr_col >= m[0].size()) return 0;
    char btm_right = m[curr_row][curr_col];
    if ( !((top_left == 'M' && btm_right == 'S') || (top_left == 'S' && btm_right == 'M')) ) return 0;

    




    // Top right
    curr_row = row;
    curr_col = col;
    curr_row--;
    curr_col++;

    if(curr_row < 0 || curr_row >= m.size() || curr_col < 0 || curr_col >= m[0].size()) return 0;

    char top_right = m[curr_row][curr_col];



    // Btm left
    curr_row = row;
    curr_col = col;
    curr_row++;
    curr_col--;

    if(curr_row < 0 || curr_row >= m.size() || curr_col < 0 || curr_col >= m[0].size()) return 0;

    char btm_left = m[curr_row][curr_col];


    if ( !((top_right == 'M' && btm_left == 'S') || (top_right == 'S' && btm_left == 'M')) ) return 0;




    

    //cout << " -->success " << endl; 

    return 1;
    
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

    for(string l : m)
    {
        cout << l << endl;
    }

    
    int ans = 0;
    for (int i = 0; i < m.size(); i++)
    {
        string curr_string = m[i];
        for (int j = 0; j < curr_string.size(); j++)
        {
            char c = curr_string[j];
            if (c == 'A') ans += get_count(m, i, j);
        }
    }
    
    cout << "ans: " << ans << endl;
    return 0;


}


