// 2SigmaSampleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Given a string containing a combination of words and numbers, sort the string
// such that the words and numbers maintain their position in the string

// Input:  car 2 bus 1
// Output: bus 1 car 2

// Time complexity O(n * n)
// Space O(n)

bool IsWord(const string& s)
{
    string::const_iterator it = s.begin();

    while (it != s.end() && isalpha(*it))
    {
        ++it;
    }

    return !s.empty() && it == s.end();
}

bool IsNumber(const string& s)
{
    return (s.find_first_not_of("-0123456789") == string::npos);
}

int getNextWordIndex(int index, vector<string>& list)
{
    for(unsigned int i = index; i < list.size(); i++)
    {
        if (IsWord(list[i]))
        {
            return i;
        }
    }

    return -1;
}


int getNextNumberIndex(int index, vector<string>& list)
{
    string result;

    for(unsigned int i = index; i < list.size(); i++)
    {
        if (IsNumber(list[i]))
        {
            return i;
        }
    }

    return -1;
}


void customSort(vector<string>& input)
{
    for(unsigned int i = 0; i < input.size() - 1; i++)
    {
        int index = 0;

        if (IsWord(input[i]))
        {
            int next = i + 1;

            while((index = getNextWordIndex(next, input)) != -1)
            {
                if (input[index] < input[i])
                {
                    input[i].swap(input[index]);
                }

                next++;
            }
        }
        else if(IsNumber(input[i]))
        {
            int next = i + 1;
            while((index = getNextNumberIndex(next, input)) != -1)
            {
                int num1 = 0;

                stringstream(input[index]) >> num1;

                int num2 = 0;

                stringstream(input[i]) >> num2;

                if (num1 < num2)
                {
                    input[i].swap(input[index]);
                }

                next++;
            }
        }
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    string input;

    getline (std::cin,input);

    istringstream stringStream(input);
    string temp;

    vector<string> list;
    while(stringStream >> temp)
    {
       list.push_back(temp);
    }

    customSort(list);

    // Print all but last element with trailing space
    for(unsigned int i = 0; i < list.size() - 1; i++)
    {
        cout << list[i] << " ";
    }
    cout << list[list.size() - 1];

    return 0;
}

