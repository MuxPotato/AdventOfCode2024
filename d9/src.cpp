// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 2 Answer:  

Solution: Go thru all the possible combinations, starting with the highest_idx

It is impt that we do one idx at a time. We cannot check eg. if 9 cannot move, we move 8 immediately, it actually results in an error

NOTE: My solution is hella slow and I am lazy to speed it up..


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
using namespace std;



long long solve2(vector<int> s, int highest_idx)
{
    
    unordered_map<int,vector<int>> map;
    int i = 0;
    while(i < s.size())
    {
        if (s[i] == -1) 
        {
            i++;
            continue;
        }

        int count = 0;
        int idx = i;
        while(s[idx] == s[i]) 
        {
            count++;
            idx++;
        }
        // {start_idx, count}
        vector<int> temp;
        temp = {i, count};
        map[s[i]] = temp;
        i = idx;
    }

    cout << "here1 " << endl;
    
    while(highest_idx--)
    {
        cout << "highest_idx: " << highest_idx << endl;
        vector<int> info = map[highest_idx];
        int start_idx = info[0];
        int freq = info[1];

        int i = 0; 
        int found = false;
        int space_idx = -1;
        while(i < s.size() && !found)
        {
            if (s[i] != -1) 
            {
                i++;
                continue;
            }


            // Found a free space
            space_idx = i;
            int j = i;
            int count = 0;
            while(s[j] == -1) 
            {
                count++;
                j++;
            }

            if (count >= freq && space_idx < start_idx) 
            {
                found = true;
            }

            if (!found) i++;
        }

        if(found)
        {
            int c = freq;
            int k = start_idx;
            while(c--)
            {
                s[k] = -1; 
                k++;
            }

            c = freq;
            while(c--)
            {
                s[space_idx] = highest_idx;
                space_idx++;
            }
        }
    }

    

    cout << "here1 " << endl;
    


    for(int i = 0; i < s.size(); i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;

    
    long long ans = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if (s[i] == -1) continue;
        int num = s[i];
        ans += i * num;
    }
    cout << "ans: " << ans << endl;
    return ans;


}


// Part 1 ANSWER: 6415184586041
long solve(vector<int> s)
{
    int left = 0;
    int right = s.size() - 1;

    while(s[left] != -1) left++;
    
    while(left < right)
    {
        s[left] = s[right];
        s[right] = -1;
        while(left < s.size() && s[left] != -1) left++;

        while(right >= 0 && s[right] == -1) right--;
    }

    //cout << "final str: " << s << endl;

    long ans = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if (s[i] == -1) continue;
        int num = s[i];
        ans += i * num;
    }
    cout << "ans: " << ans << endl;
    return ans;
}



int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    std::string line;    
    std::string input;
    while (std::getline(fin, line))
    {
        if(line.empty()) break;
        input += line;
    }
    

    vector<int> s;

    int id = 0;

    for(int i = 0; i < input.size(); i+=2)
    {
        int file_size = input[i] - '0';


        // For some reason the last digit does not have freespace, i have no idea why. --> input is an odd number
        int free_space = 0;
        if (i == input.size() - 1) free_space = 0;
        else free_space = input[i+1] - '0';

        //cout << "file_size: " << file_size << " free_space: " << free_space << endl;

        while(file_size--) s.push_back(id);
        while(free_space--) s.push_back(-1);
    
        id++;
    }
    



    long long ans = solve2(s,id);

    

    cout << "ans: " << ans << endl;

}

