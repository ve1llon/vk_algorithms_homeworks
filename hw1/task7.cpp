#include <iostream>
#include <vector>

std::vector<int> sortColors(std::vector<int> arr)
{
    int n = arr.size();
    int left = 0;
    int mid = 0;
    int right = n-1;
    
    while (mid <= right) {
        if (arr[mid] == 0) {
            std::swap(arr[mid], arr[left]);
            mid++;
            left++;
        } else {
            
            if (arr[mid] == 1)
                mid++;
            else {
                std::swap(arr[mid], arr[right]);
                right--;
            }
        }
    }
    
    return arr;
}



int main() {
    
    int n;
    std::cin >> n;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];

    auto result = sortColors(arr);
    for (int i = 0; i < n; ++i)
        std::cout << result[i] << " ";
    
    return 0;
}