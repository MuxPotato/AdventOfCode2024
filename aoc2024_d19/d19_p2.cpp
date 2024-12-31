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
/*
Part 2 Answer: 

We use recursive with memoization in order to check every possible combination.

We can either 
1. Check whether a towel is a prefix of the target string
2. Check whether a substr of the target string is a towel (both works)


My mistake
Instead of making one unordered_set for the towels and one unordered_map for memoization, i combined both towel and map together 
so map[towel] = 1 eg.

This created unnecessary complexity into the code and caused me to fail -> I am pretty sure you can do it but I am just not good enough

*/

using namespace std;

// long long solve(string target, unordered_map<string, long long> &map, unordered_set<string> towels, long largest_towel_size)
// {
//     if (target == "") return 1;
//     if (map.find(target) != map.end()) return map[target];

//     long long count = 0;
//     for(long len = 1; len <= target.size(); len++)
//     {
//         if (len > largest_towel_size) break;
//         string str = target.substr(0,len);
//         if(towels.find(str) != towels.end())
//         {
//             //cout << "found str: " << str << endl;
//             count += solve(target.substr(len), map, towels, largest_towel_size);
//         }
//     }

//     map[target] = count;
//     return count;
// }

bool is_prefix(string prefix, string str)
{
    return mismatch(prefix.begin(), prefix.end(), str.begin()).first == prefix.end();
}

long long solve(string target, unordered_map<string, long long> &map, unordered_set<string> towels, long largest_towel_size)
{
    if (target == "") return 1;
    if (map.find(target) != map.end()) return map[target];

    long long count = 0;
    for(auto s : towels)
    {
        if(is_prefix(s,target))
        {
            //cout << "found str: " << str << endl;
            count += solve(target.substr(s.size()), map, towels, largest_towel_size);
        }
    }

    map[target] = count;
    return count;
}



int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    //ifstream fin("t.txt");

    string line;

    unordered_set<string> towels;

    size_t largest_towel_size = 0;

    while(getline(fin, line))
    {
        if (line.empty()) break;
        istringstream iss(line);

        string curr = "";
        char c;
        while(iss >> c)
        {
            if (c == ',')
            {
                //cout << curr << endl;
                towels.insert(curr);
                if (curr.size() > largest_towel_size) largest_towel_size = curr.size();
                curr = "";
                iss.ignore(1);
            }
            else curr.push_back(c);
        }
        towels.insert(curr);
        if (curr.size() > largest_towel_size) largest_towel_size = curr.size();
        //cout << curr << endl;
    }


    vector<string> combo;
    while(getline(fin,line))
    {
        if (line.empty()) break;
        combo.push_back(line);
    }

    cout << "largest: " << largest_towel_size << endl;

    unordered_map<string, long long> map;
    long long ans = 0;
    for(string i : combo)
    {
        long long ways =  solve(i, map, towels, largest_towel_size);
        cout << i << " ways: " << ways << endl;
        ans += ways;
    }

    cout << "ans: " << ans << endl;



    
    
   

}