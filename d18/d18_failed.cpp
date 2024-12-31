#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
/*
Part 1: 

We utilize dijkstra's algo

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


double get_dist_from_end(int idx, int end_idx)
{
    int row = idx / 71;
    int col = idx % 71;

    int end_row = end_idx / 71;
    int end_col = end_idx % 71;

    return sqrt( (double)(pow(end_row - row, 2)) + (double)(pow(end_col - col,2)));
}


int main()
{
    //ifstream fin("in.txt");
    ifstream fin("sample.txt");
    string line;
    

    int total_rows = 71;
    int total_cols = 71;

    // int total_rows = 7;
    // int total_cols = 7;

    vector<string> matrix(total_rows, string(total_cols, '.'));

    int count = 0;
    int stop_count = 1024;
    //stop_count = 12;
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

    unordered_set<int> visited;

    //return 0;
    vector<vector<pair<int,int>>> AL(total_rows * total_cols, vector<pair<int,int>>());

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
                AL[row*total_cols + col].push_back(make_pair(r*total_cols + c, 1));
            }

            r = row - 1;
            c = col;

            if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
            {
                AL[row*total_cols + col].push_back(make_pair(r*total_cols + c, 1));
            }

            r = row;
            c = col + 1;

            if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
            {
                AL[row*total_cols + col].push_back(make_pair(r*total_cols + c, 1));
            }

            r = row;
            c = col - 1;

            if (r >= 0 && r < total_rows && c >= 0 && c < total_cols && matrix[r][c] != '#')
            {
                AL[row*total_cols + col].push_back(make_pair(r*total_cols + c, 1));
            }
        }
    }

    // 1. curr_weight 2. dist_from_end_point 3. idx
    priority_queue<vector<int>, vector<vector<int>>, CustomComparator> pq;
    vector<int> dist(total_rows * total_cols, INT_MAX);
    dist[0] = 0;



    pq.push({0,static_cast<int>(get_dist_from_end(0,total_cols*total_rows-1)),0});
  

    while(!pq.empty())
    {
        vector<int> curr = pq.top(); pq.pop();

        
        
        int curr_idx = curr[2];
        int curr_weight = curr[0];

        if (curr_idx == total_cols * total_rows - 1) break;
        

        

        if (curr_weight > dist[curr_idx]) continue;
        //cout << "curr_idx : " << curr_idx << endl; 
        for(auto &pair : AL[curr_idx])
        {
            int idx = pair.first;
            int w = pair.second;

            if (dist[idx] < curr_weight + w) continue;

            dist[idx] = curr_weight + w;
            
            pq.push({dist[idx], static_cast<int>(get_dist_from_end(idx,total_cols*total_rows-1)), idx}); 
        }
    }

    cout << "ans: " << dist[total_rows * total_cols - 1] << endl;

}