#include <iostream>
#include <vector>

std::vector<int> ReverseArr(std::vector<int> arr, int left, int right) 
{
    int n = arr.size();

    while (left < right) {
        std::swap(arr[left], arr[right]);
        left++;
        right--;
    }
    
    return arr;
}

std::vector<int> ReverseSubArr(std::vector<int> arr, int k) 
{
    int n = arr.size();
    
    arr = ReverseArr(arr, 0, n-1);
    arr = ReverseArr(arr, 0, k%n - 1);
    arr = ReverseArr(arr, k%n, n-1);
    
    return arr;
}

int main() {
    
    int n;
    std::cin >> n;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];
    
    int k;
    std::cin >> k;
    
    auto result = ReverseSubArr(arr, k);
    for (int i = 0; i < n; ++i)
        std::cout << result[i] << " ";
    
    return 0;
}