#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
#include <algorithm>
#include <unordered_map>
/*
Part 1 Answer:



*/

using namespace std;

void link_new_cell(vector<vector<int>> &AL, vector<string> matrix, int row, int col)
{
    int total_rows = matrix.size();
    int total_cols = matrix[0].size();
    int idx = row*total_cols + col;

    // Adding the edges for the cell itself to neighbors and the neighbor to itself
    int r,c;

    r = row + 1;
    c = col;

    if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
    {
        AL[idx].push_back(r*total_cols + c);
        AL[r*total_cols + c].push_back(idx);
    }

    r = row - 1;
    c = col;

    if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
    {
        AL[idx].push_back(r*total_cols + c);
        AL[r*total_cols + c].push_back(idx);
    }

    r = row;
    c = col + 1;

    if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
    {
        AL[idx].push_back(r*total_cols + c);
        AL[r*total_cols + c].push_back(idx);
    }

    r = row;
    c = col - 1;

    if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
    {
        AL[idx].push_back(r*total_cols + c);
        AL[r*total_cols + c].push_back(idx);
    }
}

void delink_new_cell(vector<vector<int>> &AL, vector<string> matrix, int row, int col)
{
    int total_rows = matrix.size();
    int total_cols = matrix[0].size();
    int idx = row*total_cols + col;

    AL[idx] = vector<int>();



    // Removing the edges from neighbors to itself
    int r,c;

    r = row + 1;
    c = col;

    if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
    {
        auto it = find(AL[r*total_cols + c].begin(), AL[r*total_cols + c].end(), idx);
        AL[r*total_cols + c].erase(it);
    }

    r = row - 1;
    c = col;

    if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
    {
        auto it = find(AL[r*total_cols + c].begin(), AL[r*total_cols + c].end(), idx);
        AL[r*total_cols + c].erase(it);
    }

    r = row;
    c = col + 1;

    if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
    {
        auto it = find(AL[r*total_cols + c].begin(), AL[r*total_cols + c].end(), idx);
        AL[r*total_cols + c].erase(it);
    }

    r = row;
    c = col - 1;

    if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
    {
        auto it = find(AL[r*total_cols + c].begin(), AL[r*total_cols + c].end(), idx);
        AL[r*total_cols + c].erase(it);
    }

}



int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    
    vector<string> matrix;

    while(getline(fin,line))
    {
        matrix.push_back(line);
    }

    int total_rows = matrix.size();
    int total_cols = matrix[0].size();
    
    // x,y
    int start_idx, end_idx;


    vector<vector<int>> AL(total_rows * total_cols, vector<int>());

    for(int row = 0; row < total_rows; row++)
    {
        for(int col = 0; col < total_cols; col++)
        {
            if(matrix[row][col] == '#') continue;

            if (matrix[row][col] == 'S')
            {
                start_idx = row*total_cols + col;
            }
            else if (matrix[row][col] == 'E')
            {
                end_idx = row*total_cols + col;
            }

            int r,c;

            r = row + 1;
            c = col;

            if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
            {
                AL[row*total_cols + col].push_back(r*total_cols + c);
            }

            r = row - 1;
            c = col;

            if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
            {
                AL[row*total_cols + col].push_back(r*total_cols + c);
            }

            r = row;
            c = col + 1;

            if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
            {
                AL[row*total_cols + col].push_back(r*total_cols + c);
            }

            r = row;
            c = col - 1;

            if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
            {
                AL[row*total_cols + col].push_back(r*total_cols + c);
            }
        }
    }


    int normal_dist;

    unordered_set<int> visited1;
    queue<pair<int,int>> q1;
    q1.push(make_pair(start_idx,0));
    visited1.insert(start_idx);
    while(!q1.empty())
    {
        int curr = q1.front().first;
        int w = q1.front().second;

        if(curr == end_idx) 
        {
            normal_dist = w;
            break;
        }

        q1.pop();
        for(int i : AL[curr])
        {
            if (visited1.find(i) == visited1.end())
            {
                q1.push(make_pair(i, w + 1));
                visited1.insert(i);
            }
        }
    }

    //unordered_map<int,int> debug;

    int ans = 0; 
    for(int row = 0; row < total_rows; row++)
    {
        for(int col = 0; col < total_cols; col++)
        {
            cout << "row: " << row << " col: " << col << endl;
            if(matrix[row][col] != '#') continue;

            link_new_cell(AL, matrix, row, col);


            unordered_set<int> visited;
            queue<pair<int,int>> q;
            q.push(make_pair(start_idx,0));
            visited.insert(start_idx);
            while(!q.empty())
            {
                int curr = q.front().first;
                int w = q.front().second;
                q.pop();

                if (w > normal_dist) continue;

                if(curr == end_idx) 
                {
                    if (normal_dist - w >= 100) ans++;

                    // if (normal_dist - w > 0) 
                    // {
                    //     debug[normal_dist-w]++;
                    //     //cout << "saves: " << normal_dist - w << endl;
                    // }

                    
                    
                    
                    break;
                }

                
                for(int i : AL[curr])
                {
                    if (visited.find(i) == visited.end())
                    {
                        q.push(make_pair(i, w + 1));
                        visited.insert(i);
                    }
                }
            }

            delink_new_cell(AL,matrix,row,col);


        }
    }

    // for(auto pair : debug)
    // {
    //     cout << "There are " << pair.second << " cheats that saves: " << pair.first << endl;
    //     //cout << "saves: " << pair.first << " number: " << pair.second << endl;
    // }

    cout << "ans: " << ans << endl;


   

}