/******************************************************************************
Leetcode Problem
Link: https://leetcode.com/problems/longest-substring-without-repeating-characters

Description: Given a string s, find the length of the longest substring without repeating characters.

Examples:
Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// Gets the longest string count in a list of strings
int GetLongestStrInArr(vector<string> strArr)
{
    int longestStrLen = 0;
    for (string s : strArr)
    {
        longestStrLen = (s.size() > longestStrLen) ? s.size() : longestStrLen;
    }
    return longestStrLen;
}

int lengthOfLongestSubstring(string s) 
{
    vector<string> noRepStrArr;
    // For each char in the vector
    string currSubStr = "";
    stringstream currSubStrSs("");
    for (int i=0; i<s.size(); i++)
    {
        char thisChar = s[i];
        // if the char exists in the currSubStr, store, and clear currSubStr
        if (currSubStr.find(thisChar, 0) != string::npos)
        {
            noRepStrArr.push_back(currSubStr);
            currSubStrSs.str("");
        }
        currSubStrSs << thisChar;
        currSubStr = currSubStrSs.str();
    }
    // If we have any trailing substring at the end, store it
    if (currSubStr.size() > 0)
    {
        noRepStrArr.push_back(currSubStr);
    }
        
    // Check the length of the collected substrs to get the longest one
    return GetLongestStrInArr(noRepStrArr);
    
}

int main()
{
    cout << lengthOfLongestSubstring("pwwkew") << endl;

    return 0;
}