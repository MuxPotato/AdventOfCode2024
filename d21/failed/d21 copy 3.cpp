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


vector<string> filter_strings_to_min_len(vector<string> &strs)
{
    int min_len = INT_MAX;
    for(string s : strs)
    {
        if (s.size() < min_len) min_len = s.size();
    }
    vector<string> ans;
    for(string s : strs)
    {
        if(s.size() == min_len)
        {
            ans.push_back(s);
        }
    }
    return ans;
}



vector<string> get_numpad_strings(string code, unordered_map<char,unordered_map<char,vector<string>>> &num_map)
{
    vector<string> curr = num_map['A'][code[0]];
    char prev = code[0];

    for(int i = 1; i < code.size(); i++)
    {
        vector<string> strs = num_map[prev][code[i]];

        vector<string> next;
        for(string s1 : curr)
        {
            for(string s2: strs)
            {
                next.push_back(s1 + s2);
            }
        }
        curr = next;
        prev = code[i];
    }
    return curr;
}

vector<string> get_arrowpad_strings(string code, unordered_map<char,unordered_map<char,vector<string>>> &arrow_map)
{
    vector<string> curr = arrow_map['A'][code[0]];
    char prev = code[0];

    for(int i = 1; i < code.size(); i++)
    {
        vector<string> strs = arrow_map[prev][code[i]];

        // cout << "debug" << endl;
        // cout << "prev: " << prev << " code[i]: " << code[i] << endl;
        // for(auto s : strs)
        // {
        //     cout << s << " ";
        
        // }
        // cout << endl;

        

        vector<string> next;
        for(string s1 : curr)
        {
            for(string s2: strs)
            {
                next.push_back(s1 + s2);
            }
        }
        curr = next;
        prev = code[i];
    }
    return curr;
}



