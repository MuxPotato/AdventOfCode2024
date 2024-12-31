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
#include <set>
/*
Part 1 Answer: 1402

Notes 
1. There is only 1 possible path

Solution: compute the distance to reach all cells first, then go thru each cell and try to "cheat" by going to another cell in two moves according to the vector moves. 
If dist[start_cell] + 2 < dist[end_cell] you are saving time 

The reason for the +2 is bcs even if u can cheat, u still need 2 sec to reach the end cell from the start cell

so to find cheats that at least save 100 seconds, we do this 
dist[new_idx] - dist[curr_idx] - 2 >= 100


*/

using namespace std;





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

    vector<int> dist(total_rows*total_cols, -1);


    queue<pair<int,int>> q;
    q.push(make_pair(start_idx,0));
    dist[start_idx] = 0;

    while(!q.empty())
    {
        int curr = q.front().first;
        int w = q.front().second;
        q.pop();
        for(int i : AL[curr])
        {
            if (dist[i] == -1)
            {
                q.push(make_pair(i, w + 1));
                dist[i] = w + 1;
            }
        }
    }
    int count = 0;
    for(auto d : dist)
    {
        count++;
        if (d >= 0 && d < 10) cout << " " << d << " "; 
        else cout << d << " ";
        if(count == total_cols) 
        {
            cout << endl;
            count = 0;
        }
    }

    vector<pair<int,int>> moves = {{2,0}, {-2,0}, {0,2}, {0,-2}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    


    int ans = 0;
    for(int row = 0; row < total_rows; row++)
    {
        for(int col = 0; col < total_cols; col++)
        {
            if(matrix[row][col] == '#') continue;
            int curr_idx = row*total_cols + col;
            for(auto &move : moves)
            {
                int r = row + move.first;
                int c = col + move.second;
                int new_idx = r*total_cols + c;

                pair<int,int> check_pair;
                if (new_idx < curr_idx) check_pair = make_pair(new_idx, curr_idx);
                else check_pair = make_pair(curr_idx, new_idx);

                if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && dist[new_idx] - dist[curr_idx] - 2 >= 100 && matrix[r][c] != '#')
                {
                    
                    
                    // if (dist[new_idx] - dist[curr_idx] == 6)
                    // {
                    //     cout << "start " << "r: " << row << " c:" << col << " end r:" << r << " c:" << c;
                    //     cout << " saving: " << dist[new_idx] - dist[curr_idx] << endl;
                    //     ans++;
                    // }
                    
                    cout << "start " << "r: " << row << " c:" << col << " end r:" << r << " c:" << c;
                    cout << " saving: " << dist[new_idx] - dist[curr_idx] - 2 << endl;
                    
                    
                    ans++;
                }

            }
            
        }
    }
    cout << "ans: " << ans << endl;
    


   

}

// for(int row = 0; row < total_rows; row++)
// {
//     for(int col = 0; col < total_cols; col++)
//     {
//         if(matrix[row][col] == '#') continue;
//         int curr_idx = row*total_cols + col;
//         for(auto &move : moves)
//         {
//             int r = row + move.first;
//             int c = col + move.second;
//             int new_idx = r*total_cols + c;

//             pair<int,int> check_pair;
//             if (new_idx < curr_idx) check_pair = make_pair(new_idx, curr_idx);
//             else check_pair = make_pair(curr_idx, new_idx);

//             if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && dist[new_idx] - dist[curr_idx] > 0 && ans.find(check_pair) == ans.end() && matrix[r][c] != '#')
//             {
//                 cout << "start: " << "r: " << ""

//                 cout << "saving: " << dist[new_idx] - dist[curr_idx] << endl;
//                 if (new_idx < curr_idx) ans.insert(make_pair(new_idx, curr_idx));
//                 else ans.insert(make_pair(curr_idx, new_idx));
//             }

//         }
        
//     }
// }