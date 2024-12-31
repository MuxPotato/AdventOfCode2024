#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
#include <unordered_map>
#include <algorithm>
/*
Part 1 Ans: 1077

This is essentially a clique problem with a size of 3 

Solution: We store the neighbors of every string in a unordered_map<string, unordered_set<string>> 
Then we check for strings that start with t, for each neighbors against every other neighbor whether those two neighbors are connected 
If yes, sort the 3 strings and concatenate them tgt and insert them into a unordered_set to prevent double checking

Notes 
    1. Edges are multiple directional
    2. Need to deal with duplicates, so need to sort the 3 strings and insert them into a set to prevent double counting

*/


using namespace std;





int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    
    unordered_map<string, unordered_set<string>> map;


    while(getline(fin,line))
    {
        if (line.empty()) break;
        istringstream iss(line);
        string s1,s2;
        char c;

        iss >> c; s1.push_back(c); 
        iss >> c; s1.push_back(c); 
        iss >> c; // dummy
        iss >> c; s2.push_back(c); 
        iss >> c; s2.push_back(c); 

        map[s1].insert(s2);
        map[s2].insert(s1);
    }

    
    unordered_set<string> ans;

    for(auto &pair : map)
    {
        string s = pair.first;
        if (s[0] != 't') continue;

        for(string i : pair.second)
        {
            for(string j : pair.second)
            {
                if (i == j) continue;
                if (map[i].find(j) == map[i].end()) continue;

                vector<string> temp = {s, i, j}; 
                sort(temp.begin(), temp.end());
                ans.insert(temp[0] + temp[1] + temp[2]);
            }
        }

    }
    int count = 0;
    for(auto i : ans)
    {
        count++;
        cout << i << endl;
    }
    cout << "ans: " << count << endl;

    
   

}