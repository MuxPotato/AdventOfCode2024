// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 2: Answer: 

Solution: 

Same solution as Part 1 but now we keep going in both directions and we also count the starting position of the nodes now


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
                int new_row = p1.first; // - row_diff;
                int new_col = p1.second; // + col_diff;
                while(new_row < matrix.size() && new_row >= 0 && new_col < matrix[0].size() && new_col >= 0)
                {
                    if(visited.find(make_pair(new_row,new_col)) == visited.end())
                    {
                        cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                        visited.insert(make_pair(new_row,new_col));
                        ans++;  
                    }
                    new_row = new_row - row_diff;
                    new_col = new_col + col_diff;
                }
                
                
                // second num
                new_row = p2.first; // + row_diff;
                new_col = p2.second; // - col_diff;

                while(new_row < matrix.size() && new_row >= 0 && new_col < matrix[0].size() && new_col >= 0)
                {
                    if(visited.find(make_pair(new_row,new_col)) == visited.end())
                    {
                        cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                        visited.insert(make_pair(new_row,new_col));
                        ans++;  
                    }
                    new_row = new_row + row_diff;
                    new_col = new_col - col_diff;
                }
            }
            else // case 2: col1 < col2 
            {
                // first num
                int new_row = p1.first; // - row_diff;
                int new_col = p1.second; // - col_diff;

                while(new_row < matrix.size() && new_row >= 0 && new_col < matrix[0].size() && new_col >= 0)
                {
                    if(visited.find(make_pair(new_row,new_col)) == visited.end())
                    {
                        cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                        visited.insert(make_pair(new_row,new_col));
                        ans++;  
                    }
                    new_row = new_row - row_diff;
                    new_col = new_col - col_diff;
                }

                // second num
                new_row = p2.first; // + row_diff;
                new_col = p2.second; // + col_diff;

                while(new_row < matrix.size() && new_row >= 0 && new_col < matrix[0].size() && new_col >= 0)
                {
                    if(visited.find(make_pair(new_row,new_col)) == visited.end())
                    {
                        cout << "new_row: " << new_row << " new_col: " << new_col << endl;
                        visited.insert(make_pair(new_row,new_col));
                        ans++;  
                    }
                    new_row = new_row + row_diff;
                    new_col = new_col + col_diff;
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
    cout<< "slay";

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

