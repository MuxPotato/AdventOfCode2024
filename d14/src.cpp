// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 1 Answer: 

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
#include <algorithm>
using namespace std;



/*
    Part 1 Answer: 231221760

    Impt Notes:
    1. There is a requirement that the robots in the middle do not count, just note that

    Solution:
    Use a unordered_map for both pos and vel. To calculate vel, we just add vel to pos, then mod the total_x or total_y 
    Additional care needs to be done for modulo function as in C++ -1 % 11 gives -1, as it follows the sign of the dividend (which is -1)


    Part 2: Answer: 6771

    We calculate the dist between each points to every other points and total all the dist up
    In order to find the second that the robots are the closest to each other
    The christmas tree looks really nice.
*/


int get_dist(pair<int,int> pos1, pair<int,int> pos2)
{
    return sqrt( pow(pos2.first - pos1.first,2) + pow(pos2.second - pos1.second, 2));
}


void print_state(unordered_map<int,pair<int,int>> pos, int total_x, int total_y)
{
    vector<vector<int>> matrix(total_y, vector<int>(total_x, 0));
    
    for(auto &p : pos)
    {
        pair<int,int> curr_pos = p.second;
        int x = curr_pos.first;
        int y = curr_pos.second;

        matrix[y][x]++;
    }

    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[0].size(); j++)
        {
            int curr = matrix[i][j];

            if (curr == 0) cout << ' ';
            else cout << curr;
        }
        cout << endl;
    }

}

long get_total_dist(unordered_map<int,pair<int,int>> pos, int id)
{
    long total_dist = 0;
    for(int i = 0; i < id; i++)
    {
        pair<int,int> pos1 = pos[i];
        for(int j = 0; j < id; j++)
        {
            if(i == j) continue;
            pair<int,int> pos2 = pos[j];
            total_dist += get_dist(pos1,pos2);
        }
    }
    return total_dist; 
}


/*
    Needed bcs in C++, the result of a mod takes the result of a (the dividend)
*/
int modulo(int a, int mod)
{
    return ((a % mod) + mod) % mod;
}


int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    unordered_map<int,pair<int,int>> vel;
    unordered_map<int,pair<int,int>> pos;

    
    std::string line;    
    int id = 0;
    while (std::getline(fin, line))
    {
        if(line.empty()) break;
        
        istringstream iss(line);
        char dummy;
        iss >> dummy; iss >> dummy;

        int pos_x; int pos_y;
        iss >> pos_x; iss >> dummy; iss >> pos_y;

        iss >> dummy; iss >> dummy;

        int vel_x; int vel_y;
        iss >> vel_x; iss >> dummy; iss >> vel_y;

        cout << "id: " << id << " pos_x: " << pos_x << " pos_y: " << pos_y << " vel_x: " << vel_x << " vel_y: " << vel_y << endl;
        pos[id] = make_pair(pos_x,pos_y);
        vel[id] = make_pair(vel_x,vel_y);

        id++;

    }

    int total_y = 103;
    int total_x = 101;


    //int total_y = 7;
    //int total_x = 11;

    int curr_sec = 1;
    
    vector<pair<int,int>> dist_with_sec;
    
    while(curr_sec <= 10000)
    {
        for(int i = 0; i < id; i++)
        {
            pair<int,int> curr_pos = pos[i];
            pair<int,int> curr_vel = vel[i];

            pos[i] = make_pair(modulo(curr_pos.first + curr_vel.first, total_x), modulo(curr_pos.second + curr_vel.second, total_y));
        }       
        

        
        
        long total_dist = get_total_dist(pos, id);
        dist_with_sec.push_back(make_pair(total_dist, curr_sec));

        

        cout << "START OF SEC: " << curr_sec << endl;
        print_state(pos, total_x, total_y);
        cout << endl;
        curr_sec++;
    }

    sort(dist_with_sec.begin(), dist_with_sec.end());

    for(auto &p : dist_with_sec)
    {
        cout << "sec: " << p.second << "dist: " << p.first << endl;
    }
    

    // vector<int> count(4,0);

    // for(int i = 0; i < id; i++)
    // {
    //     pair<int,int> curr_pos = pos[i];

    //     int x = curr_pos.first;
    //     int y = curr_pos.second;


    //     if (x < total_x/2 && y < total_y/2) count[0]++;
    //     else if (x > total_x/2 && y < total_y/2) count[1]++;
    //     else if (x < total_x/2 && y > total_y/2) count[2]++;
    //     else if (x > total_x/2 && y > total_y/2) count[3]++;
    // }
    
    // int ans = 1;
    // for(int i = 0; i < count.size(); i++)
    // {
    //     cout << "quarter: " << i+1  << " has " << count[i] << endl;
    //     ans *= count[i];
    // }

    // cout << "ans: " << ans << endl;
    





}

