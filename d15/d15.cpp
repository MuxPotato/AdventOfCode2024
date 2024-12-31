#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
/*
Part 1 Ans: 1479679

Notes 
    1. Due to the coordinate system (x,y) rmb that when changing matrix we do matrix[y][x] not matrix[x][y]
    2. Multiple edges cases where we found space to push box or not

*/


using namespace std;

bool get_robot_move(vector<string> &matrix, int x, int y, char move)
{
    int count = 0;
    int found_space = false;

    int curr_x = x;
    int curr_y = y;



    while(1)
    {
        if(matrix[curr_y][curr_x] == '#') // unable to find space i.e. unable to move boulders
        {
            break;
        }
        if (matrix[curr_y][curr_x] == '.')
        {
            found_space = true;
            break;
        }

        matrix[curr_y][curr_x] = '.';
        count++;

        if (move == '<')
        {
            curr_x -= 1;
        }
        else if (move == '>')
        {
            curr_x += 1;
        }
        else if (move == '^')
        {
            curr_y -= 1;
        }
        else if (move == 'v')
        {
            curr_y += 1;
        }
        
    }

    // We start one off 
    if (!found_space) 
    {
        if (move == '<')
        {
            curr_x += 1;
        }
        else if (move == '>')
        {
            curr_x -= 1;
        }
        else if (move == '^')
        {
            curr_y += 1;
        }
        else if (move == 'v')
        {
            curr_y -= 1;
        }
    }
    
    while(count--)
    {
        matrix[curr_y][curr_x] = 'O';
        if (move == '<')
        {
            curr_x += 1;
        }
        else if (move == '>')
        {
            curr_x -= 1;
        }
        else if (move == '^')
        {
            curr_y += 1;
        }
        else if (move == 'v')
        {
            curr_y -= 1;
        }
    }
    

    return found_space;
}



int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    
    vector<string> matrix;

    while(getline(fin,line))
    {
        if (line.empty()) break;
        matrix.push_back(line);
    }

    string moves = "";
    while(getline(fin,line))
    {
        if (line.empty()) break;
        moves = moves + line;
    }

    
    for(string s : matrix)
    {
        cout << s << endl;
    }

    cout << endl;
    
    cout << moves << endl;

    pair<int,int> start;
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[0].size(); j++)
        {
            if (matrix[i][j] == '@') 
            {
                start = make_pair(j,i); // (x,y)
                break;
            }
        }
    }

    int curr_x = start.first;
    int curr_y = start.second;
    for(char move : moves)
    {
        int x = curr_x;
        int y = curr_y;


        // Here we use (x,y) so (col,rol)
        if (move == '<')
        {
            x += -1;
        }
        else if (move == '>')
        {
            x += 1;
        }
        else if (move == '^')
        {
            y += -1;
        }
        else if (move == 'v')
        {
            y += 1;
        }

        bool able_to_move = true;
        if(matrix[y][x] == 'O') able_to_move = get_robot_move(matrix,x,y, move);
        else if (matrix[y][x] == '#') able_to_move = false;
        else if (matrix[y][x] == '.') able_to_move = true;

        if(able_to_move) 
        {   
            matrix[curr_y][curr_x] = '.';
            matrix[y][x] = '@';
            curr_x = x;
            curr_y = y;
        }

        
    }


    cout << "final maze " << endl;
    for(string s : matrix)
    {
        cout << s << endl;
    }


    int ans = 0;

    for(int y = 0; y < matrix.size(); y++)
    {
        for(int x = 0; x < matrix[0].size(); x++)
        {
            if(matrix[y][x] == 'O') ans += y*100 + x;
        }
    }

    cout << "ans: " << ans << endl;

}