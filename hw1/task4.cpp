#include <iostream>
#include <vector>

std::vector<int> merge_sorted_arrays(
                                        std::vector<int> arr1,
                                        std::vector<int> arr2
                                    )
{
    std::vector<int> result;
    
    int n = arr1.size(), m = arr2.size();
    int i = 0, j = 0;
    
    while ( (i < n) && (j < m) ) {
        
        if (arr1[i] <= arr2[j]) {
            result.push_back(arr1[i]);
            i++;
        } else {
            result.push_back(arr2[j]);
            j++;
        }
        
    }
    
    while (i < n) {
        result.push_back(arr1[i]);
        i++;
    }
    
    while (j < m) {
        result.push_back(arr2[j]);
        j++;
    }
    
    return result;
}



int main() {
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> arr1(n);
    for (int i = 0; i < n; ++i)
        std::cin >> arr1[i];
        
    std::vector<int> arr2(m);
    for (int i = 0; i < m; ++i)
        std::cin >> arr2[i];

    auto result = merge_sorted_arrays(arr1, arr2);
    for (int i = 0; i < n+m; ++i)
        std::cout << result[i] << " ";
    
    return 0;
}