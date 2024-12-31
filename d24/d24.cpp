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
Part 1 Ans: 58367545758258

Notes
1. Impt thing I missed is that, one output can lead to multiple inputs 
2. Answer needs multiple bits so use long long


Notes 

*/


using namespace std;





int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    

    unordered_map<string, int> val;

    while(getline(fin,line))
    {
        if (line.empty()) break;

        istringstream iss(line);
        string s; 
        int i;

        iss >> s; s.pop_back();
        iss >> i;
        val[s] = i;
    }


    // Key: str  Value: unordered_map of {str2, pair<operand, out_str>};
    unordered_map<string, unordered_map<string,vector<pair<string,string>>>>  map;


    while(getline(fin,line))
    {
        if (line.empty()) break;

        istringstream iss(line);
        string s1,s2,operand,out; 
 

        iss >> s1; iss >> operand; iss >> s2;
        iss >> out;  iss >> out;

        cout << s1 << " " << s2 << " " << out << endl;
    
        map[s1][s2].push_back(make_pair(operand,out));
        map[s2][s1].push_back(make_pair(operand,out));
    }

    



    // for(auto pair : val)
    // {
    //     //if(pair.first[0] == 'Z')
        
    //         cout << pair.first << " :" << pair.second << endl;
        
    // }

    
    
    queue<string> q;
    //unordered_set<string> visited;
    for(auto pair : val)
    {
        q.push(pair.first);
        //visited.insert(pair.first);
    }

    while(!q.empty())
    {
        string curr = q.front(); q.pop();
        cout << "curr: " << curr << endl;

        unordered_map<string,vector<pair<string,string>>> pairs = map[curr];
   
        for(auto p : pairs)
        {
            // Its str pair already have a value
            string s = p.first;
            if (val.find(s) != val.end()) //  && visited.find(s) == visited.end())
            {
                for(int i = 0; i < p.second.size(); i++)
                {
                    
                    string operand = p.second[i].first;
                    string out_str = p.second[i].second;
                    
                    int out;
                    if (operand == "AND") out = val[curr] & val[s];
                    else if (operand == "XOR") out = val[curr] ^ val[s];
                    else if (operand == "OR") out = val[curr] | val[s];
                    else cout << "error" << endl;
                    
                    val[out_str] = out;

                    //if (out_str[0] == 'z') continue;
                    q.push(out_str); 
                }
                
    
             
            }
       
        }
     
    }
    
    long long ans = 0;
    for(auto pair : val)
    {
        if(pair.first[0] == 'z')
        {
            string s = pair.first;
            s.erase(s.begin());
            int n = stoi(s);
            long long temp = 1;
            ans += static_cast<long long>(pair.second) * (temp << n);
            //cout << pair.first << " :" << pair.second << endl;
        }
    }
    cout << "ans: " << ans << endl;
    
   

}