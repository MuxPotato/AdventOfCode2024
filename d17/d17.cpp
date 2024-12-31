#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
/*
    Part 1 Ans: 7,0,7,3,4,1,3,0,1
    Not much trick for part 1, just straight follow implementation

*/


using namespace std;

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
    //ifstream fin("in.txt");
    ifstream fin("sample.txt");
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

    int i = 0;
    vector<int> output;
    while(i < cmds.size())
    {
        
        opcode = cmds[i];
        operand = cmds[i+1];

        cout << "opcode: " << opcode << " operand: " << operand << endl;

        if (opcode == 0)
        {
            adv(a,b,c,operand);
        }
        else if (opcode == 1)
        {
            bxl(b,operand);
        }
        else if (opcode == 2)
        {
            bst(a,b,c,operand);
        }
        else if (opcode == 3)
        {
            if (a != 0) 
            {
                i = operand;
            }
            else i += 2;
        }
        else if (opcode == 4)
        {
            bxc(b,c);
        }
        else if (opcode == 5)
        {
            out(a,b,c,operand,output);
        }
        else if (opcode == 6)
        {
            bdv(a,b,c,operand);
        }
        else if (opcode == 7)
        {
            cdv(a,b,c,operand);
        }

        if(opcode != 3) i += 2;

        cout << "a: " << a << " b: " << b << " c: " << c << endl;
    }

    cout << "ans: " << endl;
    for(int i : output)
    {
        cout << i << ",";
    }
    

    

}