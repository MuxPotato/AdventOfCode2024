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
    Part 2 Ans: 156985331222018

    For part 2, you are required to reverse engineer the solution given your unique input

    My input was: 2,4,1,4,7,5,4,1,1,4,5,5,0,3,3,0

    We basically see that it requires this operations 
    b = a % 8;
    b = b ^ 4;
    c = a >> b;
    b = b ^ c;
    b = b ^ 4;
    out b % 8;
    a = a >> 3;
    go back to the top

    The key here is to notice that we are always outputting b and a is always divided by 2 ^ 3, which is shifting 3 bits to the right

    What we want to do it to build up the solution, notice that if we just aimmed for the last digit 0, we can iterate thru all possible combinations 
    of the last 3 bits of a to see which one gives 0 for b % 8 after all the operations.

    So starting from a = 0, for every function call, we do new_a = (a << 3) | i where i is 0 to 7 representing all the possible last 3 bits a could be.
    This is bcs we notice that b = a % 8 where only the last 3 bits of a matters.

    Then we do all the operations and see if b % 8 gives us the desired output.


    Notes 
    1. There is an edge case where a cannot be 0 given the conditions of adv in the qn where if a = 0, we do not do anything
    2. We build up from the last digit in the program rather given filter down from the first digit in the program, as this involves guessing what a is or calculating a 
       very big a value and then passing it on. I tried doing this but the bit manipulation was very confusing



*/


using namespace std;





long long solve(vector<int> program, vector<int> target, long long a, long long b, long long c)
{
    // No more commands to look for
    if (target.empty()) return a;    



    for(long long i = 0; i <= 7; i++)
    {   
        long long a1 = (a << 3) | i;
        cout << "a1: " << a1 << " ";
        
        b = a1 % 8;
        b = b ^ 4;
        c = a1 >> b;
        b = b ^ c;
        b = b ^ 4;

        cout << "b%8: " << b % 8 << " target: " << target[target.size() - 1] << "target size left: " << target.size() << endl;
        if(b % 8 == target[target.size() - 1])
        {
            cout << "entered " << endl;
            vector<int> new_target = target;
            new_target.pop_back();

            if (a1 == 0) continue;
            long long ans = solve(program, new_target, a1, b, c);
            if (ans != -1) return ans;
        } 
    }
    return -1;
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

    vector<int> program;
    int opcode,  operand;
    while(iss >> opcode)
    {
        char comma; iss >> comma;
        iss >> operand;
        
        program.push_back(opcode);
        program.push_back(operand);

        iss >> comma;
    }


   long long ans = solve(program, program, 0, b, c);

   cout << "ans: " << ans << endl;
}