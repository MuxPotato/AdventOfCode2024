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
Part 1: 99448

We utilize dijkstra's algo, with a grid based coordination system

*/


using namespace std;

struct CustomComparator 
{
    bool operator()(vector<int> a, vector<int> b)
    {
        return a[3] > b[3];
    }
};

int main()
{
    //ifstream fin("in.txt");
    ifstream fin("sample.txt");
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
    dist[start_pt.first][start_pt.second][1] = 1000;
    dist[start_pt.first][start_pt.second][2] = 2000;
    dist[start_pt.first][start_pt.second][3] = 1000;
    

    while(!pq.empty())
    {
        vector<int> curr = pq.top(); pq.pop();

        int curr_row = curr[0];
        int curr_col = curr[1];
        int curr_direction = curr[2];
        int curr_weight = curr[3];

        //if (matrix[curr_row][curr_col] == 'E') break;

        // Impt check
        if (curr_weight > dist[curr_row][curr_col][curr_direction]) continue;

        

        cout << "curr_row: " << curr_row << " curr_col: " << curr_col << " curr_direction: " << curr_direction << " curr_weight: " << curr_weight << endl;

        

        int r,c;
        int cost;

        // Up
        r = curr_row - 1;
        c = curr_col;

        
        // No need matrix size check as the edges are all #
        if (matrix[r][c] != '#')
        {
            if (curr_direction == 1) cost = 1;
            else if (curr_direction == 3) cost = 2001;
            else cost = 1001;
            
            // TODO: is = needed here?
            int new_direction = 1;
            if(dist[r][c][new_direction] >=  curr_weight + cost) 
            {
                cout << "pushing row: " << r << " col: " << c << endl;
                pq.push({r,c,new_direction,curr_weight+cost});
                dist[r][c][new_direction] = curr_weight+cost;
            }
        }


        // Down
        r = curr_row + 1;
        c = curr_col;


        // No need matrix size check as the edges are all #
        if (matrix[r][c] != '#')
        {
            if (curr_direction == 3) cost = 1;
            else if (curr_direction == 1) cost = 2001;
            else cost = 1001;
            
            // TODO: is = needed here?
            int new_direction = 3;
            if(dist[r][c][new_direction] >=  curr_weight + cost) 
            {
                cout << "pushing row: " << r << " col: " << c << endl;
                pq.push({r,c,new_direction,curr_weight+cost});
                dist[r][c][new_direction] = curr_weight+cost;
            }
        }


         

        // Left
        r = curr_row;
        c = curr_col - 1;


        // No need matrix size check as the edges are all #
        if (matrix[r][c] != '#')
        {
            if (curr_direction == 2) cost = 1;
            else if (curr_direction == 0) cost = 2001;
            else cost = 1001;
            
            // TODO: is = needed here?
            int new_direction = 2;
            if(dist[r][c][new_direction] >=  curr_weight + cost) 
            {
                cout << "pushing row: " << r << " col: " << c << endl;
                
                pq.push({r,c,new_direction,curr_weight+cost});
                dist[r][c][new_direction] = curr_weight+cost;
            }
        }


        // Right
        r = curr_row;
        c = curr_col + 1;


        // No need matrix size check as the edges are all #
        if (matrix[r][c] != '#')
        {
           
            if (curr_direction == 0) cost = 1;
            else if (curr_direction == 2) cost = 2001;
            else cost = 1001;
            
            // TODO: is = needed here?
            int new_direction = 0;
            if(dist[r][c][new_direction] >=  curr_weight + cost) 
            {
                //cout << "pushing row: " << r << " col: " << c << endl;
                
                pq.push({r,c,new_direction,curr_weight+cost});
                dist[r][c][new_direction] = curr_weight+cost;
            }
        }
        

    }

    vector<int> end_pt_dists = dist[end_pt.first][end_pt.second];
    cout << "ans: " << *min_element(end_pt_dists.begin(), end_pt_dists.end()) << endl;


    
    // We run Dijkstra's algorithm again but this time from end point to start point

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

        // Impt check
        if (curr_weight > dist2[curr_row][curr_col][curr_direction]) continue;

        //cout << "curr_row: " << curr_row << " curr_col: " << curr_col << " curr_direction: " << curr_direction << " curr_weight: " << curr_weight << endl;

        

        int r,c;
        int cost;

        // Up
        r = curr_row - 1;
        c = curr_col;

        
        // No need matrix size check as the edges are all #
        if (matrix[r][c] != '#')
        {
            if (curr_direction == 3) cost = 1;
            else if (curr_direction == 1) cost = 2001;
            else cost = 1001;
            
            // TODO: is = needed here?
            int new_direction = 3;
            if(dist2[r][c][new_direction] >=  curr_weight + cost) 
            {
                ///cout << "pushing row: " << r << " col: " << c << endl;
                pq2.push({r,c,new_direction,curr_weight+cost});
                dist2[r][c][new_direction] = curr_weight+cost;
            }
        }


        // Down
        r = curr_row + 1;
        c = curr_col;


        // No need matrix size check as the edges are all #
        if (matrix[r][c] != '#')
        {
            if (curr_direction == 1) cost = 1;
            else if (curr_direction == 3) cost = 2001;
            else cost = 1001;
            
            // TODO: is = needed here?
            int new_direction = 1;
            if(dist2[r][c][new_direction] >=  curr_weight + cost) 
            {
                //cout << "pushing row: " << r << " col: " << c << endl;
                pq2.push({r,c,new_direction,curr_weight+cost});
                dist2[r][c][new_direction] = curr_weight+cost;
            }
        }


         

        // Left
        r = curr_row;
        c = curr_col - 1;


        // No need matrix size check as the edges are all #
        if (matrix[r][c] != '#')
        {
            if (curr_direction == 0) cost = 1;
            else if (curr_direction == 2) cost = 2001;
            else cost = 1001;
            
            // TODO: is = needed here?
            int new_direction = 0;
            if(dist2[r][c][new_direction] >=  curr_weight + cost) 
            {
                //cout << "pushing row: " << r << " col: " << c << endl;
                
                pq2.push({r,c,new_direction,curr_weight+cost});
                dist2[r][c][new_direction] = curr_weight+cost;
            }
        }


        // Right
        r = curr_row;
        c = curr_col + 1;


        // No need matrix size check as the edges are all #
        if (matrix[r][c] != '#')
        {
           
            if (curr_direction == 2) cost = 1;
            else if (curr_direction == 0) cost = 2001;
            else cost = 1001;
            
            // TODO: is = needed here?
            int new_direction = 2;
            if(dist2[r][c][new_direction] >=  curr_weight + cost) 
            {
                //cout << "pushing row: " << r << " col: " << c << endl;
                
                pq2.push({r,c,new_direction,curr_weight+cost});
                dist2[r][c][new_direction] = curr_weight+cost;
            }
        }
        

    }


    // Using first traversal 
    int best_path_weight = *min_element(end_pt_dists.begin(), end_pt_dists.end());

    // Now we check for every point 
    // If dist[r][c] + dist2[r][c] = best_path_weight, the node is part of at least 1 best path
    set<pair<int,int>> ans;

    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[0].size(); j++)
        {
            vector<int> dists_from_start = dist[i][j];
            vector<int> dists_from_end = dist2[i][j];

            // for(int k = 0; k < 4; k++)
            // {
            //     if (dists_from_start[k] + dists_from_end[] == best_path_weight) ans++;
            // }
            // curr_direction -> East:0 North:1 West:2 South:3  

            for(int k = 0; k < 4; k++)
            {
                for(int r = 0; r < 4; r++)
                {
                    if (dists_from_start[k] + dists_from_end[r] == best_path_weight) 
                    {
                        ans.insert(make_pair(i,j));
                    }
                }
            }
            // if (dists_from_start[0] + dists_from_end[2] == best_path_weight) ans++;
            // if (dists_from_start[2] + dists_from_end[0] == best_path_weight) ans++;
            // if (dists_from_start[1] + dists_from_end[3] == best_path_weight) ans++;
            // if (dists_from_start[3] + dists_from_end[1] == best_path_weight) ans++;




            // int min_dist_from_start = *min_element(dists_from_start.begin(), dists_from_start.end());
            // int min_dist_from_end = *min_element(dists_from_end.begin(), dists_from_end.end());


            
            // if (min_dist_from_start + min_dist_from_end == best_path_weight) ans++;
        }
    }
    

    cout << "ans: " << ans.size() << endl;

}