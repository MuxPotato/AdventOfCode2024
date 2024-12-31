// AOC_D6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;


/*
* PART 2: Answer: 5093

We utilize a topogical sort in order to get the correct order

Due to the nature of the contest, there is only one correct order hence even though topogical sort can give multiple different orders, we can 
be confident that the rules or dependencies are strong enough to always give one order everytime


Alse note if there is two rules 1 -> 2, 2 -> 3 but the line only involves 1 and 3, we can ignore both of this rules. 
-> important!!!

*/



vector<int> get_correct_ordering(vector<int>& nums, set<pair<int,int>> rules)
{
    
    unordered_map<int,int> in_degree;

    unordered_set<int> s;
    for(int num : nums)
    {
        s.insert(num);
    }

    set<pair<int,int>> relevant_rules;
    for(auto &rule : rules)
    {
        int n1 = rule.first;
        int n2 = rule.second;

        if ( !(s.find(n1) != s.end() && s.find(n2) != s.end()) ) continue;

        in_degree[n2]++;
        relevant_rules.insert(rule);    
    }

    int i = 0;
    vector<int> ans;
    unordered_set<int> added;
    while(i != nums.size())
    {
        for(int num : nums)
        {
            if (in_degree[num] > 0) continue;
            if (added.find(num) != added.end()) continue;
            
            ans.push_back(num);
            i++;
            added.insert(num);
            

            for(auto & rule : relevant_rules)
            {
                if(rule.first == num)
                {
                    in_degree[rule.second]--;
                }
            }
        }
    }

    
    return ans;



}


int main()
{
    
    string line;
	
	//std::ifstream fin("sample.txt");
    std::ifstream fin("d5_in.txt");

    set<pair<int,int>> rules;
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

        rules.insert(make_pair(num1,num2));
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
            vector<int> correct_ordering = get_correct_ordering(nums, rules);

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


