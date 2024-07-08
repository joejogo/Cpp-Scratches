/******************************************************************************
Leetcode Problem

Description:
You are given two non-empty lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum.

Examples:
1:
Input: l1 = {2,4,3}, l2 = {5,6,4}
Output: {7,0,8}
Explanation: 342 + 465 = 807.

2:
Input: l1 = {0}, l2 = {0}
Output: {0}

3:
Input: l1 = {9,9,9,9,9,9,9}, l2 = {9,9,9,9}
Output: {8,9,9,9,0,0,0,1}
*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Converts an array of numbers into a single number and reverses it
int reversedNumFromArr(vector<int> numArr)
{
    int reversedNum = 0;
    for (int i=numArr.size()-1; i>=0; i--)
    {
        reversedNum = (reversedNum * 10) + numArr[i];
    }
    return reversedNum;
}

// Converts a single number into an array of its digits
vector<int> ArrFromNum(int targetNum)
{
    vector<int> outArr = {};
    int targetNumCopy = targetNum;
    while (targetNumCopy > 0)
    {
        int rem = targetNumCopy % 10;
        outArr.insert(outArr.begin(), rem);
        targetNumCopy /= 10;
    }
    // Incase the array only has a zero in it
    if (outArr.size() == 0){
        outArr.push_back(0);
    }
    return outArr;
}

// Adds numbers as per the spec (top)
vector<int> WeirdAdd(vector<int> numsA, vector<int> numsB)
{
    int totalOg = reversedNumFromArr(numsA) + reversedNumFromArr(numsB);
    vector<int> totalAsArr = ArrFromNum(totalOg);
    std::reverse(totalAsArr.begin(), totalAsArr.end());
    return totalAsArr;
}

int main()
{
    vector<int> numListA = {9,9,9,9,9,9,9};
    vector<int> numListB = {9,9,9,9};
    
    vector<int> OutValArr = WeirdAdd(numListA, numListB);
    
    // Print the results (optional)
    for (int val : OutValArr) 
    {
        cout << val << endl;
    }

    return 0;
}