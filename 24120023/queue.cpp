#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Queue {
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue();
void enqueue(Queue &q, int key);
int dequeue(Queue &q);
int size(Queue q);
bool isEmpty(Queue q);
void display(ofstream &out, Queue q);

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    Queue* q = nullptr;
    string command;
    while (in >> command) {
        if (command == "init") {
            q = initializeQueue();
            display(out, *q);
            cout << "Init successfully" << endl;
        } else if (command == "enqueue") {
            int val;
            in >> val;
            enqueue(*q, val);
            display(out, *q);
            cout << "Enqueue successfully" << endl;
        } else if (command == "dequeue") {
            if (isEmpty(*q)) {
                out << "EMPTY" << endl;
            } else {
                int val = dequeue(*q);
                display(out, *q);
                cout << "Dequeue successfully " << val << endl;
            }
        }
    }

    in.close();
    out.close();
    return 0;
}
Queue* initializeQueue() {
    Queue* q = new Queue;
    q->head = q->tail = nullptr;
    return q;
}

void enqueue(Queue &q, int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = nullptr;

    if (q.tail == nullptr) { 
        q.head = q.tail = newNode;
    } else {
        q.tail->p_next = newNode;
        q.tail = newNode;
    }
}

int dequeue(Queue &q) {
    if (q.head == nullptr) return -1;
    NODE* temp = q.head;
    int value = temp->key;
    q.head = q.head->p_next;
    if (q.head == nullptr) q.tail = nullptr;
    delete temp;
    return value;
}

int size(Queue q) {
    int count = 0;
    NODE* curr = q.head;
    while (curr != nullptr) {
        count++;
        curr = curr->p_next;
    }
    return count;
}

bool isEmpty(Queue q) {
    return q.head == nullptr;
}

void display(ofstream &out, Queue q) {
    if (isEmpty(q)) {
        out << "EMPTY" << endl;
        return;
    }
    NODE* curr = q.head;
    while (curr != nullptr) {
        out << curr->key;
        if (curr->p_next) out << " ";
        curr = curr->p_next;
    }
    out << endl;
}