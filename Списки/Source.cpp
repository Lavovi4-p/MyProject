#include <iostream>
#include <windows.h> 

const int MAX_WORD_LENGTH = 100; 
class Node {
public:
    char data[MAX_WORD_LENGTH]; 
    Node* next;                 

    Node(const char* word) : next(nullptr) {
        copyString(data, word);
    }

private:
    void copyString(char* dest, const char* src) {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0'; 
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addWord(const char* word) {
        Node* newNode = new Node(word);
        if (!head) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void printList() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    bool contains(const char* word) const {
        Node* temp = head;
        while (temp) {
            if (compareStrings(temp->data, word)) { 
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void mergeUnique(const LinkedList& other) {
        Node* temp = other.head;
        while (temp) {
            if (!contains(temp->data)) {
                addWord(temp->data);
            }
            temp = temp->next;
        }
    }

    void sortByLength() {
        if (!head || !head->next) {
            return; 
        }

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            Node* prev = nullptr;

            while (current->next) {
                Node* next = current->next;

                if (stringLength(current->data) > stringLength(next->data)) {
                    swapStrings(current->data, next->data);
                    swapped = true;
                }

                prev = current;
                current = next;
            }
        } while (swapped);
    }

private:
    bool compareStrings(const char* str1, const char* str2) const {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0') {
            if (str1[i] != str2[i]) {
                return false;
            }
            i++;
        }
        return str1[i] == '\0' && str2[i] == '\0'; 
    }

    int stringLength(const char* str) const {
        int length = 0;
        while (str[length] != '\0') {
            length++;
        }
        return length;
    }

    void swapStrings(char* str1, char* str2) {
        char temp[MAX_WORD_LENGTH];
        int i = 0;

        while (str1[i] != '\0') {
            temp[i] = str1[i];
            i++;
        }
        temp[i] = '\0';

        i = 0;
        while (str2[i] != '\0') {
            str1[i] = str2[i];
            i++;
        }
        str1[i] = '\0';

        i = 0;
        while (temp[i] != '\0') {
            str2[i] = temp[i];
            i++;
        }
        str2[i] = '\0';
    }
};

int main() {
    SetConsoleCP(1251);       
    SetConsoleOutputCP(1251); 

    LinkedList list1, list2;

    int n1;
    std::cout << "¬ведите количество элементов дл€ первого списка: ";
    std::cin >> n1;
    std::cout << "¬ведите элементы первого списка:" << std::endl;
    for (int i = 0; i < n1; ++i) {
        char word[MAX_WORD_LENGTH];
        std::cin >> word;
        list1.addWord(word);
    }

    int n2;
    std::cout << "¬ведите количество элементов дл€ второго списка: ";
    std::cin >> n2;
    std::cout << "¬ведите элементы второго списка:" << std::endl;
    for (int i = 0; i < n2; ++i) {
        char word[MAX_WORD_LENGTH];
        std::cin >> word;
        list2.addWord(word);
    }

    list1.sortByLength();
    list2.sortByLength();

    std::cout << "ѕервый список (отсортированный по длине): ";
    list1.printList();

    std::cout << "¬торой список (отсортированный по длине): ";
    list2.printList();

    list1.mergeUnique(list2);

    list1.sortByLength();

    std::cout << "ќбъединенный список (уникальные элементы, отсортированный по длине): ";
    list1.printList();

    return 0;
}