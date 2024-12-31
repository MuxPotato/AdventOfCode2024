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


  


    // pair is <string neig, operand>
    unordered_map<string,vector<pair<string,string>>> AL;

    /*
        TODO:
        Problem here is that if i have same two strins that both give diff operands, later in the code, it will be added into the queue twice
    */


    while(getline(fin,line))
    {
        if (line.empty()) break;

        istringstream iss(line);
        string s1,s2,operand,out; 
 

        iss >> s1; iss >> operand; iss >> s2;
        iss >> out;  iss >> out;

        cout << s1 << " " << s2 << " " << out << endl;
    
        // map[s1][s2].push_back(make_pair(operand,out));
        // map[s2][s1].push_back(make_pair(operand,out));


        // Goal here is to create a directed tree which only goes upwards, where above is the inputs (x and y) and below are the ouputs (z)
        AL[out].push_back(make_pair(s1,operand));
        AL[out].push_back(make_pair(s2,operand));
    }

    


    // Here, z00 will look for x00 and y00
    // z01 look for x00,y00 in 2 step, x01,y01 in 1 steps

    int correct_xor = 4;
    int correct_and = 2;
    int correct_or = 0;

    for(int i = 1; i <= 44; i++)
    {
        int and_count = 0;
        int or_count = 0;
        int xor_count = 0;


        string z = "z";
        if (i < 10) z = z + "0" + to_string(i);
        else z = z + to_string(i);

        cout << "z: " << z << endl;


        // 1. curr string, 2. curr count
        queue<pair<string,int>> q;
        q.push(make_pair(z,0));

        while(!q.empty())
        {
            string curr = q.front().first;
            int count = q.front().second;
            q.pop();

            //cout << "curr: " << curr << endl;

            unordered_set<string> inserted;

            for(auto &pair : AL[curr])
            {
                string s = pair.first;
                
                //cout << "curr neighbor: " << s << endl;
                if (s[0] == 'x' || s[0] == 'y')
                {
                    // cout << "found: " << s;
                    // if (stoi(s.substr(1)) + 1 == count + 1) cout << " correct count of " << count + 1 << endl;
                    // else cout << " wrong count of " << count + 1 << " should be " << stoi(s.substr(1)) + 1 << endl; 
                    ;
                }
                else 
                {
                    if (inserted.find(s) == inserted.end())
                    {
                        q.push(make_pair(s, count+1));
                        inserted.insert(s);
                    }
                    
                }

                string operand = pair.second;
                //cout << "s: " << s << " operand: " << operand << endl;
                if (operand == "AND") and_count++;
                else if (operand == "OR") or_count++;
                else if (operand == "XOR") xor_count++;
            }
        }


        if (and_count == correct_and && or_count == correct_or && xor_count == correct_xor)
        {
            cout << "i: " << i << " is correct " << endl;
        }
        else 
        {
            cout << "i: " << i << " is incorrect " << endl;
        }
        cout << "and count: " << and_count << " correct and count: " << correct_and << endl;
        cout << "or count: " << or_count << " correct or count: " << correct_or << endl;
        cout << "xor count: " << xor_count << " correct xor count: " << correct_xor << endl;


        correct_xor += 2;
        correct_and += 4;
        correct_or += 2;
    }

   
    
    
    
   

}