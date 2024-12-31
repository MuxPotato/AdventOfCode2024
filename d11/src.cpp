// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 1 Answer: 55312 

Some impt notes
1. After we split, we dun process the new stone, but inserting the new stone using vector causes it to get processed so we i++


This code is slow and hence in part 2 where we do 75 blinks, it does not work
Solution is to use Linked link instead

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
    vector<long> nums;
    while (std::getline(fin, line))
    {
        if(line.empty()) break;
        istringstream iss(line);
        long num;
        while(iss >> num)
        {
            nums.push_back(num);
        }
    }

    cout << "input: ";
    for(long n : nums)
    {
        cout << n << " ";
    }
    cout << endl;


    // 1234

    int blinks = 75;
    int curr_blink = 1;
    while(curr_blink <= blinks)
    {
        

        for(int i = 0; i < nums.size(); i++)
        {
            long curr = nums[i];
            if (curr == 0) nums[i] = 1;
            else if (get_digits(curr) % 2 == 0)
            {
                string s = to_string(curr);
                
                string s1 = s.substr(0, s.size()/2);
                string s2 = s.substr(s.size()/2);

                long n1 = stol(s1);
                long n2 = stol(s2);

                //cout << "curr split into: " << n1 << " and " << n2 << endl;

                nums[i] = n2;
                nums.insert(nums.begin() + i, n1);
                i++; // impt, cause we dw to consider this new stone on this turn
            }
            else
            {
                nums[i] *= 2024;
            }
        }

        // cout << "Blink :" << curr_blink << endl;
        // for(long n : nums)
        // {
        //     cout << n << " ";
        // }
        // cout << endl;
        curr_blink++;
    }
 

    

    long ans = nums.size();
    

    cout << "ans: " << ans << endl;
    



    





}

