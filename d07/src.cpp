// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 1: Answer: 3119088655389
Part 2 Answer: 264184041398847

We iterate thru all values, adding it to a vector of curr_values that consists of all possible values until that point.
Note we need to use long as the numbers gets really big


*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <math.h>
using namespace std;

long concat(long a, long b)
{
    int digits = 0;
    int b_temp = b;
    while(b_temp > 0)
    {
        digits++;
        b_temp /= 10;
    }

    return pow(10, digits) * a + b;
}

void solve(long &target, vector<long> &nums, int next_idx, vector<long> &curr_values)
{

    vector<long> new_values;
    //cout << "next idx: " << next_idx << endl;
    
    if(next_idx >= nums.size()) return;

    long next_num = nums[next_idx];

    for(long v : curr_values)
    {
        new_values.push_back(v + next_num);
        new_values.push_back(v * next_num);

        // Part 2 additional
        //new_values.push_back(concat(v, next_num));
    }
    curr_values = new_values;
    solve(target, nums, next_idx + 1, curr_values);
}

int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    if (!fin.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    long ans = 0;
    
    while (std::getline(fin, line))
    {
        istringstream iss(line);
        //cout << "line: " << line << endl;
        if(line.empty()) break;

        long target;
        char dummy;
        vector<long> nums;
        long num;

        iss >> target; iss >> dummy;
        while(iss >> num)
        {
            nums.push_back(num);
        }


        vector<long> possible_values;
        possible_values.push_back(nums[0]);

        solve(target, nums, 1, possible_values);
        


        for (long value : possible_values)
        {
            if (value == target)
            {
                ans += target;
                break;
            }
        }
    }

    cout << "ans: " << ans << endl;

}

