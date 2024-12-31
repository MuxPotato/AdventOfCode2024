#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <math.h>
#include <algorithm>
/*
Part 1 Answer: 13004408787

Straight implementation, nothing fancy


*/

using namespace std;




long long solve(long long n)
{
    long long temp = ((n << 6) ^ n) % 16777216;
    long long temp2 = ((temp >> 5) ^ temp ) % 16777216;
    return ((temp2 << 11) ^ temp2) % 16777216;
}

int main()
{
    ifstream fin("in.txt");
    //ifstream fin("sample.txt");
    string line;
    
    vector<long> nums;

    while(getline(fin, line))
    {
        if (line.empty()) break;

        istringstream iss(line);

        int n; iss >> n;
        nums.push_back(n);
    }   

    for(auto n : nums)
    {
        cout << n << endl;
    }

    long long ans = 0;
    for(long long n : nums)
    {
        int count = 0;
        while(count < 2000)
        {
            n = solve(n);
            count++;
        }
        ans += n;
        cout << n << endl;
    }
    
    cout << "ans: " << ans << endl;


   

}