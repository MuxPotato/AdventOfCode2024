// AOC_D6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 2 Answer: 1748

We iterate thru every grid, putting an additional obstacle there

THen we try to make the guard leave, if after a while (count = 5000) it is unable to leave, we say that it is an infinite loop

*/


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

const int MAX_STEPS = 100000; 

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
    std::vector<int> start_pos;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            if (matrix[i][j] == '^')
            {
                matrix[i][j] = '.'; // Changing the unique starting position back to a regular position
                start_pos = { i,j };
                break;
            }
        }
    }


    std::cout << "Starting Position -> Row: " << start_pos[0] << " Col: " << start_pos[1] << std::endl;

    int ans = 0;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {

            if(i == start_pos[0] && j == start_pos[1]) continue; // THe starting point so we skip
            if(matrix[i][j] == '#') continue; // alr got obstacle there

            //cout << "obstacle at row: " << i << " col:" << j << endl; 
            matrix[i][j] = '#';

            vector<int> curr_pos = start_pos;
            current_direction = 'u';

            int count = MAX_STEPS;

            bool end_flag = false;
            while(!end_flag && count > 0)
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
                //cout << "next_pos[0]:" << next_pos[0] << " next_pos[1]: " << next_pos[1] << endl;

                // End Condition when guard leaves the patrol area
                if (next_pos[0] < 0 || next_pos[0] >= matrix.size() || next_pos[1] < 0 || next_pos[1] >= matrix[0].size())
                {
                    end_flag = true;
                

                    //cout << "next_pos[0]:" << next_pos[0] << " next_pos[1]: " << next_pos[1] << endl;
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

                


                curr_pos = next_pos;
                count--;
                
            } 
            matrix[i][j] = '.'; // removing the obstacle afterwards
            if (count == 0) ans++;
        }
    }

    std::cout << "Ans: " << ans << std::endl;



}

