// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 2 Answer: 92572057880885

We notice that this qn simply requires us to solve a system of linear equations 
2 linear equations with 2 variables 

aX + bY = e
cX + dY = f

We utilize Cramer's Rule, an explicit formula to solve the 2 by 2 linear system


We utilize the det of matrix [ a b ] 
                             [ c d ]
in order to detemine if there is one unique solution, no solution or infinite solutions

We know that there will always be a solution, but the solution could be a fraction number which we have to 
then conclude that it is not possible

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


long long get_det(long long a, long long b, long long c, long long d)
{
    return a*d - b*c;
}





int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    
    std::string line;    
    
    long ans = 0;
    int id = 0;
    while (std::getline(fin, line))
    {
        //cout << "on id:" << id;
        if(line.empty()) continue;

        istringstream iss(line);
        string s;
        long x;
        long y;

        iss >> s; iss.ignore(6);
        iss >> x; iss.ignore(4);
        iss >> y;

      //  cout << "x: " << x << " y: " << y << endl;
        pair<long,long> button_a = make_pair(x,y);

        getline(fin,line);

        istringstream iss2(line);

        iss2 >> s; iss2.ignore(6);
        iss2 >> x; iss2.ignore(4);
        iss2 >> y;

        pair<long,long> button_b = make_pair(x,y);


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

        cout << "A: " << button_a.first << " " << button_a.second << " ";
        cout << "B: " << button_b.first << " " << button_b.second << " ";
        cout << "P: " << p.first << " " << p.second << " ";

        cout << endl;

        
        getline(fin,line);

        

        long a = button_a.first;
        long b = button_b.first;
        long c = button_a.second;
        long d = button_b.second;
        long e = p.first;
        long f = p.second; 
        
        long long det = get_det(a,b,c,d);

        long long det1 = get_det(e,b,f,d);
        long long det2 = get_det(a,e,c,f);

        if (det1 % det != 0 || det2 % det != 0) 
        {
            cout << "no solution found" << endl;
            continue; // no solution
        }

        long long sol_a_presses = det1/det;
        long long sol_b_presses = det2/det;

        cout << "found A: " << sol_a_presses << " B: " << sol_b_presses << " " << endl;
        ans += sol_a_presses*3 + sol_b_presses;
    }
    cout << "ans: " << ans << endl;
}

