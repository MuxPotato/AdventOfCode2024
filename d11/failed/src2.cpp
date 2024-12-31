// AOC_D7 .cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
Part 1 Answer:  Following the logic.

Some impt notes
1. After we split, we dun process the new stone, but inserting the new stone using vector causes it to get processed so we i++


This code is slow and hence in part 2 where we do 75 blinks, it does not work
Solution is to use Linked list instead

Part 2:

Solution: I changed it to use Linked List, and implemented it myself to learn

*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <math.h>
#include <utility>
#include <queue>
#include <math.h>
using namespace std;


struct Node
{
    long data;
    Node* next;
};

void ll_push_back(Node*& head, long data)
{
    Node* new_node = new Node{data, nullptr};

    // Empty Linked List
    if (head == nullptr)
    {
        head = new_node;
        return;
    }

    Node* current = head;
    while(current->next != nullptr)
    {
        current = current->next;
    }

    current->next = new_node;
}




int get_digits(long n)
{
    
    int count = 0;
    while(n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}



void join_ll(Node*&head, Node*&head2)
{   
    cout << "joining two heads" << endl;
    Node* curr = head;
    while(curr->next != nullptr)
    {
        curr = curr->next;
    }
    
    curr->next = head2;

}


Node* calculate_result(long i, int blinks, unordered_map<int,Node*> map)
{
    cout << "calculating result for: " << i << endl;

    Node* head = new Node{i, nullptr};
    
    
    // head->data = i;
    // head->next = nullptr;



    int curr_blink = 1;
    while(curr_blink <= blinks)
    {
        
        Node* curr = head;
        while(curr != nullptr)
        {
        
            long num = curr->data;

            if (map.find(num) != map.end())
            {
                Node* old_next = curr->next;

                Node* cloned_ll = clone_list(map[num]);



                // Impt bcs say 1 becomes X X X
                // We dw 1 -> X -> X -> X
                // We want X -> X -> X 
                // The first new element replaces the original element
                curr->next = cloned_ll->next;
                curr->data = cloned_ll->data;

                Node* tail = cloned_ll;
                while(tail->next != nullptr)
                {
                    tail = tail->next;
                }
                tail->next = old_next;

                curr = old_next; 
            }
            else
            {
                if (num == 0) curr->data = 1;
                else if (get_digits(num) % 2 == 0)
                {
                    // 1234
                    int digits = get_digits(num);
                    long n1 = num / pow(10, digits/2);
                    long n2 = num % (long)pow(10, digits/2);

                    // string s = to_string(num);
                    
                    // string s1 = s.substr(0, s.size()/2);
                    // string s2 = s.substr(s.size()/2);

                    // long n1 = stol(s1);
                    // long n2 = stol(s2);

                    // Inserting data into Linked List
                    curr->data = n1;
                    Node* new_node = new Node{n2, curr->next};
                    curr->next = new_node;

                    curr = curr->next; // Impt, we dun want to touch new number yet

                }
                else
                {
                    curr->data *= 2024;
                }
                curr = curr->next;
                }

            


            
        }

        //cout << "Blink :" << curr_blink << endl;
        //Node* c = head;
        // while(c != nullptr)
        // {
        //     cout << c->data << " ";
        //     c = c->next;
        // }
        // cout << endl;
        curr_blink++;
    }
    return head;
}


Node* clone_list(Node* head)
{
    Node* new_head = new Node{head->data, nullptr};
    Node* curr = new_head;
    Node* org = head->next;
    while(org != nullptr)
    {
        curr->next = new Node{org->data, nullptr};
        curr = curr->next;
        org = org->next;
    }
    return new_head;

}


int main()
{
    std::ifstream fin("in.txt");
    //std::ifstream fin("sample.txt");
    //std::ifstream fin("trial.txt");

    
    std::string line;  

    Node* head = nullptr;  
    
    while (std::getline(fin, line))
    {
        if(line.empty()) break;
        istringstream iss(line);
        long num;
        while(iss >> num)
        {
            ll_push_back(head, num);
        }
    }

    cout << "input: ";
    Node* curr = head;
    while(curr != nullptr)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;


    unordered_map<long,Node*> map;

    // 1234

    //int blinks = 75;
    int steps = 3;
    int blinks_per_step = 25;
    int curr_step = 1;
    while(curr_step <= steps)
    {
        cout << "curr step: " << curr_step << endl;
        Node* curr = head;
        
        while(curr != nullptr)
        {
            int num = curr->data;

            if (map.find(num) == map.end())
            {
                map[num] = calculate_result(num, blinks_per_step);
            }

            Node* old_next = curr->next;

            Node* cloned_ll = clone_list(map[num]);



            // Impt bcs say 1 becomes X X X
            // We dw 1 -> X -> X -> X
            // We want X -> X -> X 
            // The first new element replaces the original element
            curr->next = cloned_ll->next;
            curr->data = cloned_ll->data;

            Node* tail = cloned_ll;
            while(tail->next != nullptr)
            {
                tail = tail->next;
            }
            tail->next = old_next;

            curr = old_next;            
        }

        cout << "Step :" << curr_step << endl;
        //Node* c = head;
        // while(c != nullptr)
        // {
        //     cout << c->data << " ";
        //     c = c->next;
        // }
        // cout << endl;
        curr_step++;
    }
 

    
    int ans = 0;
    Node* c = head;
    while(c != nullptr)
    {
        ans++;
        c = c->next;
    }
    

    cout << "ans: " << ans << endl;
    


}

