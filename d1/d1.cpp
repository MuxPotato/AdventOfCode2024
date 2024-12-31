// AOC_D1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// PART B

// FINAL ANSWER: 26593248

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
	vector<int> list1;
	vector<int> list2;
	
	//char dummy;
	int input;
	bool flag = true;
	
	while (cin >> input)
	{
		if (input == -1) break;

		if (flag)
		{
			list1.push_back(input);
		}
		else
		{
			list2.push_back(input);
		}
		flag = !flag;
	}

	/*for (int i : list1)
	{
		std::cout << i << std::endl;
	}
	for (int i : list1)
	{
		std::cout << i << std::endl;
	}*/
	
	unordered_map<int, int> map;
	for (int num : list2)
	{
		/*
		if (map.find(num) == map.end()) map[num] = 0;
		else map[num]++;
		*/
		map[num]++;
	}

	int ans = 0;
	for (int num : list1)
	{
		if (map.find(num) != map.end()) ans += num * map[num];
	}
	

	


	std::cout << "Final Answer: " << ans << std::endl;

	// Final Answer -> part A: 3508942

	



	return 0;
}






// PART A BELOW

// AOC_D1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	vector<int> list1;
	vector<int> list2;

	//char dummy;
	int input;
	bool flag = true;

	while (cin >> input)
	{
		if (input == -1) break;

		if (flag)
		{
			list1.push_back(input);
		}
		else
		{
			list2.push_back(input);
		}
		flag = !flag;
	}

	for (int i : list1)
	{
		std::cout << i << std::endl;
	}
	for (int i : list1)
	{
		std::cout << i << std::endl;
	}



	sort(list1.begin(), list1.end());
	sort(list2.begin(), list2.end());
	int ans = 0;

	for (int i = 0; i < list1.size(); i++)
	{
		int n1 = list1[i];
		int n2 = list2[i];
		int temp;
		if (n1 > n2) temp = n1 - n2;
		else temp = n2 - n1;

		ans += temp;
	}


	std::cout << "Final Answer: " << ans << std::endl;

	// Final Answer -> part A: 3508942





	return 0;
}

*/