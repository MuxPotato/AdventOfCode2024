// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 2 Answer: 224577979481346 

Some impt notes
1. Order of the stones does not actually matter, since each stone splits independently from other stones




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
using namespace std;





int get_digits(long n)
{
    
    int count = 0;
    while(n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}


int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    
    std::string line;    
    
    unordered_map<long,long> map;



    while (std::getline(fin, line))
    {
        if(line.empty()) break;
        istringstream iss(line);
        long num;
        while(iss >> num)
        {
            map[num]++;
        }
    }

    // cout << "input: ";
    // for(long n : nums)
    // {
    //     cout << n << " ";
    // }
    // cout << endl;


    // 1234

    int blinks = 75;
    int curr_blink = 1;
    while(curr_blink <= blinks)
    {
        unordered_map<long, long> new_map;
        for(auto &pair : map)
        {
            long curr = pair.first;
            long freq = pair.second;
            
            // Here we use += bcs they can be a case where other numbers also append to that key in the dict

            if (curr == 0) new_map[1] += freq;
            else if (get_digits(curr) % 2 == 0)
            {
                int digits = get_digits(curr);
                long n1 = curr / pow(10, digits/2);
                long n2 = curr % (long)pow(10, digits/2);

                
                new_map[n1] += freq;
                new_map[n2] += freq;

                
            }
            else
            {
                new_map[curr*2024] += freq;
            }
        }
        map = new_map;    
        curr_blink++;

        // cout << "Blink :" << curr_blink << endl;
        // for(long n : nums)
        // {
        //     cout << n << " ";
        // }
        // cout << endl;
        
    }
 

    

    long ans = 0;
    for(auto &pair : map)
    {
        ans += pair.second;
    }

    cout << "ans: " << ans << endl;
    
}

