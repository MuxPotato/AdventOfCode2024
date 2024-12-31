// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 1 Answer: 55312 

Some impt notes
1. After we split, we dun process the new stone, but inserting the new stone using vector causes it to get processed so we i++


Failed Attempt at using LinkedList, still too slow

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
#include <list>
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

list<long> get_result(long n)
{
    list<long> result;

    if (n == 0) result.push_front(1);
    else if (get_digits(n) % 2 == 0)
    {
        int digits = get_digits(n);
        long n1 = n / pow(10, digits/2);
        long n2 = n % (long)pow(10, digits/2);

        result.push_back(n1);
        result.push_back(n2);
        //cout << "curr split into: " << n1 << " and " << n2 << endl;    
    }
    else result.push_back(n*2024);
    
    return result;
}

list<long> get_result_multiple_blinks(long num, int blinks)
{
    //cout << "calculating num: " << num << endl;

    list<long> result;
    result.push_back(num);
    
    while(blinks--)
    {
        //cout << "k: " << k << endl;
        list<long> temp;
        for(long n : result)
        {
            //cout << "n: " << n << endl;
            temp.splice(temp.end(), get_result(n));
        }
        result = temp;
    }

    return result;
}


/*
The map holds each result in blinks of 5
*/
list<long> solve(list<long> nums, int blinks, unordered_map<long, list<long>> &map)
{ 
    list<long> ans;
    for(long num : nums)
    {
        if (map.find(num) == map.end())
        {
            list<long> result = get_result_multiple_blinks(num, blinks);
            map[num] = result;
        }
        
        for(long val : map[num])
        {
            ans.push_back(val);
        }
    }
    return ans;
}






int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    
    std::string line;    
    list<long> nums;
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

    unordered_map<long, list<long>> map;



    
    int blinks_per_step = 25;
    int blinks = 75;   

    int curr_step = 1;
    int total_steps = blinks/blinks_per_step;
 
    while(curr_step <= total_steps)
    {
        cout << "curr_step: " << curr_step << endl;
        nums = solve(nums, blinks_per_step, map);
        curr_step++;


        // for(int i : nums)
        // {
        //     cout << i << " ";
        // }
        // cout << endl;
    }
    

    

    

    long ans = nums.size();
    

    cout << "ans: " << ans << endl;
    



    





}

