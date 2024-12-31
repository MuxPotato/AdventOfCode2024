// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 1: Answer: 398

Solution: 

We always take p1 (pair 1) as the pair with the lower row

If rows are the same, we break by col


we can then see that the two nodes, n1 has row - row_diff, and col + or - depending on the two cases. n2 has row + row_diff and col + or - depending on the two cases
we can draw it out and see it


*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <math.h>
#include <utility>
using namespace std;


int solve(vector<string> &matrix, char c, vector<pair<int,int>> positions, set<pair<int,int>> &visited)
{
    int ans = 0;

    for(int i = 0; i < positions.size(); i++)
    {
        for(int j = 0; j < positions.size(); j++)
        {
            if (i == j) continue;

            pair<int,int> pos1 = positions[i];
            pair<int,int> pos2 = positions[j];

            pair<int,int> p1;
            pair<int,int> p2;

            if (pos1.first < pos2.first) 
            {
                p1 = pos1;
                p2 = pos2;
            }
            else if (pos1.first > pos2.first)
            {
                p1 = pos2;
                p2 = pos1;
            }
            else
            {
                if (pos1.second < pos2.second)
                {
                    p1 = pos1;
                    p2 = pos2;
                }
                else
                {
                    p1 = pos2;
                    p2 = pos1;
                }
            }



            int row_diff = abs(p1.first - p2.first);
            int col_diff = abs(p1.second - p2.second);

            // case 1: col1 >= col2 
            if (p1.second >= p2.second)
            {
                // first num
                int new_row = p1.first - row_diff;
                int new_col = p1.second + col_diff;

                

                if (new_row < matrix.size() && new_row >= 0 && new_col < matrix[0].size() && new_col >= 0 && visited.find(make_pair(new_row,new_col)) == visited.end()) 
                {
                    cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                    visited.insert(make_pair(new_row,new_col));
                    ans++;
                }
                // second num
                new_row = p2.first + row_diff;
                new_col = p2.second - col_diff;
                //cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                if (new_row < matrix.size() && new_row >= 0 && new_col < matrix[0].size() && new_col >= 0 && visited.find(make_pair(new_row,new_col)) == visited.end()) 
                {
                    cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                    visited.insert(make_pair(new_row,new_col));
                    ans++;
                }
            }
            else // case 2: col1 < col2 
            {
                // first num
                int new_row = p1.first - row_diff;
                int new_col = p1.second - col_diff;
                //cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                if (new_row < matrix.size() && new_row >= 0 && new_col < matrix[0].size() && new_col >= 0 && visited.find(make_pair(new_row,new_col)) == visited.end()) 
                {
                    cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                    visited.insert(make_pair(new_row,new_col));
                    ans++;
                }

                // second num
                new_row = p2.first + row_diff;
                new_col = p2.second + col_diff;
                //cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                if (new_row < matrix.size() && new_row >= 0 && new_col < matrix[0].size() && new_col >= 0 && visited.find(make_pair(new_row,new_col)) == visited.end()) 
                {
                    cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                    visited.insert(make_pair(new_row,new_col));
                    ans++;
                }
            }
        }
    }

    
    
    return ans;
}




int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    if (!fin.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    
    vector<string> lines;
    
    while (std::getline(fin, line))
    {
        if(line.empty()) break;
        lines.push_back(line);
    }

    unordered_map<char,vector<pair<int,int>>> chars_positions;
    
    for(int row = 0; row < lines.size(); row++)
    {
        for(int col = 0; col < lines[0].size(); col++)
        {
            char c = lines[row][col];
            if(c != '.') chars_positions[c].push_back(make_pair(row,col));
        }
    }

    int ans = 0;
    set<pair<int,int>> visited;
    for(auto &[c, positions] : chars_positions)
    {
        cout << "current char: " << c << endl;

        ans += solve(lines, c, positions, visited);
        
    }


    cout << "ans: " << ans << endl;

}

