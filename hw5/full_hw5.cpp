#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct Node {

    Node(int val = 0, Node* _left = nullptr, Node* _right = nullptr)
        : val(val), left(_left), right(_right), balanceFactor(0) {}

    void print() {
        std::cout << val << std::endl;
        if (left) left->print();
        if (right) right->print();
    }

    int val;
    int balanceFactor;
    Node* left;
    Node* right;
};

Node* buildTree(std::vector<int> arr, int i) {
    if (i >= arr.size())
        return nullptr;

    Node* root = new Node(arr[i]);
    root->left = buildTree(arr, 2*i+1);
    root->right = buildTree(arr, 2*i+2);

    return root;
}

// Task1. Проверка корректности кучи.

bool isMaxHeap(std::vector<int> arr) 
{
    size_t n = arr.size();
    
    for (size_t i = 0; i <= (n-2) / 2; ++i) {
        size_t left = 2*i + 1;
        size_t right = 2*i + 2;
        
        if (left < n && arr[i] < arr[left])
            return false;
        if (right < n && arr[i] < arr[right])
            return false;
    }
    
    return true;
}

// Task1. Проверка корректности кучи. Через обход в ширину.

bool isMaxHeap_BFS(std::vector<int> arr) 
{
    size_t n = arr.size();
    if (n <= 1)
        return true;
    
    std::queue<size_t> queue;
    queue.push(0);
    
    while (queue.size() > 0) {
        size_t i = queue.front();
        size_t left = 2*i + 1;
        size_t right = 2*i + 2;
        queue.pop();
        
        if (left < n){
            if (arr[i] < arr[left])
                return false;
            queue.push(left);
        }
        
        if (right < n){
            if (arr[i] < arr[right])
                return false;
            queue.push(right);
        }
    }
    
    return true;
}

// Task1. Проверка корректности кучи. Новые входные данные.

bool isMaxHeap_node(Node* root) 
{
    if (root == nullptr)
        return true;
        
    std::queue<Node*> queue;
    queue.push(root);
    bool shouldBeLeaf = false;
    
    while (queue.size() > 0) {
        Node* curr = queue.front();
        queue.pop();
        
        if (curr->left != nullptr){
            if (shouldBeLeaf || curr->val < curr->left->val)
                return false;
            queue.push(curr->left);
        } else {
            shouldBeLeaf = true;
        }
        
        if (curr->right != nullptr){
            if (shouldBeLeaf || curr->val < curr->right->val)
                return false;
            queue.push(curr->right);
        } else {
            shouldBeLeaf = true;
        }
        
    }
    
    return true;
}

// Task2. Полное бинарное дерево.

bool isCompleteTree(Node* root)
{
    if (root == nullptr)
        return true;
        
    std::queue<Node*> queue;
    queue.push(root);
    bool shouldBeLeaf = false;
    
    while (queue.size() > 0) {
        Node* curr = queue.front();
        queue.pop();
        
        if (curr == nullptr){
            shouldBeLeaf = true;
        } else {
            if (shouldBeLeaf)
                return false;
            queue.push(curr->left);
            queue.push(curr->right);
        }
        
    }
    
    return true;
}

// Task3. Объединение K отсортированных массивов. Простой вариант.

std::vector<int> mergeKSortedArrays_simple(std::vector<std::vector<int>> arrs)
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    
    for (size_t i = 0, k = arrs.size(); i < k; ++i) 
        for (size_t j = 0, n = arrs[i].size(); j < n; ++j) 
            min_heap.push(arrs[i][j]);
            
    std::vector<int> result;
    while (min_heap.size() > 0) {
        result.push_back(min_heap.top());
        min_heap.pop();
    }
    
    return result;
}

// Task3. Объединение K отсортированных массивов. 

std::vector<int> mergeKSortedArrays(std::vector<std::vector<int>> arrs)
{
    using tuple = std::tuple<int, size_t, size_t>;
    std::priority_queue<tuple, std::vector<tuple>, std::greater<tuple>> min_heap;
    
    for (size_t i = 0, k = arrs.size(); i < k; ++i) {
        std::vector<int> curr_arr = arrs[i];
        if (curr_arr.size() > 0)
            min_heap.push({curr_arr[0], i, 0});
    }
            
    std::vector<int> result;
    while (min_heap.size() > 0) {
        auto [value, arrId, elemId] = min_heap.top();
        min_heap.pop();
        
        result.push_back(value);
        
        if (elemId + 1 < arrs[arrId].size()) 
            min_heap.push({arrs[arrId][elemId+1], arrId, elemId+1});
    }
    
    return result;
}

// Task4. К-ый наименьший/наибольший элемент в BST. Итеративный метод.

