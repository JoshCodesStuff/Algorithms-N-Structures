#include <iostream>
#include <unordered_set>
using namespace std;

bool hasZeroSumSubArray(int nums[], int n)
{
    unordered_set<int> set;
    set.insert(0);
    
    int sum = 0;

    for (int i = 0;i<n;++i)
    {
        sum+=nums[i];

        if (set.find(sum) != set.end())
            return true;
        
        else set.insert(sum);
    }
    return false;
}

int main(){
    int nums[] = { 4, 2, -3, -1, 0, 4 };
    int n = sizeof(nums)/sizeof(nums[0]);
 
    hasZeroSumSubArray(nums, n) ?
            cout << "Subarray exists":
            cout << "Subarray does not exist";
 
    return 0;
}