#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <set>

/*
Part 2: 271631192020464

Approach: 
For every sequence, we cache the minimum length that the human has to input in order to get the robot to input AT THAT DEPTH
So our cache has two parameters 1. seq and 2. depth

If depth is 1, it is simply the summation of the len of the default arrowpad.

We first want to find out the possible combinations going from every position of the numpad to every other position, and similarly find this out for the arrow pad
Then we want to use DP in order to get our minimum length given a sequence of string 

See get_minlen function for more details

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


unordered_map<char,unordered_map<char,vector<string>>> get_map(vector<vector<char>> &pad)
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
            if (pad[start.first][start.second] == 'N' || pad[goal.first][goal.second] == 'N') continue;

            if (start == goal) 
            {
                // If start == goal, we just need to press A
                map[pad[start.first][start.second]][pad[goal.first][goal.second]].push_back("A");
                continue;
            }

            vector<pair<pair<int,int>,char>> moves = { {{-1,0},'^'}, {{1,0},'v'}, {{0,-1},'<'}, {{0,1},'>'}};

            queue<pair<pair<int,int>,string>> q;
            q.push(make_pair(start,""));
            
            int dist_to_goal = INT_MAX;
            vector<string> ways;
            while(!q.empty())
            {
               
                pair<int,int> curr_pos = q.front().first;
                string curr_s = q.front().second; q.pop();

                if((int)curr_s.size() + 1 > dist_to_goal) continue;
                

                //cout << "current pos: " << curr_pos.first << " " << curr_pos.second << " current_string: " << curr_s << endl;

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
                    if(pad[next_pos.first][next_pos.second] == 'N') continue;
                        
                    if(next_pos == goal)
                    {
                        if (curr_s.size() + 1 > dist_to_goal)
                        {
                        // if this ever happens, we are confident that there are no longer any more steps in the queue that can lead to an optimal solution
                        // this is bcs due to the nature of BFS, once an solution is discovered, it is defo the optimal solution, and the steps that lead to the optimal solution 
                        // gets queued first and processed. So if we can reach the goal with a step that is the non optimal solution, we know we have processed all steps that
                        // can potentially lead to an optimal solution.
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
    return map;
}


/*
An impt observation is that it seems like we are not trying every combination but we actually are. 
In depth 1, we can confidently take any minimum length between two pairs of chars bcs we know that this is the final depth

For depth 2 and above, we cannot simply use the arrowpad_map to find us the optimal sequence at this depth. 
So we want to try for every sequence to get from say '>' to 'A' at depth > 2 using the arrowpad_map bfs result and recurse into them so that we consider every
possible sequence at this depth by computing its minimum length using all of the results at a depth lower than it and so on 
in order to truly try every combination and find out which has the minimum length

This is a depth first search approach, where we are going all the way down to depth = 1, and caching all of the results 
So that for the next depth branch, we hope to use the cached results to speed things up
*/
long long get_minlen(string s, unordered_map<char,unordered_map<char, vector<string>>> &arrowpad_map, unordered_map<int, unordered_map<string,long long>> &cache, int depth)
{
    if(cache[depth].find(s) != cache[depth].end()) return cache[depth][s];
    /*
        For depth 1, we utilize the arrowpad, we do not need to "try every combination" bcs this is depth 1. 
        We are trying every combination in every other depth besides depth 1 bcs at depth 1, we know the best combination from the BFS search
        
        Here I am going to go with the assumption that I can just take any minimum length (hence taking the first element) and it works 
        I am unsure on how this checks every single combination like what I did in part 1
    */
    if (depth == 1)
    {
        long long len = 0;
        len = arrowpad_map['A'][s[0]][0].size();
        // get the adjacent pairs
        for(int i = 0; i < s.size() - 1; i++)
        {
            len += arrowpad_map[s[i]][s[i+1]][0].size();
        }
        cache[depth][s] = len;
    }
    else
    {
        
        
        /*
            What we are doing here is finding for every two adjacent pairs, what is the minimum length to get from one pair to another 
            We cannot simply use the arrowpad_map to do that bcs of the complexity of depth, and we cannot assume that one seq on say 
            depth 2 will give us the minimum len
            bcs lets say Seq A and B and Depth 16 has the same length but at depth 2, Seq A causes the min len at depth 2 to be longer.
        */
        string str = "";
        string temp_str;
        // From start point A to first char in seq
        long long min_len = LLONG_MAX;
        for (auto seq : arrowpad_map['A'][s[0]])
        {
            long long l = get_minlen(seq, arrowpad_map, cache, depth - 1);
            if (l < min_len) 
            {
                min_len = l;
                temp_str = seq;
            }
        }
        long long len = min_len;
        str += temp_str;

        for(int i = 0; i < s.size() - 1; i++)
        {
            vector<string> sequences = arrowpad_map[s[i]][s[i+1]];
            min_len = LLONG_MAX;
            for (auto seq : sequences)
            {
                long long l = get_minlen(seq, arrowpad_map, cache, depth - 1);
                if (l < min_len) 
                {
                    min_len = l;
                    temp_str = seq;
                }
            }
            len += min_len;
            str += temp_str;      
        }
        cache[depth][s] = len;
    }




    return cache[depth][s];

    
    

    
}

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

vector<string> get_cartesian_product(vector<vector<string>> &all_vectors)
{
    vector<string> result;
    if (all_vectors.empty()) return result;
    cartesian(all_vectors,0,"",result);
    return result;
}

// Here depth refers to the number of robots inbetween human and the robot containing the door numpad
long long solve(string code, unordered_map<char,unordered_map<char,vector<string>>> &numpad_map, unordered_map<char,unordered_map<char, vector<string>>> &arrowpad_map, int depth, unordered_map<int, unordered_map<string,long long>> &cache)
{
    vector<vector<string>> temp;
    temp.push_back(numpad_map['A'][code[0]]);
    for(int i = 0; i < code.size() - 1; i++)
    {
        temp.push_back(numpad_map[code[i]][code[i+1]]);
    }
    vector<string> strs = get_cartesian_product(temp);

    long long minlen = LLONG_MAX;
    for(string s : strs)
    {
        long long len = get_minlen(s, arrowpad_map, cache, depth);
        //cout << "s: " << s << " depth of " << depth << " minlen: " << len << endl;
        if (len < minlen) minlen = len;
    }
    return minlen;
}





int main()
{
    vector<string> codes;
    string line;

    //ifstream fin("sample.txt");
    ifstream fin("in.txt");
    
    while(getline(fin,line))
    {
        istringstream iss(line);
        string code; iss >> code;
        codes.push_back(code);
    }


    unordered_map<char,unordered_map<char,vector<string>>> numpad_map = get_map(numpad);
    unordered_map<char,unordered_map<char,vector<string>>> arrowpad_map = get_map(arrowpad);
    unordered_map<int, unordered_map<string,long long>> cache;

    long long ans = 0;
    for(string code : codes)
    {
        long long minlen = solve(code, numpad_map, arrowpad_map, 25, cache);
        cout << code << ": " <<  minlen << endl;

        ans += stoi(code.substr(0,3)) * minlen;
    }
    //long long minlen = solve(codes[0], numpad_map, arrowpad_map, 2, cache);
    cout << "ans: " << ans << endl;

    return 0;

    

    
}