int main()
{
    //ifstream fin("in.txt");
    ifstream fin("sample.txt");
    string line;
    vector<string> codes;

    while(getline(fin,line))
    {
        if (line.empty()) break;
        codes.push_back(line);
    }

    unordered_map<char,unordered_map<char,vector<string>>> num_map;

    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 3; c++)
        {
            pair<int,int> start = make_pair(r,c);

            unordered_map<char,vector<string>> possible_combinations;

            for(int g_row = 0; g_row < 4; g_row++)
            {
                for(int g_col = 0; g_col < 3; g_col++)
                {
                    pair<int,int> goal = make_pair(g_row,g_col);

                    if (start == goal) 
                    {
                        possible_combinations[ numpad[r][c] ].push_back("A");
                        continue;
                    }


                    queue<pair<pair<int,int>,string>> q;    
                    q.push(make_pair(start,""));
                    
                    vector<string> methods;
                    int dist = INT_MAX;

                    while(!q.empty())
                    {
                        pair<int,int> curr = q.front().first;
                        string s = q.front().second;

                        //cout << "curr: " << curr.first << " " << curr.second << endl;
                        q.pop();

                        int row = curr.first;
                        int col = curr.second;

                        int new_r, new_c;

                        new_r = row + 1;
                        new_c = col;

                        if (new_r >= 0 && new_r <= 3 && new_c >= 0 && new_c < 3) // && numpad[new_r][new_c] != 'N')
                        {
                            if (make_pair(new_r,new_c) == goal)
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    methods.push_back(s + "vA");
                                }
                                else if (s.size() + 1 < dist)
                                {
                                    dist = s.size() + 1;
                                    methods = vector<string>();
                                    methods.push_back(s + "vA");
                                }
                            }
                            else if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + "v");
                                q.push(next);
                            } 
                               
                        }

                        new_r = row - 1;
                        new_c = col;

                        if (new_r >= 0 && new_r <= 3 && new_c >= 0 && new_c < 3) // && numpad[new_r][new_c] != 'N')
                        {
                            if (make_pair(new_r,new_c) == goal)
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    methods.push_back(s + "^A");
                                }
                                else if (s.size() + 1 < dist)
                                {
                                    dist = s.size() + 1;
                                    methods = vector<string>();
                                    methods.push_back(s + "^A");
                                }
                            }
                            else if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + "^");
                                q.push(next);
                            }        
                        }

                        new_r = row;
                        new_c = col + 1;

                        if (new_r >= 0 && new_r <= 3 && new_c >= 0 && new_c < 3) // && numpad[new_r][new_c] != 'N')
                        {
                            if (make_pair(new_r,new_c) == goal)
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    methods.push_back(s + ">A");
                                }
                                else if (s.size() + 1 < dist)
                                {
                                    dist = s.size() + 1;
                                    methods = vector<string>();
                                    methods.push_back(s + ">A");
                                }
                            }
                            else if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + ">");
                                q.push(next);
                            }         
                        }

                        new_r = row;
                        new_c = col - 1;

                        if (new_r >= 0 && new_r <= 3 && new_c >= 0 && new_c < 3) // && numpad[new_r][new_c] != 'N')
                        {
                            if (make_pair(new_r,new_c) == goal)
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    methods.push_back(s + "<A");
                                }
                                else if (s.size() + 1 < dist)
                                {
                                    dist = s.size() + 1;
                                    methods = vector<string>();
                                    methods.push_back(s + "<A");
                                }
                            }
                            else if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + "<");
                                q.push(next);
                            }       
                        }

                    }
                    possible_combinations[numpad[g_row][g_col]] = methods;
                    
                }
                
            }
            num_map[numpad[r][c]] = possible_combinations;
        }
    }

            
            
    // for(auto i : num_map)
    // {
    //     //cout << i.first << " " << endl;
    //     for(auto j : i.second)
    //     {
    //         //cout << j.first << " " << endl;
    //         for(auto k : j.second)
    //         {
    //             //cout << k << " ";
    //         }
    //         //cout << endl;
    //     }
    // }

    

    unordered_map<char,unordered_map<char,vector<string>>> arrow_map;

    for(int r = 0; r < 2; r++)
    {
        for(int c = 0; c < 3; c++)
        {
            pair<int,int> start = make_pair(r,c);

            unordered_map<char,vector<string>> possible_combinations;

            for(int g_row = 0; g_row < 2; g_row++)
            {
                for(int g_col = 0; g_col < 3; g_col++)
                {
                    pair<int,int> goal = make_pair(g_row,g_col);

                    // impt, unlike the numpad, for arrows this can happen
                    if (start == goal)  
                    {
                        char temp = arrowpad[r][c];
                        possible_combinations[temp].push_back("A");
                        continue;
                    }

                    queue<pair<pair<int,int>,string>> q;    
                    q.push(make_pair(start,""));
                    
                    vector<string> methods;
                    int dist = INT_MAX;

                    while(!q.empty())
                    {
                        pair<int,int> curr = q.front().first;
                        string s = q.front().second;

                        //cout << "curr: " << curr.first << " " << curr.second << endl;
                        q.pop();

                        int row = curr.first;
                        int col = curr.second;

                        int new_r, new_c;

                        new_r = row + 1;
                        new_c = col;

                        if (new_r >= 0 && new_r <= 1 && new_c >= 0 && new_c < 3) // && numpad[new_r][new_c] != 'N')
                        {
                            if (make_pair(new_r,new_c) == goal)
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    methods.push_back(s + "vA");
                                }
                                else if (s.size() + 1 < dist)
                                {
                                    dist = s.size() + 1;
                                    methods = vector<string>();
                                    methods.push_back(s + "vA");
                                }
                            }
                            else if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + "v");
                                q.push(next);
                            } 
                               
                        }

                        new_r = row - 1;
                        new_c = col;

                        if (new_r >= 0 && new_r <= 1 && new_c >= 0 && new_c < 3) // && numpad[new_r][new_c] != 'N')
                        {
                            if (make_pair(new_r,new_c) == goal)
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    methods.push_back(s + "^A");
                                }
                                else if (s.size() + 1 < dist)
                                {
                                    dist = s.size() + 1;
                                    methods = vector<string>();
                                    methods.push_back(s + "^A");
                                }
                            }
                            else if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + "^");
                                q.push(next);
                            }        
                        }

                        new_r = row;
                        new_c = col + 1;

                        if (new_r >= 0 && new_r <= 1 && new_c >= 0 && new_c < 3) // && numpad[new_r][new_c] != 'N')
                        {
                            if (make_pair(new_r,new_c) == goal)
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    methods.push_back(s + ">A");
                                }
                                else if (s.size() + 1 < dist)
                                {
                                    dist = s.size() + 1;
                                    methods = vector<string>();
                                    methods.push_back(s + ">A");
                                }
                            }
                            else if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + ">");
                                q.push(next);
                            }         
                        }

                        new_r = row;
                        new_c = col - 1;

                        if (new_r >= 0 && new_r <= 1 && new_c >= 0 && new_c < 3) // && numpad[new_r][new_c] != 'N')
                        {
                            if (make_pair(new_r,new_c) == goal)
                            {
                                if (dist != INT_MAX && s.size() + 1 == dist)
                                {
                                    methods.push_back(s + "<A");
                                }
                                else if (s.size() + 1 < dist)
                                {
                                    dist = s.size() + 1;
                                    methods = vector<string>();
                                    methods.push_back(s + "<A");
                                }
                            }
                            else if (s.size() + 1 < dist)
                            {
                                pair<int,int> temp = make_pair(new_r,new_c);
                                pair<pair<int,int>,string> next = make_pair(temp, s + "<");
                                q.push(next);
                            }       
                        }

                    }
                    possible_combinations[arrowpad[g_row][g_col]] = methods;
                    
                }
                
            }
            arrow_map[arrowpad[r][c]] = possible_combinations;
        }
    }


    // for(auto i : arrow_map)
    // {
    //     ////cout << i.first << " " << endl;
    //     for(auto j : i.second)
    //     {
    //         //cout << "going from " << i.first << " --> " << j.first << endl;
    //         ////cout << j.first << " " << endl;
    //         for(auto k : j.second)
    //         {
    //             //cout << k << " ";
    //         }
    //         //cout << endl;
    //     }
    // }
    
    // return 0;
    

            

    vector<string> ans = get_numpad_strings(codes[0],num_map);
    ans = filter_strings_to_min_len(ans);
    vector<string> next;
    for(string s : ans)
    {
        vector<string> temp = get_arrowpad_strings(s,arrow_map);
        for(auto t : temp)
        {
            //cout << t << endl;
        }
        //cout << endl;
        next.insert(next.end(), temp.begin(), temp.end());
    }

    ans = next;
    ans = filter_strings_to_min_len(ans);


    next = vector<string>();
    for(string s : ans)
    {
        vector<string> temp = get_arrowpad_strings(s,arrow_map);
        for(auto t : temp)
        {
            //cout << t << endl;
        }
        //cout << endl;
        next.insert(next.end(), temp.begin(), temp.end());
    }

    ans = next;


    
    
    


    


    int shortest = INT_MAX;
    string shortest_s = "";
    for(string s : ans)
    {
        if (s.size() < shortest) 
        {
            shortest = s.size();
            shortest_s = s;
        }

    }
    cout << "ans: " << shortest << endl;
    cout << "string: " << shortest_s << endl;
    


}