#include <iostream>
#include <vector>

std::vector<int> sort_binary_array(std::vector<int> arr)
{
    int n = arr.size();
    int left = 0;
    int right = n-1;
    
    while (left <= right) {
        
        if (arr[left] == 0) {
            left++;
        } else {
            
            if (arr[right] == 1) {
                right--;
            } else {
                std::swap(arr[left], arr[right]);
                left++;
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

    auto result = sort_binary_array(arr);
    for (int i = 0; i < n; ++i)
        std::cout << result[i] << " ";
    
    return 0;
}