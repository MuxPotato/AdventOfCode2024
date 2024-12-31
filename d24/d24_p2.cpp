#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
#include <unordered_map>
#include <algorithm>
/*
Part 2 Ans: bpf,fdw,hcc,hqc,qcw,z05,z11,z35


Solution:
Credit to HyperNeutrino for this solution, or else I would have never got it. Link to Video: https://www.youtube.com/watch?v=SU6lp6wyd3I 

To understand this solution, we must first understand how additional works using gates. Refer to the pictures in this repo to better understand this solution

Notes
1. The structure of the code has the final output as the key and value being the strings and operands that is routed to that output 
2. Code follows how an binary additional should work according to gates
3. Forward declaration of functions are needed as there are cyclic dependencies

Manually retrieving the solution:
To get the correct pairing, we just keep checking from z00 upwards until we encounter an error, and we manually inspect the puzzle input and swap the 
two outputs gates to fix the error
Note u have to swap the output gates to continue, else the error carries forward to the next few z outputs
 

*/


using namespace std;
bool check_carry_bit(unordered_map<string, vector<string>> &map, string out, int num);

string get_wire(string s, int num)
{
    if (num < 10) return s += "0" + to_string(num);
    return s += to_string(num);

}

/*
Checks if this output wire, is an intermediate wire that captures the output of the two x,y inputs of a certain number 
*/
bool check_intermediate_xor(unordered_map<string, vector<string>> &map, string out, int num)
{
    cout << "checking intermediate xor, out wire: " << out << endl;

    vector<string> temp = map[out];
    string s1 = temp[0];
    string s2 = temp[1];
    string operand = temp[2];

    if (operand != "XOR") return false;

    if ( (s1 == get_wire("x", num) && s2 == get_wire("y", num)) || (s1 == get_wire("y", num) && s2 == get_wire("x", num)) ) return true;

    return false;
}

/*
Same as check_intermediate_xor function but this time, the operand has to be AND bcs it is a direct carry bit where it is the output of the AND operand between the x,y inputs
*/
bool check_direct_carry_bit(unordered_map<string, vector<string>> &map, string out, int num)
{
    cout << "checking direct carry bit, out wire: " << out << endl;
    vector<string> temp = map[out];
    string s1 = temp[0];
    string s2 = temp[1];
    string operand = temp[2];

    if (operand != "AND") return false;

    if ( (s1 == get_wire("x", num) && s2 == get_wire("y", num)) || (s1 == get_wire("y", num) && s2 == get_wire("x", num)) ) return true;

    return false;
}





bool check_z(unordered_map<string, vector<string>> &map, string out, int num)
{
    cout << "checking z, out wire: " << out << endl;
    vector<string> temp = map[out];
    string s1 = temp[0];
    string s2 = temp[1];
    string operand = temp[2];
    

    
    if (operand != "XOR") return false;
    if (num == 0)
    {
        //if (operand != "XOR") return false;
        if ( (s1 == get_wire("x", 0) && s2 == get_wire("y", 0)) || (s1 == get_wire("y", 0) && s2 == get_wire("x", 0)) ) return true;
        return false;
    }
    

    return ( check_intermediate_xor(map, s1, num) && check_carry_bit(map, s2, num) ) || ( check_intermediate_xor(map, s2, num) && check_carry_bit(map, s1, num) );
}

bool check_indirect_carry_bit(unordered_map<string, vector<string>> &map, string out, int num)
{
    cout << "checking indirect carry bit, out wire: " << out << endl;
    vector<string> temp = map[out];
    string s1 = temp[0];
    string s2 = temp[1];
    string operand = temp[2];


    if (operand != "AND") return false;

    return (check_carry_bit(map, s1, num) && check_intermediate_xor(map, s2, num)) || (check_carry_bit(map, s2, num) && check_intermediate_xor(map, s1, num));

}

bool check_carry_bit(unordered_map<string, vector<string>> &map, string out, int num)
{
    cout << "checking carry bit, out wire: " << out << endl;
    vector<string> temp = map[out];
    string s1 = temp[0];
    string s2 = temp[1];
    string operand = temp[2];

    

    // Edge case, for z01, the carry bit is just x00 and y00
    if (num == 1)
    {
        if (operand != "AND") return false;
        if ( (s1 == get_wire("x", 0) && s2 == get_wire("y", 0)) || (s1 == get_wire("y", 0) && s2 == get_wire("x", 0)) ) return true;
        return false;
    }

    if (operand != "OR") return false;

    return ( check_direct_carry_bit(map, s1, num - 1) && check_indirect_carry_bit(map, s2, num-1) ) || ( check_direct_carry_bit(map, s2, num - 1) && check_indirect_carry_bit(map, s1, num-1) );
}



int main()
{
    ifstream fin("in.txt");
    string line;
    unordered_map<string, int> val;

    while(getline(fin,line))
    {
        if (line.empty()) break;

        istringstream iss(line);
        string s; 
        int i;

        iss >> s; s.pop_back();
        iss >> i;
        val[s] = i;
    }


  
    unordered_map<string, vector<string>> map;


    while(getline(fin,line))
    {
        if (line.empty()) break;

        istringstream iss(line);
        string s1,s2,operand,out; 
 

        iss >> s1; iss >> operand; iss >> s2;
        iss >> out;  iss >> out;

        cout << s1 << " " << s2 << " " << out << endl;
    
        vector<string> temp;
        temp = {s1, s2, operand};
        map[out] = temp;
    }

    

    
    int flag = true;
    int z = 0;
    while(flag)
    {
        flag = check_z(map,get_wire("z",z),z);
        z++;

        if (z == 45) break;
    }


    
    
    vector<string> ans = {"z05", "bpf", "fdw", "z35", "qcw", "hqc", "hcc", "z11"};

    sort(ans.begin(), ans.end());
    for(string s : ans)
    {
        cout << s << ",";
    }
    
   

}