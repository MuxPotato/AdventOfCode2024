#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>


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


    // Here we assume start and end points are at the corners of the maze
    pair<int,int> start_pt = make_pair(matrix.size() - 2, 1);
    pair<int,int> end_pt =  make_pair(1, matrix[0].size() - 2);


    // Vector<int> holds 1. row 2. col 3. curr_direction 4. weight so far
    // curr_direction -> East:0 North:1 West:2 South:3  
    priority_queue<vector<int>, vector<vector<int>>, CustomComparator> pq;
    vector<int> start = {start_pt.first, start_pt.second, 0, 0};
    pq.push(start);

    vector<vector<int>> dist(matrix.size(), vector<int>(matrix[0].size(), INT_MAX));
    dist[start_pt.first][start_pt.second] = 0;

    while(!pq.empty())
    {
        vector<int> curr = pq.top(); pq.pop();

        int curr_row = curr[0];
        int curr_col = curr[1];
        int curr_direction = curr[2];
        int curr_weight = curr[3];

        // Impt check
        if (curr_weight > dist[curr_row][curr_col]) continue;

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
            if(dist[r][c] >=  curr_weight + cost) 
            {
                cout << "pushing row: " << r << " col: " << c << endl;
                pq.push({r,c,1,curr_weight+cost});
                dist[r][c] = curr_weight+cost;
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
            if(dist[r][c] >=  curr_weight + cost) 
            {
                cout << "pushing row: " << r << " col: " << c << endl;
                pq.push({r,c,3,curr_weight+cost});
                dist[r][c] = curr_weight+cost;
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
            if(dist[r][c] >=  curr_weight + cost) 
            {
                cout << "pushing row: " << r << " col: " << c << endl;
                pq.push({r,c,2,curr_weight+cost});
                dist[r][c] = curr_weight+cost;
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
            if(dist[r][c] >=  curr_weight + cost) 
            {
                //cout << "pushing row: " << r << " col: " << c << endl;
                pq.push({r,c,0,curr_weight+cost});
                dist[r][c] = curr_weight+cost;
            }
        }
        

    }

    cout << "ans: " << dist[end_pt.first][end_pt.second] << endl;

    int best_path_weight = dist[end_pt.first][end_pt.second];


    queue<pair<vector<int>,unordered_set<int>>> q;
    unordered_set<int> set; set.insert(start_pt.first * matrix[0].size() + start_pt.second);
    start = {start_pt.first, start_pt.second, 0, 0};
    q.push({start,set});

    unordered_set<int> ans_set;
    
    while(!q.empty())
    {
        vector<int> info = q.front().first;
        unordered_set<int> visited = q.front().second;
        q.pop();

        


        int curr_row = info[0];
        int curr_col = info[1];
        int curr_direction = info[2];
        int curr_weight = info[3];      

        //cout << "curr_row: " << curr_row << " curr_col: " << curr_col << endl;

        if(matrix[curr_row][curr_col] == 'E')
        {
            if(curr_weight == best_path_weight)
            {
                for(const auto& val : visited) ans_set.insert(val);
            }
            continue;
        }  

        if (curr_weight > best_path_weight) continue;

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
            
            if(visited.find(r*matrix[0].size() + c) == visited.end()) 
            {
                
                vector<int> new_info = {r,c,1,curr_weight+cost};
                visited.insert(r*matrix[0].size() + c);
                q.push({new_info,visited});
                visited.erase(r*matrix[0].size() + c);     
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
            
            if(visited.find(r*matrix[0].size() + c) == visited.end()) 
            {
                
                vector<int> new_info = {r,c,3,curr_weight+cost};
                visited.insert(r*matrix[0].size() + c);
                q.push({new_info,visited});
                visited.erase(r*matrix[0].size() + c);        
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
            
            if(visited.find(r*matrix[0].size() + c) == visited.end()) 
            {
                
                vector<int> new_info = {r,c,2,curr_weight+cost};
                visited.insert(r*matrix[0].size() + c);
                q.push({new_info,visited});
                visited.erase(r*matrix[0].size() + c);          
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
            
            if(visited.find(r*matrix[0].size() + c) == visited.end()) 
            {
                
                vector<int> new_info = {r,c,0,curr_weight+cost};
                visited.insert(r*matrix[0].size() + c);
                q.push({new_info,visited});
                visited.erase(r*matrix[0].size() + c);          
            }
        }


    }


    int ans = 0;
    for(const int &val : ans_set)
    {
        ans++;
    }
    cout << "ans: " << ans << endl;
    



}