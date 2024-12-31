// AOC_D4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;


/*
* PART 2: Answer: 5142


There is a fact that is abused here in this solution, 
given the conditions of the situation, the number given in a line are always a connected component
or else they are unable to check
if there are two disconnected component there is ambiguous on what the middle number is which is not acceptable given the advent of code condition

*/



vector<int> get_correct_ordering(vector<int>& nums, unordered_map<int, vector<int>>& AL)
{
    
    unordered_map<int,int> in_degree;

    for(int num : nums)
    {
        
    }

}


int main()
{
    
    string line;
	
	std::ifstream fin("sample.txt");
    //std::ifstream fin("d5_in.txt");
    unordered_map<int,vector<int>> AL;
    unordered_map<int,vector<int>> m;


	while(getline(fin, line))
	{
		if(line.empty()) break;
		
        istringstream iss(line);

        int num1;
        int num2;
        char dummy;
        
        iss >> num1;
        iss >> dummy;
        iss >> num2;

        //cout << num1 << " " << num2 << endl;

        AL[num1].push_back(num2);
        m[num2].push_back(num1);
        
	}

    
    int ans = 0;

    while(getline(fin, line))
    {
        unordered_set<int> s;
        if(line.empty()) break;

        //cout << "line: " << line << endl;

        istringstream iss(line);
        int curr;
        vector<int> nums;
        bool flag = true;
        while(iss >> curr)
        { 
            //cout << "curr num: " << curr << endl;
            if(s.find(curr) != s.end()) 
            {
                flag = false;
                //break; we dun break as we want all the numbers to be stored
            }

            for(int i : m[curr])
            {
                s.insert(i);
            }
            nums.push_back(curr);

            char dummy; iss >> dummy;
        }

        if(!flag) // For part 2, we now only care if is it an incorrect ordering
        {
            vector<int> correct_ordering = get_correct_ordering(nums, AL);

            cout << "wrong line: " << line;
            cout << " correct line:";
            for(int i : correct_ordering)
            {
                cout << i << " "; 
            }
            cout << endl;

            ans += correct_ordering[correct_ordering.size()/2];
        }

    }


    cout << "ans: " << ans << endl;
    return 0;


}




// PART A BELOW

// // AOC_D5.cpp : This file contains the 'main' function. Program execution begins and ends there.
// //

// #include <iostream>
// #include <string>
// #include <vector>
// #include <sstream>
// #include <fstream>
// #include <unordered_set>
// #include <unordered_map>
// using namespace std;


// /*
// * ANS: 6051

//     Solution: Use an unordered_map to keep track of all numbers that should not be encountered 
//               For every line, we then use an unordered_set to see what numbers we should not encounter
// */

// int main()
// {
    
//     string line;
	
// 	std::ifstream fin("d5_in.txt");

//     unordered_map<int,vector<int>> m;

// 	while(getline(fin, line))
// 	{
// 		if(line.empty()) break;
		
//         istringstream iss(line);

//         int num1;
//         int num2;
//         char dummy;
        
//         iss >> num1;
//         iss >> dummy;
//         iss >> num2;

//         //cout << num1 << " " << num2 << endl;

//         if(m.find(num2) == m.end()) m[num2] = vector<int>();
//         m[num2].push_back(num1);
// 	}

    
//     int ans = 0;

//     while(getline(fin, line))
//     {
//         unordered_set<int> s;
//         if(line.empty()) break;

//         //cout << "line: " << line << endl;

//         istringstream iss(line);
//         int curr;
//         vector<int> nums;
//         bool flag = true;
//         while(iss >> curr)
//         { 
//             //cout << "curr num: " << curr << endl;
//             if(s.find(curr) != s.end()) 
//             {
//                 flag = false;
//                 break;
//             }

//             for(int i : m[curr])
//             {
//                 s.insert(i);
//             }
//             nums.push_back(curr);

//             char dummy; iss >> dummy;
//         }

//         if(flag)
//         {
//             cout << "adding " << nums[nums.size()/2] << endl;
//             ans += nums[nums.size()/2];
//         }

//     }


//     cout << "ans: " << ans << endl;
//     return 0;


// }


