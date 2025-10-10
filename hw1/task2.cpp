#include <iostream>
#include <vector>

std::vector<int> ReverseArr(std::vector<int> arr) 
{
    int n = arr.size();
    int left = 0;
    int right = n-1;
    
    while (left < right) {
        std::swap(arr[left], arr[right]);
        left++;
        right--;
    }
    
    return arr;
}

int main() {
    
    int n;
    std::cin >> n;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];
    
    auto result = ReverseArr(arr);
    for (int i = 0; i < n; ++i)
        std::cout << result[i] << " ";
    
    return 0;
}