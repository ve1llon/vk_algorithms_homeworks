#include <iostream>
#include <vector>

std::vector<int> merge(
                        std::vector<int> arr1,
                        std::vector<int> arr2
                      )
{
    int m = arr2.size();
    int n = arr1.size() - m;
    int i = n-1, j = m-1;
    int p = n + m - 1;
    
    while (p >= 0) {
        
        while ( (i >= 0) && (j >= 0) ) {
            if (arr1[i] >= arr2[j]) {
                arr1[p] = arr1[i];
                i--;
            } else {
                arr1[p] = arr2[j];
                j--;
            }
            p--;
        }
        
        while (i >= 0) {
            arr1[p] = arr1[i];
            i--;
            p--;
        }
        
        while (j >= 0) {
            arr1[p] = arr2[j];
            j--;
            p--;
        }
    }
    
    return arr1;
}



int main() {
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> arr1(n+m);
    for (int i = 0; i < n+m; ++i)
        std::cin >> arr1[i];
        
    std::vector<int> arr2(m);
    for (int i = 0; i < m; ++i)
        std::cin >> arr2[i];

    auto result = merge(arr1, arr2);
    for (int i = 0; i < n+m; ++i)
        std::cout << result[i] << " ";
    
    return 0;
}