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
            cout << setw(MIN_NR) << current->name << endl;
            current = current->next;
        }
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
    
    void gather_customers(string file){
        ifstream inputFile(file);
        if (!inputFile) {
            cout << "Error opening file" << endl;
            return;
        }
        string name;
        while (getline(inputFile,name)) {
            push_back(name);
        }
        inputFile.close();
    }
    
    string get_rand_customer(){
        int size = get_size();
        if (size == 0) {
            return "Empty";
        }
        
        int index = rand() % size;
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->name;
    }
    
    void pick_event(DoublyLinkedList &name,DoublyLinkedList &line ){
        int rand1, rand2, rand3, rand4, rand5;
        rand1 = rand() % 100 +1;
        rand2 = rand() % 100 +1;
        rand3 = rand() % 100 +1;
        rand4 = rand() % 100 +1;
        rand5 = rand() % 100 +1;
        if (rand1 <= 40) {
            event_A(line);
        }
        if (rand2 <= 60) {
            event_B(name,line);
        }
        if (rand3 <= 20) {
            event_C(line);
        }
        if (rand4 <= 10) {
            event_D(line);
        }
        if (rand5 <= 10) {
            event_E(name,line);
        }
        
    }
    void event_A(DoublyLinkedList &line){
        Node *current = line.head;
        cout << current->name << " was served" << endl;
        line.pop_front();
    }
    void event_B(DoublyLinkedList &name,DoublyLinkedList &line){
        string n = name.get_rand_customer();
        cout << n << " joined the line" << endl;
        line.push_back(n);
    }
    void event_C(DoublyLinkedList &line){
        Node *current = line.tail;
        cout << current->name << " (at the rear) left the line" << endl;
        line.pop_back();
    }
    void event_D(DoublyLinkedList &line){
        int length = line.get_size();
        cout << length << endl;
        int val = rand() % length;
        line.delete_pos(val);
        
    }
    void event_E(DoublyLinkedList &name,DoublyLinkedList &line){
        
    }
};

int main() {
    srand(time(0));
    DoublyLinkedList nameList;
    nameList.gather_customers("names.txt");
    DoublyLinkedList lineList;
    cout << "Store opens: " << endl;
    for (int i = 0;  i < MIN_LS; i++) {
        lineList.push_back(nameList.get_rand_customer());
    }
    lineList.print();
    //int step = 2;
    lineList.event_A(lineList);
    lineList.print();
    lineList.event_B(nameList,lineList);
    lineList.print();
    lineList.event_C(lineList);
    lineList.print();
    lineList.event_D(lineList);
    lineList.print();
    /*for (int i = 0; i < MAX_LS - 1; i++) {
        cout << "Time #step" << step << endl;
        lineList.pick_event(nameList,lineList);
        cout << setw(MIN_NR) << "Resulting line" << endl;
        lineList.print();
        step++;
    }*/
    return 0;
}
