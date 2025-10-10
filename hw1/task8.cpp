#include <iostream>
#include <vector>

std::vector<int> evenFirst(std::vector<int> arr)
{
    int n = arr.size();
    int i = 0;

    for (int j = 0; j < n; ++j) {
        if (arr[j]%2 == 0) {
            std::swap(arr[j], arr[i]);
            i++;
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

    auto result = evenFirst(arr);
    for (int i = 0; i < n; ++i)
        std::cout << result[i] << " ";
    
    return 0;
}