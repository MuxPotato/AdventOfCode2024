// AOC_D3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
using namespace std;


// Part 1 ans: 173785482 
// Part 2 ans: 83158140
bool is_valid_num(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if (!isdigit(c)) return false;
	}
	return true;
}

int main()
{

	std::ifstream fin("d3_in.txt");

    if (!fin.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
	string input = "";	

    while(std::getline(fin, line))
    {
        if (line.empty()) break;

        input = input + line;
    }



	

	//cout << input;
	bool is_on = true;

	int ans = 0;
	for (int i = 0; i < input.size(); i++)
	{
		char c = input[i];

		

		// START OF Part 2 Additional
		if (c == 'd')
		{
			string temp = input.substr(i,4);

			if (temp == "do()") is_on = true;

			temp = input.substr(i,7);

			if (temp == "don't()") is_on = false;

		}
		// END OF Part 2 Additional


		if (c == 'm' && is_on)
		{
			string temp = input.substr(i, 4);

			cout << "temp: " << temp << endl;
			if (temp != "mul(") continue;

			cout << "reached here" << endl;

			int start_idx = i + 4;
			int comma_idx = -1;
			int closing_bracket_idx = -1;
			for (int j = start_idx; j < input.size(); j++)
			{
				if (input[j] == ',') comma_idx = j;
				if (input[j] == ')') closing_bracket_idx = j;

				if (comma_idx != -1 && closing_bracket_idx != -1) break;
			}

			if (comma_idx == -1 || closing_bracket_idx == -1) continue;

			if (comma_idx > closing_bracket_idx) continue;

			string first_num = input.substr(start_idx, comma_idx - start_idx);
			string second_num = input.substr(comma_idx + 1, closing_bracket_idx - comma_idx - 1);

			cout << "first num: " << first_num << " second num: " << second_num << std::endl;
			
			if (!is_valid_num(first_num) || !is_valid_num(second_num))
			{
				cout << "not a number" << endl;
				continue;
			}

			
			ans += stoi(first_num) * stoi(second_num);


		}
	}

	cout << "ans: " << ans << endl;

	return 0;
}


