#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>


/// Task1. Найти корень числа (ближайшее целое)

int binarySearchSqrt(int target) 
{
    int l = 0, r = target;
    
    while (l <= r) {
        long long mid = (l + r) / 2;
        
        if (mid*mid > target) {
            r = mid - 1;
            continue;
        }
            
        if (mid*mid < target) {
            l = mid + 1;
            continue;
        }
        
        return mid;
    }
    
    return r;
} 



/// Task2. Очень лёгкая задача (два ксерокса и N копий)

int copyTime(int n, int x, int y)
{
    int l = 0, r = (n-1) * std::max(x, y);

    while (l+1 < r) {
        int mid = (l + r) / 2;

        if ((mid/x + mid/y) < n-1) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return r + std::min(x, y);
}



/// Task3. Накормить животных

int feedAnimals(std::vector<int> animals, std::vector<int> food)
{
    if (animals.size() == 0 || food.size() == 0)
        return 0;

    std::sort(animals.begin(), animals.end());
    std::sort(food.begin(), food.end());

    int count = 0;
    for (int f : food) {
        if (f >= animals[count])
            count++;

        if (count == animals.size())
            break;
    }

    return count;
}



/// Task4. Найти разницу между двух строк.

char extraLetter(std::string a, std::string b)
{
    std::unordered_map<char, int> hashMapA;

    for (int i = 0; i < a.size(); ++i)
        hashMapA[a[i]]++;

    for (int i = 0; i < b.size(); ++i) {

            return b[i];

        hashMapA[b[i]]--;
    }

    return '\0';
}



/// Task5. Сумма двух элементов.

std::vector<int> twoSum(std::vector<int> data, int target)
{
    std::unordered_map<int, int> cache;

    for (int i = 0; i < data.size(); ++i)
        cache[data[i]] = i;

    for (int i = 0; i < data.size(); ++i) {
        int diff = target - data[i];

        if (cache.find(diff) != cache.end())
            return {i, cache[diff]};
    }

    return {};
}



/// Task6. Сортировка шелла.

std::vector<int> shell_sort(std::vector<int> arr)
{
    int n = arr.size();
    int gap = n / 2;

    while (gap > 0) {

        for (int curr_pos = gap; curr_pos < n; curr_pos++) {
            int m_gap = curr_pos;

            while (m_gap >= gap && arr[m_gap] < arr[m_gap - gap]) {
                std::swap(arr[m_gap], arr[m_gap - gap]);
                m_gap -= gap;
            }
        }

        gap /= 2;
    }

    return arr;
}



/// Task7. Массив анаграмм.

std::vector<std::vector<std::string>> Anagrams(std::vector<std::string> arr)
{
    std::unordered_map<std::string, std::vector<std::string>> anagrams_sorted;
    std::vector<std::vector<std::string>> res;

    for (int i = 0; i < arr.size(); ++i) {

        std::string curr_str = arr[i];
        std::sort(curr_str.begin(), curr_str.end());

        anagrams_sorted[curr_str].push_back(arr[i]);
    }

    for (auto [k, v] : anagrams_sorted)
        res.push_back(v);

    return res;
}

int main()
{
    std::vector<std::string> arr {"won","now","aaa","ooo","ooo"};
    std::vector<std::vector<std::string>> res = Anagrams(arr);

    for (int i = 0; i < res.size(); ++i) {
        std::cout << "[";
        for (int j = 0; j < res[i].size(); ++j) {
            for (char c : res[i][j])
                std::cout << c;
            std::cout << " ";
        }
        std::cout << "]" << std::endl;;
    }

    return 0;
}
