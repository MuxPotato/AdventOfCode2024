#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
#include <bitset>
#include <unordered_map>
/*
    Part 1 Ans: 7,0,7,3,4,1,3,0,1
    Not much trick for part 1, just straight follow implementation

*/


using namespace std;


// bool is_found_sol(vector<int> output, vector<int> correct)
// {
//     if (output.size() != correct.size()) return false;

//     for(int i = 0; i < output.size(); i++)
//     {
//         if (output[i] != correct[i]) return false;
//     }
//     return true;
// }



int get_combo_operand(int operand, int a, int b, int c)
{
    if(operand == 4) return a;
    else if (operand == 5) return b;
    else if (operand == 6) return c;
    else return operand;
}

void adv(int &a, int b, int c, int operand)
{
    int ans = static_cast<double>(a) / pow(2,get_combo_operand(operand,a,b,c));
    a = ans;
}

void bxl(int &b, int operand)
{
    b = b^operand;
}

void bst(int a, int &b, int c, int operand)
{
    b = get_combo_operand(operand,a,b,c) % 8;
}

void bxc(int &b, int c)
{
    b = b^c;
}

void out(int a, int b, int c, int operand, vector<int> &output)
{
    output.push_back(get_combo_operand(operand,a,b,c) % 8);
}

void bdv(int a, int &b, int c, int operand)
{
    int ans = static_cast<double>(a) / pow(2,get_combo_operand(operand,a,b,c));
    b = ans;
}

void cdv(int a, int b, int &c, int operand)
{
    int ans = static_cast<double>(a) / pow(2,get_combo_operand(operand,a,b,c));
    c = ans;
}


int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    
    int a,b,c;

    getline(fin,line);
    istringstream iss1(line);
    string dummy; 
    iss1 >> dummy; 
    iss1.ignore(4);
    iss1 >> a;

    getline(fin,line);
    istringstream iss2(line);
    iss2 >> dummy; 
    iss2.ignore(4);
    iss2 >> b;

    getline(fin,line);
    istringstream iss3(line);
    iss3 >> dummy; 
    iss3.ignore(4);
    iss3 >> c;
    

    cout << a << " " << b << " " << c << endl;

    getline(fin,line); // empty line

    getline(fin,line);
    istringstream iss(line);
    iss >> dummy; iss.ignore(1);

    vector<int> cmds;
    int opcode,  operand;
    while(iss >> opcode)
    {
        char comma; iss >> comma;
        iss >> operand;
        
        cmds.push_back(opcode);
        cmds.push_back(operand);

        iss >> comma;
    }

    


    

    /*
        Goal here is to iterate thru the 8 possible combinations of the last 3 bits of a, finding out what value of a is possible to get the desired output given in cmds
    */

    unordered_set<int> possible;
    unordered_map<long long, long long> ans;

    for(int j = 0; j < cmds.size(); j++)
    {
        int t = cmds[j];
        cout << "goal: " << t << endl;
        unordered_map<long long, long long> new_ans;
        unordered_set<int> new_possible;
        for(int i = 0; i <= 7; i++)
        {
            int k = i^4; 

            int possible_a = (1 << k)*( (t^4) ^ k );
            //cout << "possible_a: " << possible_a << " bits: " << bitset<16>(possible_a) << endl;

            // in ans map, store first 13 bits of new found number 
            // key: first 13 bit of new found number, value: number so far
            
            // store the first 13 bits 
            if (j == 0) 
            {
                long long temp = possible_a & 0b1111111111111;
                new_possible.insert(temp);
                new_ans[temp] = temp;
            }
            else
            {
                // bcs of the 3 bit shifting every "turn" we need to check the last 13 bits of the new possible_a whether they belong to every first 13 bits of the previous possible_a's
                
                if (possible.find(possible_a & 0b0001111111111111) != possible.end())
                {
                    cout << "possible_a: " << possible_a << " bits: " << bitset<16>(possible_a) << endl;
                    long long temp = possible_a & 0b1111111111111;
                    new_possible.insert(temp);
                    new_ans[temp] = (possible_a << 3*j) | (ans[temp]);
                }
            }
            


        }
        possible = new_possible;
        ans = new_ans;
        cout << "possible paths: " << possible.size() << endl;
        cout << endl;
    }

    for(auto pair : ans)
    {
        cout << "ans: " << pair.second << endl;
    }
    
    

    
        



   
    

    

}