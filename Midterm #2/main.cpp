//
//  main.cpp
//  COMSC-210 | Midterm #2 | Guo An Wang
//  IDE: Xcode
//  Created by Guo An Wang on 10/19/25.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string name;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            name = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    //unused function
    /*void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->name != value)
            temp = temp->next;

        if (!temp) return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    } */

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->name << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->name << " ";
            current = current->prev;
        }
        cout << endl;
    }
    
    int get_size(){
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    void choose_customer(string file){
        ifstream inputFile(file);
        if (!inputFile) {
            cout << "Error opening file" << endl;
            return;
        }
        string name;
        while (getline(inputFile,name)) {
            push_back(name);
        }
    }
    
    void get_rand_customer(){
        int size = get_size();
        if (size == 0) {
            cout << "linked list is empty" << endl;
            return;
        }
        
    }
    
    void pick_event(){
        int rand1, rand2, rand3, rand4, rand5;
        rand1 = rand() % 100 +1;
        rand2 = rand() % 100 +1;
        rand3 = rand() % 100 +1;
        rand4 = rand() % 100 +1;
        rand5 = rand() % 100 +1;
        if (rand1 <= 40) {
            event_A();
        }
        if (rand2 <= 60) {
            event_B();
        }
        if (rand3 <= 20) {
            event_C();
        }
        if (rand4 <= 10) {
            event_D();
        }
        if (rand5 <= 10) {
            event_E();
        }
        
    }
    void event_A(){
        
    }
    void event_B(){
        
    }
    void event_C(){
        
    }
    void event_D(){
        
    }
    void event_E(){
        
    }
};

int main() {
    srand(time(0));
    DoublyLinkedList nameList;
    nameList.choose_customer("names.txt");
    cout << nameList.get_size() << endl;
    nameList.print();
    /*cout << "Store opens: " << endl;
    for (int i = 0;  i < MIN_LS; i++) {
        
    }
    
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning*/
    
    
    return 0;
}
