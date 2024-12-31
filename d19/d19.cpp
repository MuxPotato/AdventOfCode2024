#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
#include <algorithm>
/*
Part 1 Answer: 240

We use recursive with memoization in order to check every possible combination, with the is_prefix function

*/

using namespace std;

bool is_prefix(string prefix, string str)
{
    return mismatch(prefix.begin(), prefix.end(), str.begin()).first == prefix.end();
}

bool solve(string target, const vector<string> &towels, unordered_set<string> &set, string str_formed_so_far)
{
    if (set.find(target) != set.end()) return true;

    for(string t : towels)
    {
        if(is_prefix(t,target))
        {
            set.insert(str_formed_so_far + t);
            string next = target.substr(t.size());
            if (solve(next, towels, set, str_formed_so_far + t)) return true;
        }
    }
    return false;
}



int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    


    vector<string> towels;
    unordered_set<string> set;

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
                towels.push_back(curr);
                set.insert(curr);
                curr = "";
                iss.ignore(1);
            }
            else curr.push_back(c);
            
        }
        towels.push_back(curr);
        set.insert(curr);
    }

    vector<string> combo;
    while(getline(fin,line))
    {
        if (line.empty()) break;
        combo.push_back(line);
    }

    // for (string t : towels)
    // {
    //     cout << t << " ";
    // }
    // cout << endl;

    // for (string c : combo)
    // {
    //     cout << c << endl;
    // }

    int ans = 0;
    for(int i = 0; i < combo.size(); i++)
    {
        if(solve(combo[i], towels, set, "")) 
        {
            ans++;
            cout << combo[i] << " yes" << endl;
        }
        else cout << combo[i] << " no" << endl;

    }

    cout << "ans: " << ans << endl;
   

}