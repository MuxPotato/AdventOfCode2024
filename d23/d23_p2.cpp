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
Part 2 Ans: ans: bc,bf,do,dw,dx,ll,ol,qd,sc,ua,xc,yu,zt

This is essentially a finding the maximum clique question
We utilize Unpivoted Bron-Kerbosch Algorithm to find all the cliques and keep track of the biggest clique

*/


using namespace std;


void solve(unordered_set<string> R, unordered_set<string> P, unordered_set<string> X, unordered_set<string>&largest_clique,  unordered_map<string, unordered_set<string>> &map)
{
    if (P.empty() && X.empty())
    {
        if (R.size() > largest_clique.size()) largest_clique = R;
        return;
    }


    auto P_copy = P;

    for(auto &v : P_copy)
    {

        auto R_new = R;
        R_new.insert(v);


        unordered_set<string> P_intersect;
        for(auto &cand : P)
        {
            if(map[v].find(cand) != map[v].end())
            {
                P_intersect.insert(cand);
            }
        }


        unordered_set<string> X_intersect;
        for(auto &excl : X)
        {
            if (map[v].find(excl) != map[v].end())
            {
                X_intersect.insert(excl);
            }
        }

        solve(R_new, P_intersect, X_intersect, largest_clique, map);

        P.erase(v);
        X.insert(v);

    }

}




int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    
    unordered_map<string, unordered_set<string>> map;

    unordered_set<string> all;
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

        all.insert(s1);
        all.insert(s2);
    }
    fin.close();

    
    unordered_set<string> R, P(all), X, largest_clique;
    solve(R,P,X,largest_clique,map);

    vector<string> v;
    for(string s : largest_clique) v.push_back(s);

    sort(v.begin(), v.end());
    
    string ans = "";
    for(string s : v)
    {
        ans += s;
        ans += ",";
    }
    ans.pop_back(); // pop the last ,




    cout << "ans: " << ans << endl;

    
    
    
   

}