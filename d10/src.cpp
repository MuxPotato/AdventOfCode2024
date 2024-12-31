// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 1 Answer:  512

Solution: Create a graph where one can travel to its neighbors if num = neigh_num - 1;

Then use BFS on each starting point with 0, and see how many 9 u can reach


Part 2 Answer: 1045

Part 2 is literally part 1, but now u can revisit nodes, so we remove the visited set used in Part 1 answer
We are confident that we will not revisit the same path multiple times, bcs there is no way of getting to the same starting node again as 
the starting node is the lowest number

The differences between Part 1 vs Part 2

**Part 1**: You're counting **how many distinct 9-height positions are reachable** from a given trailhead (a cell with height 0). Each 9 is counted once, no matter how many different paths lead to it.

**Part 2**: You're counting **the total number of distinct paths** from a trailhead (height 0) to any 9-height position. Instead of just knowing which 9s you can reach, you now care about every unique route that gets you there.

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
#include <queue>
using namespace std;








int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    vector<vector<int>> matrix;
    std::string line;    
    
    while (std::getline(fin, line))
    {
        if(line.empty()) break;
        vector<int> temp;
        istringstream iss(line);
        char i;
        while(iss >> i)
        {
            temp.push_back(int(i - '0'));
        }
        matrix.push_back(temp);
    }

    for(int row = 0; row < matrix.size(); row++)
    {
        for(int col = 0; col < matrix[0].size(); col++)
        {   
            cout << matrix[row][col];
        }
        cout << endl;
    }


    vector<vector<int>> AL(matrix.size() * matrix[0].size(), vector<int>());

    for(int row = 0; row < matrix.size(); row++)
    {
        for(int col = 0; col < matrix[0].size(); col++)
        {
            int idx = row*matrix[0].size() + col;

            int num = matrix[row][col];

            int r,c;

            r = row - 1;
            c = col;

            if(r >= 0 && r < matrix.size() && c >= 0 && c < matrix[0].size())
            {
                int num2 = matrix[r][c];

                if (num2 == num + 1) AL[idx].push_back(r*matrix[0].size() + c);
            }


            r = row + 1;
            c = col;

            if(r >= 0 && r < matrix.size() && c >= 0 && c < matrix[0].size())
            {
                int num2 = matrix[r][c];

                if (num2 == num + 1) AL[idx].push_back(r*matrix[0].size() + c);
            }

            r = row;
            c = col - 1;

            if(r >= 0 && r < matrix.size() && c >= 0 && c < matrix[0].size())
            {
                int num2 = matrix[r][c];

                if (num2 == num + 1) AL[idx].push_back(r*matrix[0].size() + c);
            }

            r = row;
            c = col + 1;

            if(r >= 0 && r < matrix.size() && c >= 0 && c < matrix[0].size())
            {
                int num2 = matrix[r][c];

                if (num2 == num + 1) AL[idx].push_back(r*matrix[0].size() + c);
            }
        }
    }

    

    int ans = 0;
    for(int row = 0; row < matrix.size(); row++)
    {
        for(int col = 0; col < matrix[0].size(); col++)
        {
            if(matrix[row][col] != 0) continue; // we only care about 0

            cout << "starting at: row: " << row << " col: " << col << endl;
            int idx = row*matrix[0].size() + col;

      
            queue<int> q; q.push(idx);
            
            // Part 1
            //set<int> visited; 
            //visited.insert(idx);

            while(!q.empty())
            {
                cout << "at row: " << row << " col: " << col << endl;
                int curr_idx = q.front(); q.pop();

                cout << "curr_idx : " << curr_idx << endl;
                
                int r = curr_idx / matrix[0].size();
                int c = curr_idx % matrix[0].size();



                if (matrix[r][c] == 9) ans++;

                // Part 2
                for(int i: AL[curr_idx])
                {             
                    q.push(i);  
                }

                // // Part 1
                // for(int i: AL[curr_idx])
                // {
                //     if(visited.find(i) == visited.end())
                //     {
                //         visited.insert(i);
                //         q.push(i);
                //     }
                // }
            }
        }
    }

    cout << "ans: " << ans << endl;
    



    





}

