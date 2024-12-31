#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <set>

/*
Part 2: 498

Objective: Find every node that is part of at least 1 shortest path
Approach: We run Dijkstra's algorithm from start to end, and then end to start

If for a cell, path's weight from start + path's weight from end = best path weight
It is a node that is part of at least 1 shortest path

The tricky part is to recongize that, u need to inverse the direction for path's weight from end 
Bcs from the end we are going in the "opposite direction"

hence we have this condition
if (dists_from_start[modulo(k-2,4)] + dists_from_end[k] == best_path_weight)  

The modulo function is for convenient as modulo operator in C++ follows the sign of the dividend, so if u have -1 % 4, u get -1 instead of 3
*/


using namespace std;

struct CustomComparator 
{
    bool operator()(vector<int> a, vector<int> b)
    {
        return a[3] > b[3];
    }
};

int modulo(int a, int b)
{
    return (a % b + b) % b;
}

// East:0 North:1 West:2 South:3  
int map_dir(char c)
{
    if (c == 'E') return 0;
    else if (c == 'N') return 1;
    else if (c == 'W') return 2;
    else if (c == 'S') return 3;
    else return -1;
}


int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample2.txt");
    string line;
    vector<string> matrix;

    while(getline(fin,line))
    {
        if (line.empty()) break;
        matrix.push_back(line);
    }


    for(string s : matrix)
    {
        cout << s << endl;
    }


    


    int total_rows = matrix.size();
    int total_cols = matrix[0].size();
    
    // 3D Array, [row][col][direction] where the innermost holds vector<int> = {row, col, direction, weight}
    // East:0 North:1 West:2 South:3  
    vector<vector<vector<vector<vector<int>>>>> AL(total_rows, vector<vector<vector<vector<int>>>>(total_cols, vector<vector<vector<int>>>(4, vector<vector<int>>())));

    for(int i = 1; i < total_rows - 1; i++)
    {
        for(int j = 1; j < total_cols - 1; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                AL[i][j][k].push_back({i,j,modulo(k+1,4),1000 });
                AL[i][j][k].push_back({i,j,modulo(k-1,4),1000 });
            }
            
        }
    }


    for(int i = 1; i < total_rows - 1; i++)
    {
        for(int j = 1; j < total_cols - 1; j++)
        {
            
            int r,c;

            // Up
            r = i - 1;
            c = j;
            if(matrix[r][c] != '#') 
            {
                int dir = map_dir('N');
                AL[i][j][dir].push_back({r,c,dir,1});
            }

            // Down
            r = i + 1;
            c = j;
            if(matrix[r][c] != '#') 
            {
                int dir = map_dir('S');
                AL[i][j][dir].push_back({r,c,dir,1});
            }

            // Left
            r = i;
            c = j - 1;
            if(matrix[r][c] != '#') 
            {
                int dir = map_dir('W');
                AL[i][j][dir].push_back({r,c,dir,1});
            }

            // Right
            r = i;
            c = j + 1;
            if(matrix[r][c] != '#') 
            {
                int dir = map_dir('E');
                AL[i][j][dir].push_back({r,c,dir,1});
            }    
        }
    }
    



    // Here we assume start and end points are at the corners of the maze
    pair<int,int> start_pt = make_pair(matrix.size() - 2, 1);
    pair<int,int> end_pt =  make_pair(1, matrix[0].size() - 2);



    // Vector<int> holds 1. row 2. col 3. curr_direction 4. weight so far
    // curr_direction -> East:0 North:1 West:2 South:3  
    priority_queue<vector<int>, vector<vector<int>>, CustomComparator> pq;
    vector<int> start = {start_pt.first, start_pt.second, 0, 0};
    pq.push(start);

    vector<vector<vector<int>>> dist(matrix.size(), vector<vector<int>>(matrix[0].size(), vector<int>(4, INT_MAX)));

    dist[start_pt.first][start_pt.second][0] = 0;
    

    while(!pq.empty())
    {
        vector<int> curr = pq.top(); pq.pop();

        int curr_row = curr[0];
        int curr_col = curr[1];
        int curr_direction = curr[2];
        int curr_weight = curr[3];

        if (matrix[curr_row][curr_col] == 'E') break;

        // Impt check
        if (curr_weight > dist[curr_row][curr_col][curr_direction]) continue;

        
        vector<vector<int>> neighbors = AL[curr_row][curr_col][curr_direction];

        for(int i = 0; i < neighbors.size(); i++)
        {
            vector<int> neig = neighbors[i];
            int r = neig[0];
            int c = neig[1];
            int dir = neig[2];
            int w = neig[3];

            if (curr_weight + w >= dist[r][c][dir]) continue;
            
            dist[r][c][dir] = curr_weight + w;
            pq.push({r,c,dir,curr_weight+w});
        }
    }

    vector<int> end_pt_dists = dist[end_pt.first][end_pt.second];
    int best_path_weight = *min_element(end_pt_dists.begin(), end_pt_dists.end());
    cout << "ans: " << best_path_weight << endl;


    
    // // We run Dijkstra's algorithm again but this time from end point to start point
    // Vector<int> holds 1. row 2. col 3. curr_direction 4. weight so far
    // curr_direction -> East:0 North:1 West:2 South:3  
    priority_queue<vector<int>, vector<vector<int>>, CustomComparator> pq2;
    vector<int> start2 = {end_pt.first, end_pt.second, 0, 0};
    vector<int> start3 = {end_pt.first, end_pt.second, 1, 0};
    vector<int> start4 = {end_pt.first, end_pt.second, 2, 0};
    vector<int> start5 = {end_pt.first, end_pt.second, 3, 0};
    pq2.push(start2);
    pq2.push(start3);
    pq2.push(start4);
    pq2.push(start5);

    vector<vector<vector<int>>> dist2(matrix.size(), vector<vector<int>>(matrix[0].size(), vector<int>(4, INT_MAX)));
    dist2[end_pt.first][end_pt.second][0] = 0;
    dist2[end_pt.first][end_pt.second][1] = 0;
    dist2[end_pt.first][end_pt.second][2] = 0;
    dist2[end_pt.first][end_pt.second][3] = 0;


    while(!pq2.empty())
    {
        vector<int> curr = pq2.top(); pq2.pop();

        int curr_row = curr[0];
        int curr_col = curr[1];
        int curr_direction = curr[2];
        int curr_weight = curr[3];

        if (matrix[curr_row][curr_col] == 'S') break;

        // Impt check
        if (curr_weight > dist2[curr_row][curr_col][curr_direction]) continue;

        
        vector<vector<int>> neighbors = AL[curr_row][curr_col][curr_direction];

        for(int i = 0; i < neighbors.size(); i++)
        {
            vector<int> neig = neighbors[i];
            int r = neig[0];
            int c = neig[1];
            int dir = neig[2];
            int w = neig[3];

            if (curr_weight + w >= dist2[r][c][dir]) continue;
            
            dist2[r][c][dir] = curr_weight + w;
            pq2.push({r,c,dir,curr_weight+w});
        }
    }


    set<pair<int,int>> ans;

    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[0].size(); j++)
        {
            vector<int> dists_from_start = dist[i][j];
            vector<int> dists_from_end = dist2[i][j];
            for(int k = 0; k < 4; k++)
            {
                // for(int z = 0; z < 4; z++)
                // {
                //     if (dists_from_start[k] + dists_from_end[z] == best_path_weight) 
                //     {
                //         ans.insert(make_pair(i,j));
                //         cout << "row: " << i + 1 << " col: " << j + 1 << endl;
                //     }
                // }

                // if (dists_from_start[k] + dists_from_end[k] == best_path_weight) 
                // {
                //     ans.insert(make_pair(i,j));
                //     cout << "row: " << i + 1 << " col: " << j + 1 << endl;
                // }
                
                if (dists_from_start[modulo(k-2,4)] + dists_from_end[k] == best_path_weight) 
                {
                    ans.insert(make_pair(i,j));
                    cout << "row: " << i + 1 << " col: " << j + 1 << endl;
                }

            }
        }
    }


    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[0].size(); j++)
        {
            if (ans.find(make_pair(i,j)) == ans.end())
            {
                cout << matrix[i][j];
            }       
            else cout << "O";
        }
        cout << endl;
    }

    cout << "ans: " << ans.size() << endl;
}