int inorderMinIterative(Node* node, int k) 
{
    std::stack<Node*> stack;
    int counter = 0;
    Node* curr = node;
    
    while (stack.size() > 0  || curr != nullptr) {
        
        while (curr != nullptr) {
            stack.push(curr);
            curr = curr->left;
        }
        
        curr = stack.top();
        stack.pop();
        
        counter++;
        if (counter == k)
            return curr->val;
        
        curr = curr->right;
    }
    
    return 1000000;
}

// Task4. К-ый наименьший/наибольший элемент в BST. Рекурсивный метод.

int inorderMin(Node* node, int k, int& counter)
{
    if (node == nullptr)
        return 1000000;
    
    int left_res = inorderMin(node->left, k, counter);
    if (left_res != 1000000) 
        return left_res;
        
    counter++;
    if (counter == k)
        return node->val;
    
    return inorderMin(node->right, k, counter);
}

// Task5. Balance factor.

int calculateHeightsAndBalance(Node* node) 
{
    if (node == nullptr)
        return 0;
    
    int left_res = calculateHeightsAndBalance(node->left);
    int right_res = calculateHeightsAndBalance(node->right);
    
    node->balanceFactor = left_res - right_res;
    return 1 + std::max(left_res, right_res);
}

// Task6. Преобразование в зеркальное дерево. Итеративный вариант.

Node* mirrorTreeIterative(Node* node)
{
    if (node == nullptr)
        return nullptr;
    
    std::queue<Node*> queue;
    queue.push(node);
    
    while (queue.size() > 0) {
        Node* curr = queue.front();
        queue.pop();
        
        std::swap(curr->left, curr->right);      
        
        if (curr->left != nullptr)
            queue.push(curr->left);
        if (curr->right != nullptr)
            queue.push(curr->right);
    }
    
    return node;
}

// Task6. Преобразование в зеркальное дерево. Рекурсивный вариант.

Node* mirrorTree(Node* node)
{
    if (node == nullptr)
        return nullptr;
    
    node->left, node->right = node->right, node->left;
    
    mirrorTree(node->left);
    mirrorTree(node->right);
    
    return node;
}

int main() {
    std::vector<int> arr1 {7, 9, 8, 11, 1, 36, 4, 3, 16, 17};
    std::vector<int> arr2 {36, 16, 17, 9, 11, 8, 7, 4, 1, 3};
    
    std::cout << isMaxHeap(arr1) << " " 
              << isMaxHeap(arr2) << std::endl;
    std::cout << isMaxHeap_BFS(arr1) << " " 
              << isMaxHeap_BFS(arr2) << std::endl;

    Node* root1 = new Node(7);
    root1->left = new Node(9);
    root1->right = new Node(8);
    root1->left->left = new Node(11);
    root1->left->right = new Node(1);
    
    Node* root2 = new Node(36);
    root2->left = new Node(16);
    root2->right = new Node(17);
    root2->left->left = new Node(9);
    root2->left->right = new Node(11);
    
    Node* root3 = new Node(36);
    root3->left = new Node(16);
    root3->right = new Node(17);
    root3->left->left = new Node(9);
    root3->right->right = new Node(11);
    
    std::cout << isMaxHeap_node(root1) << " " 
              << isMaxHeap_node(root2) << " " 
              << isMaxHeap_node(root3) << std::endl;
    std::cout << isCompleteTree(root1) << " " 
              << isCompleteTree(root2) << " " 
              << isCompleteTree(root3) << std::endl;
              
    
    std::vector<std::vector<int>> arrs {
        {1, 3, 5, 7}, {2, 4, 6}, {0, 8, 9, 11}
    };
    
    std::vector<int> res_s = mergeKSortedArrays_simple(arrs);
    for (int i = 0, n = res_s.size(); i < n; ++i)
        std::cout << res_s[i] << " ";
    std::cout << "" << std::endl;
    
    std::vector<int> res = mergeKSortedArrays(arrs);
    for (int i = 0, n = res.size(); i < n; ++i)
        std::cout << res[i] << " ";
    std::cout << "" << std::endl;
    
    std::vector<int> arr3 {36, 16, 50, 13, 20, 40, 54, 1, 14, 18};
    Node* root_arr3 = buildTree(arr3, 0);
    
    std::cout << inorderMinIterative(root_arr3, 4) << std::endl;
    int counter = 0;
    std::cout << inorderMin(root_arr3, 4, counter) << std::endl;
    
    std::cout << calculateHeightsAndBalance(root_arr3) << " "
              << root_arr3->balanceFactor << std::endl;
              
    Node* root_arr3_mir = mirrorTreeIterative(root_arr3);
    Node* root_arr3_mir2 = mirrorTree(root_arr3);
    //root_arr3_mir->print();
    //root_arr3_mir2->print();
    
    return 0;
}
