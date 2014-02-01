// SortWordsAndNumbers.cpp : Defines the entry point for the console application.
//

// Given a string containing a combination of words and numbers, sort the string
// such that the words and numbers maintain their position in the string

// Input:  car 2 bus 1
// Output: bus 1 car 2

// Time complexity O(n)
// Space O(n)

#include "stdafx.h"
#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

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

string Join (string separator, vector<string> strings)
{
    string result;
    for(unsigned int i = 0; i < strings.size() - 1; i++)
    {
        result += strings[i] + separator;
    }

    result += strings[strings.size() - 1];

    return result;
}

string Sort(string input)
{
    istringstream stringStream(input);
    string temp;
    vector<string> list;

    while(stringStream >> temp)
    {
       list.push_back(temp);
    }

    vector<string> words;
    vector<int> numbers;

    bool* boolStringInput = new bool[list.size()]();

    for(unsigned int i = 0; i < list.size(); i++)
    {
        if (IsWord(list[i]))
        {
            words.push_back(list[i]);
            boolStringInput[i] = true;
        }
        else if (IsNumber(list[i]))
        {
            int number = 0;
            stringstream(list[i]) >> number;
            numbers.push_back(number);
        }
    }

    if (!words.empty())
    {
        sort(words.begin(), words.end());
    }

    if (!numbers.empty())
    {
        sort(numbers.begin(), numbers.end());
    }

    unsigned int wordCount = 0;
    unsigned int numberCount = 0;
    int current = 0;

    vector<string> result;

    for(unsigned int i = 0; i < list.size(); i++)
    {
        if(boolStringInput[i])
        {
            result.push_back(words[wordCount++]);
        }
        else
        {
            string s = to_string(numbers[numberCount++]);
            result.push_back(s);
        }
    }

    string output = Join(" ", result);

    delete[] boolStringInput;

    return output;
}

int _tmain(int argc, _TCHAR* argv[])
{
    string input;

    getline (std::cin,input);

    string output = Sort(input);

    cout << output << endl;

    return 0;
}

