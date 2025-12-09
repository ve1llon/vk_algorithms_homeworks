#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <climits>

// Task1. Последовательность из 0 и 1.

int b_sequences_recursion(int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return 2;
    if (n == 2)
        return 3;
    
    return b_sequences_recursion(n - 1) + b_sequences_recursion(n - 2);
}

int b_sequences(int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return 2;

    std::vector<int> dp {1, 2};
    
    for (int i = 2; i <= n; i++)
        dp.push_back(dp[i-1] + dp[i-2]);
    
    return dp[n];
}


// Task2. Последовательность без трех единиц подряд.

int count_sequences(int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return 2;
    if (n == 2)
        return 4;

    std::vector<int> dp {1, 2, 4};
    
    for (int i = 3; i <= n; i++)
        dp.push_back(dp[i-1] + dp[i-2] + dp[i-3]);
    
    return dp[n];
}


// Task3. Наибольшая непрерывная возрастающая последовательность.

int findLIS(std::vector<int> nums)
{
    if (nums.size() == 0)
        return 0;
    if (nums.size() == 1)
        return 1;
        
    std::vector<int> dp (nums.size(), 1);
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i - 1] < nums[i])
            dp[i] = dp[i - 1] + 1;
    }
    
    return *std::max_element(dp.begin(), dp.end());
}


// Task4. Треугольник Паскаля.

int pascal_triangle(int row, int col) 
{
    if (col == 0 or row == col)
        return 1;
    
    return pascal_triangle(row - 1, col - 1) + pascal_triangle(row - 1, col);
}

std::vector<std::vector<int>> print_pascal_triangle(int n)
{
    std::vector<std::vector<int>> dp;
    for (int row = 0; row < n; ++row) {
        std::vector<int> currentRow;
        for (int col = 0; col < row + 1; ++col)
            currentRow.push_back(pascal_triangle(row, col));
        dp.push_back(currentRow);
    }
    
    return dp;
}

std::vector<std::vector<int>> print_pascal_triangle_iter(int n)
{
    std::vector<std::vector<int>> dp;
    for (int i = 1; i <= n; ++i) {
        std::vector<int> tmp;
        for (int j = 1; j <= i; ++j)
            tmp.push_back(1);
        dp.push_back(tmp);
    }
    
    for (int row = 1; row < n; ++row) {
        for (int col = 1; col < row + 1; ++col)
            dp[row][col] = dp[row-1][col-1] + dp[row-1][col];
    }
    
    return dp;
}


// Task5. Максимальная выгода.

int maxProfit(std::vector<int> prices)
{
    int profit = 0;
    int min_price = prices[0];
    
    for (int i = 1; i < prices.size(); ++i) {
        profit = std::max(profit, prices[i] - min_price);
        min_price = std::min(prices[i], min_price);
    }
    
    return profit;
}


// Task6. Размен монет.

int coinChange_recursion(std::vector<int> coins, 
               int amount, 
               std::unordered_map<int, int> cache) 
{
    if (amount == 0) 
        return 0;
    if (amount < 0) 
        return -1;
    
    if (cache.find(amount) != cache.end())
        return cache[amount];
    
    int minCoins = INT_MAX;
    
    for (int coin : coins) {
        int res = coinChange_recursion(coins, amount - coin, cache);
        if (res >= 0 && res < minCoins)
            minCoins = res + 1;
    }
    
    if (minCoins == INT_MAX) {
        cache[amount] = -1;
    } else {
        cache[amount] = minCoins;
    }
    
    return cache[amount];
}

int coinChange_recursion(std::vector<int> coins, int amount) 
{
    std::unordered_map<int, int> cache;
    return coinChange_recursion(coins, amount, cache);
}

int coinChange(std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}


// Task7. Максимальный палиндром в строке.

std::string longestPalindrome_recursion(std::string s)
{
    if (s.empty()) 
        return "";
    
    int currentMaxLeft = 0;
    int currentMaxRight = 0;
    
    auto expandAroundCenter = [&](int l, int r) 
    {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            if ((r - l) > (currentMaxRight - currentMaxLeft)) {
                currentMaxLeft = l;
                currentMaxRight = r;
            }
            l--;
            r++;
        }
    };
    
    for (int i = 0; i < s.size(); i++) {
        expandAroundCenter(i, i); 
        expandAroundCenter(i, i + 1);
    }
    
    return s.substr(currentMaxLeft, currentMaxRight - currentMaxLeft + 1);
}


std::string longestPalindrome(std::string s) 
{
    int n = s.size();
    if (n == 0) 
        return "";
    
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
    
    int start = 0;
    int maxLength = 1;
    
    for (int i = 0; i < n; i++)
        dp[i][i] = true;
    
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }
    
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                
                if (len > maxLength) {
                    start = i;
                    maxLength = len;
                }
            }
        }
    }
    
    return s.substr(start, maxLength);
}


int main() {
    
    std::cout << b_sequences_recursion(3) << std::endl;
    std::cout << b_sequences(3) << std::endl;
    std::cout << count_sequences(4) << std::endl;
    
    std::vector<int> nums {3, 1, 4, 7, 2, 11, 9};
    std::cout << findLIS(nums) << std::endl;
    
    int n = 6;
    std::vector<std::vector<int>> dp_res = print_pascal_triangle(n);
    for (int row = 0; row < n; ++row) {
        std::cout << " " << std::endl;
        for (int col = 0; col < row + 1; ++col)
            std::cout << dp_res[row][col] << ", ";
    }
    std::cout << " " << std::endl;
    
    std::vector<std::vector<int>> dp_res_iter = print_pascal_triangle_iter(n);
    for (int row = 0; row < n; ++row) {
        std::cout << " " << std::endl;
        for (int col = 0; col < row + 1; ++col)
            std::cout << dp_res_iter[row][col] << ", ";
    }
    std::cout << " " << std::endl;
    
    std::vector<int> prices {8, 9, 3, 7, 4, 16, 12};
    std::cout << maxProfit(prices) << std::endl;
    
    std::vector<int> coins {1, 2, 5};
    int amount = 11;
    std::cout << coinChange_recursion(coins, amount) << 
        " " << coinChange(coins, amount) << std::endl;
    
    std::vector<int> coins1 {2};
    int amount1 = 3;
    std::cout << coinChange_recursion(coins1, amount1) << 
        " " << coinChange(coins1, amount1) << std::endl;
        
    std::string str = "babad";
    std::string pal = longestPalindrome_recursion(str);
    for (int i = 0; i < pal.size(); ++i)
            std::cout << pal[i];
    std::cout << "" << std::endl;
    
    std::string pal1 = longestPalindrome(str);
    for (int i = 0; i < pal1.size(); ++i)
            std::cout << pal[i];
    std::cout << "" << std::endl;
    
    return 0;
} 
