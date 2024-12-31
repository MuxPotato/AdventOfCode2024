// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 1 Answer: 33481

For part 1, we know that the limit is 100, so we can simply iterate from 0 to 100 for button A and find the corresponding button B

Notes:
    1. Maximum number of times is guaranteed to be <= 100 for each button
    2. Take extra consideration when dealing with integer division


Part 2 Answer: 

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







int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    
    std::string line;    
    
    long ans = 0;
    int id = 0;
    while (std::getline(fin, line))
    {
        cout << "on id:" << id;
        if(line.empty()) continue;

        istringstream iss(line);
        string s;
        long x;
        long y;

        iss >> s; iss.ignore(6);
        iss >> x; iss.ignore(4);
        iss >> y;

      //  cout << "x: " << x << " y: " << y << endl;
        pair<long,long> a = make_pair(x,y);

        getline(fin,line);

        istringstream iss2(line);

        iss2 >> s; iss2.ignore(6);
        iss2 >> x; iss2.ignore(4);
        iss2 >> y;

        pair<long,long> b = make_pair(x,y);


        getline(fin,line);
        //cout << "c line: " << line << endl;
        

        istringstream iss3(line);

        iss3 >> s; iss3.ignore(3);
        iss3 >> x; iss3.ignore(4);
        iss3 >> y; 

        // For Part 2
        x += 10000000000000;
        y += 10000000000000;
        
        pair<long,long> p = make_pair(x,y);

        cout << "A: " << a.first << " " << a.second << " ";
        cout << "B: " << b.first << " " << b.second << " ";
        cout << "P: " << p.first << " " << p.second << " ";

        // cout << endl;

        
        getline(fin,line);

        long A_max_presses = ceil(static_cast<double>(p.first) / a.first);

        cout << " A_max_presses: " << A_max_presses << endl;

        vector<long> tokens;
        for(int i = 0; i <= A_max_presses; i++)
        {
            long px = p.first;
            long py = p.second;

            px -= i*a.first;
            py -= i*a.second;

            // Deal with the cases where there are integer division, they are invalid cases
            if (px % b.first != 0 || py % b.second != 0) continue;

            if (px / b.first == py / b.second) 
            {
                cout << "found A:" << i << " B: " << px / b.first << " ";
                tokens.push_back(3*i + px / b.first);
            }

            
            

            
        }

        if (tokens.empty()) 
        {
            cout << "no combinations found" << endl; 
            
        }
        else
        {
            sort(tokens.begin(),tokens.end());

            cout << "adding tokens: " << tokens[0] << endl;

            ans += tokens[0];
        }

        
        
        id++;
    }

    
   
    
    
  	

    cout << "ans: " << ans << endl;



}

