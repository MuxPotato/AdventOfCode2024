#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
#include <algorithm>
/*
Part 1: 354

We utilize BFS as it is an unweighted graph

Notes: Djkstra's Algo is way overkill and way too slow


Part 2: 36,17

Same as part 1 but we just keep running BFS while adding the additional obstacle and removing all of its neighbors connection to it

*/


using namespace std;


struct CustomComparator 
{
    bool operator()(vector<int> a, vector<int> b)
    {
        if (a[0] != b[0]) return a[0] > b[0];
        return a[1] > b[1];
    }
};


// double get_dist_from_end(int idx, int end_idx)
// {
//     int row = idx / 71;
//     int col = idx % 71;

//     int end_row = end_idx / 71;
//     int end_col = end_idx % 71;

//     return sqrt( (double)(pow(end_row - row, 2)) + (double)(pow(end_col - col,2)));
// }


int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    

    int total_rows = 71;
    int total_cols = 71;

    // int total_rows = 7;
    // int total_cols = 7;

    vector<string> matrix(total_rows, string(total_cols, '.'));

    int count = 0;
    int stop_count = 1024;
    //int stop_count = 12;
    while(getline(fin,line) && count < stop_count)
    {
        if (line.empty()) break;
        istringstream iss(line);
        
        int row,col;
        iss >> col; iss.ignore(1); iss >> row;
        matrix[row][col] = '#'; 
        count++;
    }

    for(string s : matrix)
    {
        cout << s << endl;
    }


    //return 0;
    vector<vector<int>> AL(total_rows * total_cols, vector<int>());

    for(int row = 0; row < total_rows; row++)
    {
        for(int col = 0; col < total_cols; col++)
        {
            if(matrix[row][col] == '#') continue;
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



    

    while(1)
    {
        getline(fin, line);
        istringstream iss(line);
        
        int row,col;
        iss >> col; iss.ignore(1); iss >> row;
        matrix[row][col] = '#'; 

        int idx = row*total_cols + col;
        AL[idx] = vector<int>();
        
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


        unordered_set<int> visited;
        bool reachable = false;
        queue<pair<int,int>> q;
        q.push(make_pair(0,0));
        visited.insert(0);
        while(!q.empty())
        {
            int curr = q.front().first;
            int w = q.front().second;

            if(curr == AL.size() - 1) 
            {
                reachable = true;
                break;
            }

            q.pop();
            for(int i : AL[curr])
            {
                if (visited.find(i) == visited.end())
                {
                    q.push(make_pair(i, w + 1));
                    visited.insert(i);
                }
            }
        }
        

        if (!reachable) 
        {
            cout << "ans  col: " << col << " row: " << row << endl;
            break;
        }
        else
        {
            cout << "reachable" << endl;
        }

    }


   

}