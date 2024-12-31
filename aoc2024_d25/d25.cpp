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
Part 1 Ans: 2840

Straight implementation

*/


using namespace std;





int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    

    vector<vector<int>> keys;
    vector<vector<int>> locks;

   

    
    while(getline(fin,line))
    {
        if (line.empty()) 
        {
            break;
        }
        bool is_lock = false;
        if (line[0] == '#') is_lock = true;
        
        vector<int> curr = {0,0,0,0,0};
        for(int i = 0; i < 5; i++)
        {
            getline(fin,line);
            for(int j = 0; j < 5; j++)
            {
                if (line[j] == '#') curr[j]++;
            }
        }

        if(is_lock) locks.push_back(curr);
        else keys.push_back(curr);

        getline(fin,line); // last line that is not impt
        getline(fin,line); // blank line
        

    }






    cout << "locks" << endl;
    for(auto lock : locks)
    {
        for(int i = 0; i < 5; i++)
        {
            cout << lock[i];
        }
        cout << endl;
    }

    cout << "keys " << endl;
    for(auto key : keys)
    {
        for(int i = 0; i < 5; i++)
        {
            cout << key[i];
        }
        cout << endl;
    }


    int ans = 0;

    for(vector<int> lock : locks)
    {
        for(vector<int> key : keys)
        {
            bool is_valid = true;
            for(int i = 0; i < 5; i++)
            {

                if (lock[i] + key[i] > 5)
                {
                    is_valid = false;
                    break;
                }
            }
            if(is_valid) ans++;
        }
    }

    cout << "ans: " << ans << endl;
   
   

}