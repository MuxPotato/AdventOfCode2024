#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>


/*
This solution failed bcs there are sometimes multiple ways to get from one point to another, and pre determining one path leads to some inefficient 
eg. u can do >^ ir ^>, sometimes doing one is easier bcs the inputs are otw of each other. 

*/

using namespace std;



unordered_map<string,unordered_map<string,string>> map_arrows =
{
    {
        "<",
        {
            {"<", ""},
            {">", ">>"},
            {"^", ">^"},
            {"v", ">"},
            {"A", ">>^"}
        }
    },

    {
        ">",
        {
            {"<", "<<"},
            {">", ""},
            {"^", "<^"},
            {"v", "<"},
            {"A", "^"}
        }
    },

    {
        "^",
        {
            {"<", "v<"},
            {">", ">v"},
            {"^", ""},
            {"v", "v"},
            {"A", ">"}
        }
    },

    {
        "v",
        {
            {"<", "<"},
            {">", ">"},
            {"^", "^"},
            {"v", ""},
            {"A", "^>"}
        }
    },

    {
        "A",
        {
            {"<", "v<<"},
            {">", "v"},
            {"^", "<"},
            {"v", "<v"},
            {"A", ""}
        }
    },
};


unordered_map<string,unordered_map<string,string>> map_numpad =
{
    {
        "0",
        {
            {"0", ""},
            {"1", "^<"},
            {"2", "^"},
            {"3", "^>"},
            {"4", "^^<"},
            {"5", "^^"},
            {"6", "^^>"},
            {"7", "^^^<"},
            {"8", "^^^"},
            {"9", "^^^>"},
            {"A", ">"}
        }
    },

    {
        "1",
        {
            {"0", ">v"},
            {"1", ""},
            {"2", ">"},
            {"3", ">>"},
            {"4", "^"},
            {"5", "^>"},
            {"6", "^>>"},
            {"7", "^^"},
            {"8", "^^>"},
            {"9", "^^>>"},
            {"A", ">v>"}
        }
    },

    {
        "2",
        {
            {"0", "v"},
            {"1", "<"},
            {"2", ""},
            {"3", ">"},
            {"4", "<^"},
            {"5", "^"},
            {"6", "^>"},
            {"7", "<^^"},
            {"8", "^^"},
            {"9", "^^>"},
            {"A", "v>"}
        }
    },

    {
        "3",
        {
            {"0", "<v"},
            {"1", "<<"},
            {"2", "<"},
            {"3", ""},
            {"4", "<<^"},
            {"5", "<^"},
            {"6", "^"},
            {"7", "<<^^"},
            {"8", "<^^"},
            {"9", "^^"},
            {"A", "v"}
        }
    },

    {
        "4",
        {
            {"0", "v>v"},
            {"1", "v"},
            {"2", "v>"},
            {"3", "v>>"},
            {"4", ""},
            {"5", ">"},
            {"6", ">>"},
            {"7", "^"},
            {"8", "^>"},
            {"9", "^>>"},
            {"A", "v>>v"}
        }
    },

    {
        "5",
        {
            {"0", "vv"},
            {"1", "v<"},
            {"2", "v"},
            {"3", "v>"},
            {"4", "<"},
            {"5", ""},
            {"6", ">"},
            {"7", "<^"},
            {"8", "^"},
            {"9", "^>"},
            {"A", "vv>"}
        }
    },

    {
        "6",
        {
            {"0", "<vv"},
            {"1", "v<<"},
            {"2", "v<"},
            {"3", "v"},
            {"4", "<<"},
            {"5", "<"},
            {"6", ""},
            {"7", "^<<"},
            {"8", "^<"},
            {"9", "^"},
            {"A", "vv"}
        }
    },

    {
        "7",
        {
            {"0", ">vvv"},
            {"1", "vv"},
            {"2", "vv>"},
            {"3", ">>vv"},
            {"4", "v"},
            {"5", "v>"},
            {"6", "v>>"},
            {"7", ""},
            {"8", ">"},
            {"9", ">>"},
            {"A", ">>vvv"}
        }
    },

    {
        "8",
        {
            {"0", "vvv"},
            {"1", "vv<"},
            {"2", "vv"},
            {"3", "vv>"},
            {"4", "v<"},
            {"5", "v"},
            {"6", "v>"},
            {"7", "<"},
            {"8", ""},
            {"9", ">"},
            {"A", ">vvv"}
        }
    },

    {
        "9",
        {
            {"0", "vvv<"},
            {"1", "vv<<"},
            {"2", "vv<"},
            {"3", "vv"},
            {"4", "v<<"},
            {"5", "v<"},
            {"6", "v"},
            {"7", "<<"},
            {"8", "<"},
            {"9", ""},
            {"A", "vvv"}
        }
    },

    {
        "A",
        {
            {"0", "<"},
            {"1", "^<<"},
            {"2", "^<"},
            {"3", "^"},
            {"4", "^^<<"},
            {"5", "^^<"},
            {"6", "^^"},
            {"7", "^^^<<"},
            {"8", "^^^<"},
            {"9", "^^^"},
            {"A", ""}
        }
    }
};

string get_directions_input(string s)
{
    string ans = "";
    string curr = "A";
    for(char c : s)
    {
        string c_string = ""; c_string.push_back(c);
        ans += map_arrows[curr][c_string] + "A";
        curr = c_string;
    }
    return ans;
}

string get_directions_numpad(string s)
{
    string ans = "";
    string curr = "A";
    for(char c : s)
    {
        string c_string = ""; c_string.push_back(c);
        ans += map_numpad[curr][c_string] + "A";
        curr = c_string;
    }
    return ans;
}




int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    vector<string> codes;

    while(getline(fin,line))
    {
        if (line.empty()) break;
        codes.push_back(line);
    }


    int ans = 0;
    for(string code : codes)
    {
        int num = stoi(code.substr(0,3));

        string s = get_directions_numpad(code);
        // for(int i = 0; i < 2; i++)
        // {
        //     s = get_directions_input(s);
        // }
        // //cout << "code: " << code << " ans: " << s << endl;
        cout << code << ": " << s << endl;

        ans += num*s.size();
    }

    cout << "ans: " << ans << endl;


}