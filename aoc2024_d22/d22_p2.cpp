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
#include <list>
/*
Part 2 Answer: 1455

Straight implmentation, where we keep an local unordered_map for each sequence and how much 
banana we can get if we sold it when we FIRST see the sequence
and we keep another global unordered_map for the overall sequence that can reap us the most bananas


Notes
1. We look at the first 2000 numbers generated excluding the initial number
2. It is impt to use a unordered_set to see if we have seen the sequence of numbers or not 
    bcs the qn states we will immediately get the number of bananas when we first see the sequence
    we cant see the seq, dun sell, then see the same seq again for a higher price and sell.
    I.e. The first time we see the sequence of number, we have to sell it at that price


*/

using namespace std;




long long solve(long long n)
{
    long long temp = ((n << 6) ^ n) % 16777216;
    long long temp2 = ((temp >> 5) ^ temp ) % 16777216;
    return ((temp2 << 11) ^ temp2) % 16777216;
}

int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    
    vector<long> nums;

    while(getline(fin, line))
    {
        if (line.empty()) break;

        istringstream iss(line);

        int n; iss >> n;
        nums.push_back(n);
    }   

    for(auto n : nums)
    {
        cout << n << endl;
    }

    
    unordered_map<string, int> global;
    int idx = 0;
    for(long long n : nums)
    {
        unordered_map<string, int> local;
        unordered_set<string> seen;
        list<int> window;
        int prev = n%10;
        for(int i = 0; i < 2000; i++)
        {
            n = solve(n);
            int d = n%10;
            int diff = d - prev; 
            if (window.size() >= 4) window.pop_front();
            window.push_back(diff);

            if (window.size() == 4)
            {
                string s = "";
                for(auto val : window)
                {
                    s += to_string(val);
                }
                if(seen.find(s) == seen.end())
                {
                    local[s] = max(local[s], d);
                    seen.insert(s);
                }
            }
            prev = d;
        }

        for(auto &pair : local)
        {
            global[pair.first] += local[pair.first]; 
        }
        idx++;
    }

    int highest = -1;
    string highest_str = "";
    for(auto &pair : global)
    {
        if (pair.second > highest) 
        {
            highest = pair.second;
            highest_str = pair.first;
        }
    }
    cout << "ans: " << highest << " str: " << highest_str << endl;
}