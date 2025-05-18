#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Stack {
    NODE* top;
};
void display(ofstream &out, Stack s);
Stack *initializeStack();      // Initialize an empty Stack
void push(Stack &s, int key);  // Put a new element onto the Stack
int pop(Stack &s);             // Pop the top element off the Stack and return its value
int size(Stack s);            // Return the number of elements in the Stack
bool isEmpty(Stack s);        // Return true if the Stack is empty

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    if (!in.is_open())
    {
        cout << "Can not open the input file";
    }
    if (!out.is_open())
    {
        cout << "Can not open the output file";
    }
    Stack* s = nullptr;
    string command;
    while (in >> command) {
        if (command == "init") {
            s = initializeStack();
            display(out, *s);
            cout << "Init successfully" << endl;
        } else if (command == "push") {
            int val;
            in >> val;
            push(*s, val);
            display(out, *s);
            cout <<"Push successfully" << endl;
        } else if (command == "pop") {
            if (isEmpty(*s)) {
                out << "EMPTY" << endl;
            } else {
                int val = pop(*s);
                display(out, *s);
                cout << "Pop successfully " << val << "\n";
            }
        }
    }
    in.close();
    out.close();
    return 0;
}

Stack* initializeStack() {
    Stack* s = new Stack;
    s->top = nullptr;
    return s;
}

void push(Stack &s, int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = s.top;
    s.top = newNode;
}

int pop(Stack &s) {
    if (s.top == nullptr) return -1;
    NODE* temp = s.top;
    int value = temp->key;
    s.top = s.top->p_next;
    delete temp;
    return value;
}

int size(Stack s) {
    int count = 0;
    NODE* curr = s.top;
    while (curr != nullptr) {
        count++;
        curr = curr->p_next;
    }
    return count;
}

bool isEmpty(Stack s) {
    return s.top == nullptr;
}

// Ghi toàn bộ Stack ra file (từ dưới lên top )
void display(ofstream &out, Stack s) {
    if (isEmpty(s)) {
        out << "EMPTY" << endl;
        return;
    }
    int n = size(s);
    int *a = new int [n];
    int cur = 0;
    NODE* curr = s.top;
    while (curr != nullptr) {
        a[cur] = curr->key;
        //if (curr->p_next) out << " ";
        curr = curr->p_next;
        cur++;
    }
    for (int i = n-1; i > 0; i-- ) out << a[i] << " ";
    out << a[0] << endl;
    delete [] a;
}
