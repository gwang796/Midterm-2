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
        Node* tempNext = temp->next;
        tempPrev->next = tempNext;
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
    //function get_size finds size of linked list
    //arguments: none
    //return: int size
    int get_size(){
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
    //function gather_customers opens name.txt file and adds it to linked list
    //arguments: string file
    //return: none
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
    //funtion get_rand_customer chooses a random customer from
    //arguments: linked list name
    //return: string name
    string get_rand_customer(DoublyLinkedList &name){
        int size = name.get_size();
        if (size == 0) {
            return "Empty";
        }
        
        int index = rand() % size;
        Node* current = name.head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->name;
    }
    //function pick_event chooses from the possible events
    //arguments: linked list line, linked list name
    //return : none
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
    //function event_A occurs when person at the front of line is served
    //arguments: linked list line
    //return: none
    void event_A(DoublyLinkedList &line){
        Node *current = line.head;
        cout << current->name << " was served" << endl;
        line.pop_front();
    }
    //function event_B occurs when person joins back of line
    //arguments: linked list line, linked list name
    //return: none
    void event_B(DoublyLinkedList &name,DoublyLinkedList &line){
        string n = name.get_rand_customer(name);
        cout << n << " joined the line" << endl;
        line.push_back(n);
    }
    //function event_A occurs when person at bakc of line leaves
    //arguments: linked list line
    //return: none
    void event_C(DoublyLinkedList &line){
        Node *current = line.tail;
        cout << current->name << " (at the rear) left the line" << endl;
        line.pop_back();
    }
    //function event_A occurs when somebody in the line leaves
    //arguments: linked list line
    //return: none
    void event_D(DoublyLinkedList &line){
        int length = line.get_size();
        if (length == 0) {
            cout << "Empty line" << endl;
            return;
        }
        int val = rand() % length;
        Node *current = line.head;
        for (int i = 0; i < val; i++) {
            current = current->next;
        }
        cout << setw(MIN_NR) << current->name << " has left the line" << endl;
        line.delete_pos(val);
        
    }
    //function event_A occurs when an VIP joins front of the line
    //arguments: linked list line
    //return: none
    void event_E(DoublyLinkedList &name,DoublyLinkedList &line){
        string n = name.get_rand_customer(name);
        cout << n << " (VIP) joins the front of line" << endl;
        line.push_front(n);
    }
};

int main() {
    srand(time(0));
    DoublyLinkedList nameList; //declaring nameList linked list
    nameList.gather_customers("names.txt"); //calling gather_customer function
    //makes it so we don't access names file everytime instead another linked list
    DoublyLinkedList lineList;
    string name;
    cout << "Store opens: " << endl;
    for (int i = 0;  i < MIN_LS; i++) {
        name = nameList.get_rand_customer(nameList);
        lineList.push_back(name);
        cout << name << " joins the line" << endl;
    }

    int step = 2;
    for (int i = 0; i < MAX_LS - 1; i++) {
        if (lineList.get_size()==0) {
            cout << "Line is empty" << endl;
            return 0;
        }
        cout << "Time step #" << step << endl;
        lineList.pick_event(nameList,lineList);
        cout << setw(MIN_NR) << "Resulting line: " << endl;
        lineList.print();
        step++;
    }
    return 0;
}
