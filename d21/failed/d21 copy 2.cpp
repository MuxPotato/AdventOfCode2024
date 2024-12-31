#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <set>

/*
Part 1: 

*/

using namespace std;


vector<vector<char>> numpad =
{
    {'7','8','9'},
    {'4','5','6'},
    {'1','2','3'},
    {'N','0','A'},
};


vector<vector<char>> arrowpad =
{
    {'N','^','A'},
    {'<','v','>'},
};






int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    vector<string> codes;

    while(getline(fin,line))
    {
        if (line.empty()) break;
        codes.push_back(line);
    }

    unordered_map<char,unordered_map<char,vector<string>>> num_map;

    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 3; c++)
        {
            pair<int,int> start = make_pair(r,c);

            for(int g_row = 0; g_row < 4; g_row++)
            {
                for(int g_col = 0; g_col < 3; g_col++)
                {
                    pair<int,int> goal = make_pair(g_row,g_col);

                    if (start == goal) continue;

                    queue<pair<pair<int,int>,string>> q;    
                    q.push(make_pair(start,""));
                    unordered_map<char,vector<string>> possible_combinations;
                    int dist = INT_MAX;

                    while(!q.empty())
                    {
                        pair<int,int> curr = q.front().first;
                        string s = q.front().second;

                        int row = curr.first;
                        int col = curr.second;

                        int new_r, new_c;

                        new_r = row + 1;
                        new_c = col;

                        if (new_r >= 0 && new_r <= 3 && new_c >= 0 && new_c < 3 && numpad[new_r][new_c] != 'N')
                        {
                            if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + "^");
                                q.push(next);
                            } 
                            else if (make_pair(new_r,new_c) == goal )
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    possible_combinations[numpad[new_r][new_c]].push_back(s + "^");
                                }
                                else 
                                {
                                    dist = s.size() + 1;
                                    possible_combinations[numpad[new_r][new_c]].push_back(s + "^");
                                }
                                
                            }         
                        }

                        new_r = row - 1;
                        new_c = col;

                        if (new_r >= 0 && new_r <= 3 && new_c >= 0 && new_c < 3 && numpad[new_r][new_c] != 'N')
                        {
                            if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + "v");
                                q.push(next);
                            } 
                            else if (make_pair(new_r,new_c) == goal )
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    possible_combinations[numpad[new_r][new_c]].push_back(s + "v");
                                }
                                else 
                                {
                                    dist = s.size() + 1;
                                    possible_combinations[numpad[new_r][new_c]].push_back(s + "v");
                                }
                                
                            }         
                        }

                        new_r = row;
                        new_c = col + 1;

                        if (new_r >= 0 && new_r <= 3 && new_c >= 0 && new_c < 3 && numpad[new_r][new_c] != 'N')
                        {
                            if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + ">");
                                q.push(next);
                            } 
                            else if (make_pair(new_r,new_c) == goal )
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    possible_combinations[numpad[new_r][new_c]].push_back(s + ">");
                                }
                                else 
                                {
                                    dist = s.size() + 1;
                                    possible_combinations[numpad[new_r][new_c]].push_back(s + ">");
                                }
                                
                            }         
                        }

                        new_r = row;
                        new_c = col - 1;

                        if (new_r >= 0 && new_r <= 3 && new_c >= 0 && new_c < 3 && numpad[new_r][new_c] != 'N')
                        {
                            if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + "<");
                                q.push(next);
                            } 
                            else if (make_pair(new_r,new_c) == goal )
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    possible_combinations[numpad[new_r][new_c]].push_back(s + "<");
                                }
                                else 
                                {
                                    dist = s.size() + 1;
                                    possible_combinations[numpad[new_r][new_c]].push_back(s + "<");
                                }
                                
                            }         
                        }

                    }
                    
                    num_map[numpad[r][c]][numpad[g_row][g_col]] = possible_combinations;
                }
                
            }
                
            

        }
    }

            
            
            

    
    


}