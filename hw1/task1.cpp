#include <iostream>
#include <vector>

std::pair<int, int> TwoSum(std::vector<int> arr, int target) 
{
    int n = arr.size();
    int left = 0;
    int right = n-1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) {
            return {left, right};
            
        } else { 
            if (sum > target)
                right--;
            else
                left++;
        }
    }
}

int main() {
    
    int n;
    std::cin >> n;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];
        
    int target;
    std::cin >> target;
    
    auto result = TwoSum(arr, target);
    std::cout << result.first << " " << result.second << std::endl;
    
    return 0;
}