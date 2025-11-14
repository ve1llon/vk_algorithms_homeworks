#include <iostream>
#include <vector>

struct TreeNode {

    TreeNode(int val = 0, TreeNode* _left = nullptr, TreeNode* _right = nullptr)
        : data(val), left(_left), right(_right) {}

    void print() {
        std::cout << data << std::endl;
        if (left) left->print();
        if (right) right->print();
    }

    int data = 0;
    TreeNode* left;
    TreeNode* right;
};


/// Task1. Восстановление бинарного дерева из массива.

TreeNode* buildTree(std::vector<int> arr, int i) {
    if (i >= arr.size())
        return nullptr;

    TreeNode* root = new TreeNode(arr[i]);
    root->left = buildTree(arr, 2*i+1);
    root->right = buildTree(arr, 2*i+2);

    return root;
}


/// Task2. Проверка на симметричность бинарного дерева. (bfs)

bool isSymmetric(TreeNode* root) {
    if (root == nullptr)
        return true;

    std::vector<TreeNode*> queue {root};

    while (!queue.empty()) {
        int n = queue.size();

        for (int i = 0; i < n; ++i) {
            if (queue[i] == nullptr && queue[n-i-1] == nullptr)
                continue;
            if (queue[i] == nullptr || queue[n-i-1] == nullptr)
                return false;
            if (queue[i]->data != queue[n-i-1]->data)
                return false;

            queue.push_back(queue[i]->left);
            queue.push_back(queue[i]->right);
        }
        std::vector<TreeNode*> temp(queue.begin()+n, queue.end());
        queue = temp;
    }

    return true;
}


/// Task3. Поиск минимальной глубины бинарного дерева. (dfs)

int minDepth(TreeNode* root) {
    if (root == nullptr)
        return 0;

    if (root->left == nullptr && root->right == nullptr)
        return 1;

    if (root->left != nullptr && root->right != nullptr)
        return 1 + std::min(minDepth(root->left), minDepth(root->right));

    if (root->left != nullptr)
        return 1 + minDepth(root->left);

    return 1 + minDepth(root->right);
}


/// Task4. Произведение минимального и максимального значения.

int MaxMinMultiplication(std::vector<int> data) {
    if (data.size() < 3)
        return -1;

    int max_index = 1;
    int min_index = 2;

    for (int i = 1; i < data.size(); i = 2*i+1)
        min_index = i;

    for (int i = 1; i < data.size(); i = 2*i+2)
        max_index = i;

    return data[min_index] * data[max_index];

}


/// Task5. Сравнение двух деревьев.

bool isSameTree(TreeNode* a, TreeNode* b) {
    if (a == nullptr && b == nullptr)
        return true;

    if (a == nullptr || b == nullptr)
        return false;

    if (a->data != b->data)
        return false;

    return (isSameTree(a->left, b->left) && isSameTree(a->right, b->right));
}


int main() {

    std::vector<int> arr {3, 8, 8, 9, 6, 6, 9};
    TreeNode* root = buildTree(arr, 0);
    root->print();
    std::cout << "isS = " << isSymmetric(root) << std::endl;

    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);
    root2->print();
    std::cout << "MinD = " << minDepth(root2) << std::endl;
    std::cout << "IsSame = " << isSameTree(root, root2) << std::endl;

}
