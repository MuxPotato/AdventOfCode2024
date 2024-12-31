#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
#include <set>


/*
Part 2 Ans: 1509780

For part 2, moving left and right is relatively similar to part 1, just extra care needs to be taken as the boxes are now 2 cells wide 

Moving up and down is the difficult part

We recursively (thru a queue) find out how many boxes are attached to our robot, and see if for each of those boxes we are able to
find a free space (up or down, according to direction) for them to move.
If yes, then we deem that the move is able to be done, otherwise no

*/


using namespace std;

bool left_right_move(vector<string> &matrix, int x, int y, char move)
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


        // Found an obstacle so we move two steps
        matrix[curr_y][curr_x] = '.';
        if (move == '<')
        {
            curr_x -= 1;
        }
        else if (move == '>')
        {
            curr_x += 1;
        } 
        matrix[curr_y][curr_x] = '.';
        if (move == '<')
        {
            curr_x -= 1;
        }
        else if (move == '>')
        {
            curr_x += 1;
        } 
        count++;
    }

    // start from the last point we had an obstacle
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
    }
    
    while(count--)
    {
        if (move == '<')
        {
            matrix[curr_y][curr_x] = '[';
            matrix[curr_y][curr_x+1] = ']';
            curr_x += 2;
        }
        else if (move == '>')
        {
            matrix[curr_y][curr_x] = ']';
            matrix[curr_y][curr_x-1] = '[';
            curr_x -= 2;
        }
    }
    return found_space;
}


bool up_down_move(vector<string> &matrix, int x, int y, char move)
{
    // Store the position of every '[' we encounter in an vector<pair<int,int>> -> position is stored as (x,y) so (col, row)
    set<pair<int,int>> box_positions;
    int new_x = x;
    int new_y = y;
    char c = matrix[new_y][new_x];
    
    // We want the pos of the '[' to make things easier
    if (c == '[') box_positions.insert(make_pair(new_x,new_y));
    else if (c == ']') box_positions.insert(make_pair(new_x - 1,new_y));



    // Step 1: Find all the box positions that are connected to the robot 
    queue<pair<int,int>> q;
    for(auto &pair : box_positions) q.push(pair);
    while(!q.empty())
    {
        pair<int,int> curr = q.front(); q.pop();

        int curr_x = curr.first;
        int curr_y = curr.second;

        // a. Check above or below '[' 
        if (move == '^') 
        {
            curr_y--;
        }
        else if (move == 'v') 
        {
            curr_y++;
        }
        char a = matrix[curr_y][curr_x];
    
        // We want the pos of the '[' to make things easier
        if (a == '[') 
        {
            box_positions.insert(make_pair(curr_x,curr_y));
            q.push(make_pair(curr_x,curr_y));
        }
        else if (a == ']') 
        {
            box_positions.insert(make_pair(curr_x - 1,curr_y));
            q.push(make_pair(curr_x - 1,curr_y));
        }

        // b. check above or below ']'
        curr_x++;
        a = matrix[curr_y][curr_x];
      
        if (a == '[') 
        {
            box_positions.insert(make_pair(curr_x,curr_y));
            q.push(make_pair(curr_x,curr_y));
        }
        else if (a == ']') 
        {
            box_positions.insert(make_pair(curr_x - 1,curr_y));
            q.push(make_pair(curr_x - 1,curr_y));
        }
    }
    cout << "box's [ positions: ";
    for(auto &pair : box_positions)
    {
        cout << " x: " << pair.first << " y:" << pair.second;
    }
    cout << endl;



    // Step 2: Check for every box position whether we are able to find a '.' above or below it such that it is able to be moved;

    bool able_to_move = true;

    for(auto &curr : box_positions)
    {
        int curr_x = curr.first;
        int curr_y = curr.second;

        // a. Check above or below '[' 
        if (move == '^') 
        {
            curr_y--;
        }
        else if (move == 'v') 
        {
            curr_y++;
        }
        char a = matrix[curr_y][curr_x];

        if (a == '#') // if above or below it is a box or '.' we can move
        {
            able_to_move = false;
            break;
        }

        // b. Check above or below ']'
        a = matrix[curr_y][curr_x+1];

        if (a == '#') 
        {
            able_to_move = false;
            break;
        }
    }



    // Step 3: Move the boxes, if we are able to move

    if (able_to_move)
    {
        for(auto &curr : box_positions)
        {
            int curr_x = curr.first;
            int curr_y = curr.second;
            matrix[curr_y][curr_x] = '.';
            matrix[curr_y][curr_x+1] = '.';
        }

        for(auto &curr : box_positions)
        {
            int curr_x = curr.first;
            int curr_y = curr.second;
            

            if (move == '^') 
            {
                curr_y--;
            }
            else if (move == 'v') 
            {
                curr_y++;
            }
            matrix[curr_y][curr_x] = '[';
            matrix[curr_y][curr_x+1] = ']';
        }

    }



    return able_to_move;


}




int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample2.txt");
    //ifstream fin("large_custom.txt");
    string line;
    
    vector<string> matrix;

    while(getline(fin,line))
    {
        if (line.empty()) break;

        string curr = "";

        for(char c : line)
        {
            if(c == '#')
            {
                curr += "##";
            }
            else if (c == 'O') 
            {
                curr += "[]";
            }
            else if (c == '.')
            {
                curr += "..";
            }
            else if (c == '@')
            {
                curr += "@.";
            }
        }

        matrix.push_back(curr);
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
        if (move == '<') x += -1;
        else if (move == '>') x += 1;
        else if (move == '^') y += -1;
        else if (move == 'v') y += 1;
        
        bool able_to_move = true;
        if(matrix[y][x] == '[' || matrix[y][x] == ']') 
        {
            if (move == '^' || move == 'v') able_to_move = up_down_move(matrix,x,y, move);
            else able_to_move = left_right_move(matrix,x,y, move);
        }
        else if (matrix[y][x] == '#') able_to_move = false;
        else if (matrix[y][x] == '.') able_to_move = true;

        if(able_to_move) 
        {   
            matrix[curr_y][curr_x] = '.';
            matrix[y][x] = '@';
            curr_x = x;
            curr_y = y;
        }        


        // cout << "processed move: " << move << endl;
        // for(string s : matrix)
        // {
        //     cout << s << endl;
        // }
    }


    // cout << "final maze " << endl;
    // for(string s : matrix)
    // {
    //     cout << s << endl;
    // }


    int ans = 0;

    for(int y = 0; y < matrix.size(); y++)
    {
        for(int x = 0; x < matrix[0].size(); x++)
        {
            char c = matrix[y][x];

            if (c != '[') continue;     
            ans += 100 * y + x;
            

            
        }
    }

    cout << "ans: " << ans << endl;

}