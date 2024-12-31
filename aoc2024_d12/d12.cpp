#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
#include <unordered_map>
#include <set>
/*
Part 2 Ans: 881182

Solution: The strategy here is to count the number of corners one region has, the number of corners == number of sides 

We first get the region and each cell that belong to that region (similar to part 1)
Then we process each region accordingly


Notes:
    1. We represent every corner using 0.5 floating numbers. (See picture to understand better)
    2. We can tell whether a corner is a valid corner by looking at the 4 quadrants around it.
    3. The range out of bound checking has to be altered due to the 0.5
    4. Rmb to use floating points, I used int and was debugging for a while 
*/

using namespace std;

int get_corners(vector<pair<int,int>> &region, int total_rows, int total_cols, vector<string> &matrix)
{
    unordered_set<int> set;
    for(auto i : region)
    {
        set.insert(i.first*total_cols + i.second);
    }

    vector<pair<char, pair<float,float>>> corners;
    vector<pair<float,float>> moves = {{-0.5,-0.5}, {-0.5,0.5}, {0.5,-0.5}, {0.5,0.5}};
    for(auto i : region)
    {
        char letter = matrix[i.first][i.second];
        for(auto move : moves)
        {
            float r = static_cast<float>(i.first) + move.first;
            float c = static_cast<float>(i.second) + move.second;

            if(r < -0.5 || r >= total_rows + 0.5 || c < -0.5 || c >= total_cols + 0.5) continue;
            corners.push_back(make_pair(letter,make_pair(r,c)));

            cout << " r: " << r << " c: " << c << "   ";
        }
    }

 
 

    std::set<std::pair<float,float>> visited;
    int ans = 0;
    for(auto corner : corners)
    {
        char letter = corner.first;
        pair<float,float> coord = corner.second;

        if(visited.find(coord) != visited.end()) continue;
        visited.insert(coord);

        cout << "coord r: " << coord.first << " c:" << coord.second << endl;

        // representing q1,q2,q3,q4
        vector<bool> quadrants = {false, false, false , false};

        // notice how the vector "moves" is how we get from corner to q1 q2 q3 q4 already
        for(int i = 0; i < 4; i++)
        {
            pair<float,float> move = moves[i];
            float r = coord.first + move.first;
            float c = coord.second + move.second;

            if(r < 0 || r >= total_rows || c < 0 || c >= total_cols) continue;
            
            if (set.find(r*total_cols + c) != set.end()) quadrants[i] = true;
        }

        
        int count = 0;
        int num_of_corners = 0;
        for(bool b : quadrants) 
        {
            if(b) 
            {
                cout << "true ";
                count++;
            }
            else cout << "false ";
        }
        cout << endl;

        if(count == 1 || count == 3) num_of_corners++;
        else if (count == 2)
        {
            // q1 and q4 OR q2 and q3
            if((quadrants[0] && quadrants[3]) || (quadrants[1] && quadrants[2])) num_of_corners += 2;
        }
        ans += num_of_corners;

    }
    return ans;
 
}




int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    
    vector<string> matrix;

    while(getline(fin,line))
    {
        if (line.empty()) break;
        matrix.push_back(line);
    }

    int total_rows = matrix.size();
    int total_cols = matrix[0].size();

    vector<pair<int,int>> moves = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    unordered_set<int> visited;
    
    vector<vector<pair<int,int>>> regions;
    for(int r = 0; r < total_rows; r++)
    {
        for(int c = 0; c < total_cols; c++)
        {
            int idx = r*total_cols + c;
            if(visited.find(idx) != visited.end()) continue; 

            queue<pair<int,int>> q;
            q.push(make_pair(r,c));
            visited.insert(idx);

            char letter = matrix[r][c];
            vector<pair<int,int>> new_region = {make_pair(r,c)};

            while(!q.empty())
            {
                pair<int,int> curr = q.front(); q.pop();
                
                for(pair<int,int> move : moves)
                {
                    int curr_r = curr.first;
                    int curr_c = curr.second;
                    curr_r += move.first;
                    curr_c += move.second;
                    if(curr_r < 0 || curr_r >= total_rows || curr_c < 0 || curr_c >= total_cols) continue;

                    if(matrix[curr_r][curr_c] == letter && visited.find(curr_r*total_cols + curr_c) == visited.end())
                    {
                        q.push(make_pair(curr_r,curr_c));
                        new_region.push_back(make_pair(curr_r,curr_c));
                        visited.insert(curr_r*total_cols + curr_c);
                    }

                }
            }

            regions.push_back(new_region);

        }
    }


    int ans = 0;

    for(auto region : regions)
    {
        int corners = get_corners(region,total_rows,total_cols,matrix);
        int area = region.size();
        cout << "letter: " << matrix[region[0].first][region[0].second] << " corners: " << corners << " area: " << area << " price: " << corners*area << endl;
        ans += corners*area;
        cout << "num of corners: " << corners << endl;
    }

    cout << "ans: " << ans << endl;

}