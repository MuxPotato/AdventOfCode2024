#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <set>

/*
Part 1: 

*/

using namespace std;


vector<vector<char>> numpad =
{
    {'7','8','9'},
    {'4','5','6'},
    {'1','2','3'},
    {'N','0','A'},
};


vector<vector<char>> arrowpad =
{
    {'N','^','A'},
    {'<','v','>'},
};


void cartesian(const vector<vector<string>> &all_vectors, int idx, const string &current, vector<string> &result)
{
    if (idx == all_vectors.size())
    {
        result.push_back(current);
        return;
    }

    for(auto &s : all_vectors[idx])
    {
        cartesian(all_vectors, idx + 1, current + s, result);
    }
}

vector<string> get_cartesian_product(vector<vector<string>> all_vectors)
{
    vector<string> result;
    if (all_vectors.empty()) return result;
    cartesian(all_vectors,0,"",result);
    return result;
}


vector<string> solve(string s, vector<vector<char>> pad)
{
    vector<pair<int,int>> pos;
    for(int i = 0; i < pad.size(); i++)
    {
        for(int j = 0; j < pad[0].size(); j++)
        {
            pos.push_back(make_pair(i,j));
        }
    }

    unordered_map<char,unordered_map<char,vector<string>>> map;
    for(auto start : pos)
    {
        for(auto goal : pos)
        {
            if (start == goal) 
            {
                // If start == goal, we just need to press A
                map[pad[start.first][start.second]][pad[goal.first][goal.second]].push_back("A");
                continue;
            }

            vector<pair<pair<int,int>,char>> moves = { {{-1,0},'^'}, {{1,0},'v'}, {{0,-1},'<'}, {{0,1},'>'}};
            queue<pair<pair<int,int>,string>> q;
            q.push(make_pair(start,""));
            bool stop_flag = false;
            int dist_to_goal = INT_MAX;
            vector<string> ways;
            while(!q.empty())
            {
               
                pair<int,int> curr_pos = q.front().first;
                string curr_s = q.front().second; q.pop();

                if((int)curr_s.size() + 1 > dist_to_goal) continue;
                

                cout << "current pos" << curr_pos.first << " " << curr_pos.second << " current_string: " << curr_s << endl;

                bool break_out = false;
                for(auto t : moves)
                {
                    if (break_out) break;

                    pair<int,int> move = t.first;
                    char c = t.second;
                    
                    pair<int,int> next_pos = curr_pos;
                    next_pos.first += move.first; 
                    next_pos.second += move.second;

                    if(next_pos.first < 0 || next_pos.first >= pad.size() || next_pos.second < 0 || next_pos.second >= pad[0].size()) continue;             
                    //if(pad[next_pos.first][next_pos.second] == 'N') continue;
                        
                    if(next_pos == goal)
                    {
                        if (curr_s.size() + 1 > dist_to_goal)
                        {
                            break_out = true;
                            break;
                        }
                        if (curr_s.size() + 1 < dist_to_goal)
                        {
                            dist_to_goal = curr_s.size() + 1;
                            string next_s = curr_s; next_s.push_back(c); next_s.push_back('A');
                            ways.push_back(next_s);
                        }
                        else if (curr_s.size() + 1 == dist_to_goal)
                        {
                            string next_s = curr_s; next_s.push_back(c); next_s.push_back('A');
                            ways.push_back(next_s);
                        }
                        else 
                        {
                            // if this ever happens, we are confident that there are no longer any more steps in the queue that can lead to an optimal solution
                            // this is bcs due to the nature of BFS, once an solution is discovered, it is defo the optimal solution, and the steps that lead to the optimal solution 
                            // gets queued first and processed. So if we can reach the goal with a step that is the non optimal solution, we know we have processed all steps that
                            // can potentially lead to an optimal solution.
                            break_out = true;
                            break;
                        }
                    }
                    else
                    {
                        string next_s = curr_s; next_s.push_back(c);
                        q.push(make_pair(next_pos,next_s));

                        
                    }
                    
                }
                
            }
            map[pad[start.first][start.second]][pad[goal.first][goal.second]] = ways;
        }
    }

    //unordered_map<char,unordered_map<char,vector<string>>> map;

    // for(auto i : map)
    // {
    //     for(auto j : i.second)
    //     {
    //         cout << "from: " << i.first << " to " << j.first << endl;
    //         for(auto k : j.second)
    //         {
    //             cout << k << " ";
    //         }
    //         cout << endl;
    //     } 

    // }


    vector<vector<string>> all_vectors;
    all_vectors.push_back(map['A'][s[0]]); // the start to get from A to the first char
    for(int i = 0; i < s.size() - 1; i++)
    {
        all_vectors.push_back(map[s[i]][s[i+1]]);
    }

    vector<string> result = get_cartesian_product(all_vectors);

    // for(auto s : result)
    // {
    //     cout << s << endl;
    // }
    



    return result;
}

int main()
{
    vector<string> codes;
    string line;

    ifstream fin("sample.txt");
    //ifstream fin("in.txt");
    
    while(getline(fin,line))
    {
        istringstream iss(line);
        string code; iss >> code;
        codes.push_back(code);
    }

    vector<string> result = solve(codes[0], numpad);

    vector<string> next;
    int min_len = INT_MAX;
    for(int i = 0; i < result.size(); i++)
    {
        vector<string> temp = solve(result[i], arrowpad);
        if (i == 0) 
        {
            for(auto s : temp)
            {
                if(s.size() < min_len) min_len = s.size();
            }
            for(auto s : temp)
            {
                if(s.size() == min_len) next.push_back(s);
            }
            continue;
        }

        vector<string> new_next;
        for(auto s : temp)
        {
            if(s.size() < min_len) min_len = s.size();
        }

        for(auto s : temp)
        {
            if(s.size() == min_len) new_next.push_back(s);
        }
        for(auto s : next)
        {
            if(s.size() == min_len) new_next.push_back(s);
        }

        next = new_next;
    }

    result = next;



    next = vector<string>();
    min_len = INT_MAX;
    for(int i = 0; i < result.size(); i++)
    {
        vector<string> temp = solve(result[i], arrowpad);
        if (i == 0) 
        {
            for(auto s : temp)
            {
                if(s.size() < min_len) min_len = s.size();
            }
            for(auto s : temp)
            {
                if(s.size() == min_len) next.push_back(s);
            }
            continue;
        }

        vector<string> new_next;
        for(auto s : temp)
        {
            if(s.size() < min_len) min_len = s.size();
        }

        for(auto s : temp)
        {
            if(s.size() == min_len) new_next.push_back(s);
        }
        for(auto s : next)
        {
            if(s.size() == min_len) new_next.push_back(s);
        }

        next = new_next;
    }

    result = next;

    for(auto s : result)
    {
        cout << s << endl;
    }

    
}