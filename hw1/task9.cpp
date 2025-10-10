#include <iostream>
#include <vector>

std::vector<int> ZeroesToEnd(std::vector<int> arr)
{
    int n = arr.size();
    int i = n-1;

    for (int j = n-1; j >= 0; --j) {
        if (arr[j] == 0) {
            std::swap(arr[j], arr[i]);
            i--;
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

    // сделал без сохрания порядка чисел
    auto result = ZeroesToEnd(arr);
    for (int i = 0; i < n; ++i)
        std::cout << result[i] << " ";
    
    return 0;
}