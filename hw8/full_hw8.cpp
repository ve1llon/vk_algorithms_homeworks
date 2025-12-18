#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// Task1. Максимальная сумма подмассива

int maxSubarraySum(std::vector<int> arr, int k) 
{
    if (arr.size() < k)
        return -1;
    
    int currSum = 0;
    for (int i=0; i < k; i++)
        currSum += arr[i];
    
    int maxSum = currSum;
    for (int i = k; i < arr.size(); i++) {
        currSum = currSum - arr[i-k] + arr[i];
        maxSum = std::max(maxSum, currSum);
    }
    
    return currSum;
}


// Task2. Subarray Sum Equals K

int subarraySum(std::vector<int> nums, int k) 
{
    int prefixSum = 0;
    std::unordered_map<int, int> prefixCount {{0, 1}};
    int count = 0;
    
    for (int num: nums) {
        prefixSum += num;
        
        if (prefixCount.find(prefixSum - k) != prefixCount.end())
            count += prefixCount[prefixSum - k];
            
        prefixCount[prefixSum]++;
    }
    
    return count;
}


// Task3. Максимальная длина подмассива с равным количеством 0 и 1

int findMaxLength(std::vector<int> nums) 
{
    int prefixSum = 0;
    int maxLen = 0;
    std::unordered_map<int, int> indexMap {{0, -1}};
    
    for (int i = 0; i < nums.size(); ++i) {
        int num = nums[i];
        prefixSum += (num == 0) ? -1 : 1;

        if (indexMap.find(prefixSum) != indexMap.end()) {
            maxLen = std::max(maxLen, i - indexMap[prefixSum]);
        } else {
            indexMap[prefixSum] = i;
        }
    }
    
    return maxLen;
}


// Task4. Индекс поворота массива

int pivotIndex(std::vector<int> nums) 
{
    int totalSum = 0;
    int leftSum = 0;
    
    for (int i = 0; i < nums.size(); ++i) 
        totalSum += nums[i];

    for (int i = 0; i < nums.size(); ++i) {
        
        if (leftSum == totalSum - leftSum - nums[i])
            return i;
            
        leftSum += nums[i];
    }
    
    return -1;
}


// Task5. Баланс скобок через префиксные суммы

bool canMakeValidWithDeletions(std::string s, int k) 
{
    int balance = 0;
    int min_deletions = 0;
    
    for (char c : s) {
        if (c == '(') {
            balance++;
        } else { 
            if (balance > 0) {
                balance--; 
            } else {
                min_deletions++; 
            }
        }
    }
    
    min_deletions += balance;
    
    return min_deletions <= k;
}


int main()
{
    std::vector<int> arr1 {3, 8, 6, 9, 9, 8, 6, 11};
    std::cout << maxSubarraySum(arr1, 4) << std::endl;
    
    std::vector<int> nums1 {3, 8, 6, 9, 2, 1, 4};
    std::cout << subarraySum(nums1, 11) << std::endl;
    
    std::vector<int> nums2 {0, 1, 0, 0, 1};
    std::cout << findMaxLength(nums2) << std::endl;
    
    std::vector<int> nums3 {9, 4, 8, 7, 1, 11, 2, 6, 1};
    std::cout << pivotIndex(nums3) << std::endl;
    
    std::cout << std::endl;
    std::cout << canMakeValidWithDeletions("()", 0) << std::endl;
    std::cout << canMakeValidWithDeletions("(()", 1) << std::endl;
    std::cout << canMakeValidWithDeletions("))()", 2) << std::endl;
    std::cout << canMakeValidWithDeletions("()((", 3) << std::endl;
    std::cout << canMakeValidWithDeletions("))()(", 3) << std::endl;
}