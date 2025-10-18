/// Task1. Проверить, является ли список циклическим

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

bool hasCycle(ListNode* head) {
    if (head == nullptr || head.next == nullptr)
        return false;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast)
            return true;
    }
    
    return false;
}



/// Task2. Развернуть односвязный список

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    head = prev;
    return head;
}



/// Task3. Найти середину списка

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}



/// Task4. Удалить элемент из односвязного списка

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
ListNode* removeElements(ListNode* head, int val) {
    ListNode* dummy = new ListNode();
    dummy->next = head;
    ListNode* prev = dummy;
    ListNode* curr = head;

    while (curr != nullptr) {
        if (curr->val == val) {
            prev->next = curr->next;
        } else {
            prev = curr;
        }

        curr = curr->next;
    }

    return dummy->next;
}



/// Task5. Является ли одна строка исходной для другой строки

bool isSubsequence(std::string s, std::string t) {
    std::queue<char> mq;
    
    for (char c : s)
        mq.push(c);
        
    for (char c: t)
        if (c == mq.front())
            mq.pop();
            
    return mq.empty();
}



/// Task6. Является ли слово палиндромом

bool isPalindrome(std::string s) {
    std::deque<char> md;
    
    for (char c : s)
        md.push_back(c);
    
    while (md.size() > 1) {
        if (md.front() == md.back()) {
            md.pop_front();
            md.pop_back();
        } else {
            return false;
        }
    }
    
    return true;
}



/// Task7. Слияние двух отсортированных списков с памятью O(1)

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* dummy = new ListNode();
    ListNode* head = dummy;
    
    while (list1 != nullptr && list2!= nullptr){
        if (list1->val <= list2->val){
            head->next = list1;
            list1 = list1->next;
        }
        else{
            head->next = list2;
            list2 = list2->next;
        }
        head = head->next;
    }

    if (list1 != nullptr)
        head->next = list1;
    else
        head->next = list2;

    return dummy->next;
}









