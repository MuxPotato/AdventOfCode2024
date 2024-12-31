// AOC_D2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


// ANS: 559

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	
	
	std::ifstream fin("d2_in.txt");

    if (!fin.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;


    vector<vector<int>> levels;
    while(std::getline(fin, line))
    {
        if (line.empty()) break;

        std::istringstream iss(line);

        vector<int> row;
        int val;
        while(iss >> val)
        {
            row.push_back(val);
        }
        levels.push_back(row);
    }
    
    
	
	

	/*
	cout << "reached here" << endl;
	cout << "num of levels " << levels.size() << endl;

	for(int i = 0; i < levels.size(); i++)
	{
		std::cout << "Level:" << i + 1 << std::endl;
		for (int num : levels[i])
		{
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}
	*/
	

	int ans = 0;
	vector<int> safe_indices;

	for (int i = 0; i < levels.size(); i++)
	{
		vector<int> curr_level = levels[i];


		bool is_increasing;
		int first = curr_level[0];
		int second = curr_level[1];
		if (first == second) continue;
		else if (first < second) is_increasing = true;
		else is_increasing = false;
		

		int prev = curr_level[0];
		int curr;
		bool flag = true;
		for (int j = 1; j < curr_level.size(); j++)
		{
			curr = curr_level[j];
			if (is_increasing)
			{
				if (curr <= prev || curr - prev > 3)
				{
					flag = false;
					break;
					
				}
			} 
			else // !is_increasing
			{
				if (curr >= prev || prev - curr > 3)
				{
					flag = false;
					break;
				}
			}
			prev = curr;
		}


		if (flag)
		{
			ans++;
			safe_indices.push_back(i);
		}
	}

	cout << "safe levels: ";
	for (int i : safe_indices)
	{
		cout << i << " ";
	}
	cout << endl;

	cout << "ans: " << ans << endl;

	return 0;
}