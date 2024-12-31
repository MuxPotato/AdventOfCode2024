// AOC_D6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 1 Answer: 5312

We use a simple algorithm to detect when the guy is out of the grid, and return the answer 
*/


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

int main()
{
    vector<std::string> matrix;

    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");

    if (!fin.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    
    while (std::getline(fin, line))
    {
        matrix.push_back(line);
    }

    // TODO: Insert check if needed for input;


    // directions: d, u, l, r
    char current_direction = 'u';

    // {row,col} -> guard's positions
    std::vector<int> curr_pos;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            if (matrix[i][j] == '^')
            {
                matrix[i][j] = '.'; // Changing the unique starting position back to a regular position
                curr_pos = { i,j };
                break;
            }
        }
    }

    std::cout << "Starting Position -> Row: " << curr_pos[0] << " Col: " << curr_pos[1] << std::endl;

    std::unordered_set<int> ans_set;
    ans_set.insert(curr_pos[0] * matrix[0].size() + curr_pos[1]);

    bool end_flag = false;
    
    while(!end_flag)
    {
        

        std::vector<int> next_pos;
        if (current_direction == 'u')
        {
            next_pos = { curr_pos[0] - 1 , curr_pos[1] };
        }
        else if (current_direction == 'd')
        {
            next_pos = { curr_pos[0] + 1 , curr_pos[1] };
        }
        else if (current_direction == 'l')
        {
            next_pos = { curr_pos[0], curr_pos[1] - 1 };
        }
        else if (current_direction == 'r')
        {
            next_pos = { curr_pos[0] , curr_pos[1] + 1 };
        }
        else
        {
            std::cerr << "Error in next pos calculation" << std::endl;
            return 1;
        }
        cout << "next_pos[0]:" << next_pos[0] << " next_pos[1]: " << next_pos[1] << endl;

        // End Condition when guard leaves the patrol area
        if (next_pos[0] < 0 || next_pos[0] >= matrix.size() || next_pos[1] < 0 || next_pos[1] >= matrix[0].size())
        {
            end_flag = true;
          

            cout << "next_pos[0]:" << next_pos[0] << " next_pos[1]: " << next_pos[1] << endl;
            break;
        }


        while(matrix[next_pos[0]][next_pos[1]] == '#')
        {
            // Change directions first 
            if (current_direction == 'u')
            { 
                current_direction = 'r';
            }
            else if (current_direction == 'd')
            {
                current_direction = 'l';
            }
            else if (current_direction == 'l')
            {
                current_direction = 'u';
            }
            else if (current_direction == 'r')
            {
                current_direction = 'd';
            }
            else
            {
                std::cerr << "Error in next pos calculation" << std::endl;
                return 1;
            }

           




            // Bcs u hit a wall, u cant go to the next_pos, so u recompute it
            if (current_direction == 'u')
            {
                next_pos = { curr_pos[0] - 1 , curr_pos[1] };
            }
            else if (current_direction == 'd')
            {
                next_pos = { curr_pos[0] + 1 , curr_pos[1] };
            }
            else if (current_direction == 'l')
            {
                next_pos = { curr_pos[0], curr_pos[1] - 1 };
            }
            else if (current_direction == 'r')
            {
                next_pos = { curr_pos[0] , curr_pos[1] + 1 };
            }
            else
            {
                std::cerr << "Error in next pos calculation" << std::endl;
                return 1;
            }

            // End Condition when guard leaves the patrol area
            if (next_pos[0] < 0 || next_pos[0] >= matrix.size() || next_pos[1] < 0 || next_pos[1] >= matrix[0].size())
            {
                end_flag = true;
                break;
            }
        }

        

        if (end_flag) break;

        

        
        

        // if (matrix[next_pos[0]][next_pos[1]] == '#')
        // {
        //     if (current_direction == 'u')
        //     {
        //         current_direction = 'r';
        //     }
        //     else if (current_direction == 'd')
        //     {
        //         current_direction = 'l';
        //     }
        //     else if (current_direction == 'l')
        //     {
        //         current_direction = 'u';
        //     }
        //     else if (current_direction == 'r')
        //     {
        //         current_direction = 'd';
        //     }

            
        // }
        // else
        // {
        //     ans_set.insert(next_pos[0] * matrix[0].size() + next_pos[1]);
        // }

        curr_pos = next_pos;
        ans_set.insert(curr_pos[0] * matrix[0].size() + curr_pos[1]);
    } 

    int ans = 0;
    for (auto it = ans_set.begin(); it != ans_set.end(); it++)
    {
        ans++;
    }

    std::cout << "Ans: " << ans << std::endl;



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
