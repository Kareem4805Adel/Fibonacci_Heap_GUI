#include <iostream>
#include "linkedlist.cpp"
#include "heap.h"

using namespace std;

void printSeparator() {
    cout << "\n" << string(60, '=') << "\n\n";
}

void testBasicNodeCreation() {
    cout << "TEST 1: Basic Node Creation\n";
    cout << string(60, '-') << "\n";

    node a(10, "Sample Task");
    cout << "Node created with key: " << a.key
         << " and Taskname: " << a.Taskname << endl;
    cout << "Left->key: " << a.left->key << endl;
    cout << "Right->key: " << a.right->key << endl;
    cout << "Children empty: " << (a.children->isEmpty() ? "Yes" : "No") << endl;
    cout << "Degree: " << a.degree << endl;
    cout << "✓ Test Passed: Node created successfully\n";
}

void testHeapCreationAndInsert() {
    cout << "TEST 2: Heap Creation and Single Insert\n";
    cout << string(60, '-') << "\n";

    FibonacciHeap heap;
    node* n1 = new node(5, "Task A");

    heap.insert(n1);
    node* min = heap.findMin();

    if (min != nullptr && min->key == 5) {
        cout << "✓ Inserted node with key 5\n";
        cout << "✓ Min is: " << min->key << " (Task: " << min->Taskname << ")\n";
        cout << "✓ Test Passed\n";
    } else {
        cout << "✗ Test Failed: Min is incorrect\n";
    }
}

void testMultipleInserts() {
    cout << "TEST 3: Multiple Inserts and FindMin\n";
    cout << string(60, '-') << "\n";

    FibonacciHeap heap;
    node* n1 = new node(10, "Task A");
    node* n2 = new node(5, "Task B");
    node* n3 = new node(20, "Task C");
    node* n4 = new node(3, "Task D");

    heap.insert(n1);
    cout << "Inserted key 10, Min: " << heap.findMin()->key << endl;

    heap.insert(n2);
    cout << "Inserted key 5, Min: " << heap.findMin()->key << endl;

    heap.insert(n3);
    cout << "Inserted key 20, Min: " << heap.findMin()->key << endl;

    heap.insert(n4);
    cout << "Inserted key 3, Min: " << heap.findMin()->key << endl;

    if (heap.findMin()->key == 3) {
        cout << "✓ Test Passed: Min is correctly 3\n";
    } else {
        cout << "✗ Test Failed: Expected min 3, got " << heap.findMin()->key << "\n";
    }
}

void testExtractMin() {
    cout << "TEST 4: Extract Min\n";
    cout << string(60, '-') << "\n";

    FibonacciHeap heap;
    node* n1 = new node(10, "Task A");
    node* n2 = new node(5, "Task B");
    node* n3 = new node(15, "Task C");

    heap.insert(n1);
    heap.insert(n2);
    heap.insert(n3);

    cout << "Initial min: " << heap.findMin()->key << endl;

    node* extracted = heap.extractMin();
    cout << "Extracted: " << extracted->key << " (Task: " << extracted->Taskname << ")\n";

    cout << "New min: " << heap.findMin()->key << endl;

    if (extracted->key == 5 && heap.findMin()->key == 10) {
        cout << heap.findMin()->children->isEmpty();
        cout << "✓ Test Passed: Extracted 5, new min is 10\n";
    } else {
        cout << "✗ Test Failed\n";
    }

    delete extracted;
}

void testDecreaseKey() {
    cout << "TEST 5: Decrease Key\n";
    cout << string(60, '-') << "\n";

    FibonacciHeap heap;
    node* n1 = new node(10, "Task A");
    node* n2 = new node(5, "Task B");
    node* n3 = new node(15, "Task C");

    heap.insert(n1);
    heap.insert(n2);
    heap.insert(n3);

    cout << "Initial min: " << heap.findMin()->key << endl;
    cout << "Decreasing key of Task C from 15 to 2\n";

    heap.decreaseKey(n3, 2);

    cout << "New min: " << heap.findMin()->key << " (Task: " << heap.findMin()->Taskname << ")\n";

    if (heap.findMin()->key == 2 && heap.findMin()->Taskname == "Task C") {
        cout << "✓ Test Passed: Min is now 2 (Task C)\n";
    } else {
        cout << "✗ Test Failed\n";
    }
}

void testDeleteNode() {
    cout << "TEST 6: Delete Node\n";
    cout << string(60, '-') << "\n";

    FibonacciHeap heap;
    node* n1 = new node(10, "Task A");
    node* n2 = new node(5, "Task B");
    node* n3 = new node(15, "Task C");
    node* n4 = new node(20, "Task D");

    heap.insert(n1);
    heap.insert(n2);
    heap.insert(n3);
    heap.insert(n4);

    cout << "Initial min: " << heap.findMin()->key << endl;
    cout << "Deleting node with key 15 (Task C)\n";

    heap.deleteNode(n3);

    cout << "Min after deletion: " << heap.findMin()->key << endl;

    cout << "✓ Test completed: Node deleted\n";
}

void testMultipleExtracts() {
    cout << "TEST 7: Multiple Extract Mins\n";
    cout << string(60, '-') << "\n";

    FibonacciHeap heap;
    int keys[] = {15, 10, 20, 5, 30, 25};
    string tasks[] = {"Task A", "Task B", "Task C", "Task D", "Task E", "Task F"};

    cout << "Inserting keys: ";
    for (int i = 0; i < 6; i++) {
        heap.insert(new node(keys[i], tasks[i]));
        cout << keys[i] << " ";
    }
    cout << "\n\n";

    cout << "Extracting in order:\n";
    for (int i = 0; i < 6; i++) {
        node* extracted = heap.extractMin();
        if (extracted != nullptr) {
            cout << i+1 << ". Key: " << extracted->key
                 << " (Task: " << extracted->Taskname << ")\n";
            delete extracted;
        }
    }

    cout << "✓ Test completed: All nodes extracted\n";
}

void testEdgeCases() {
    cout << "TEST 8: Edge Cases\n";
    cout << string(60, '-') << "\n";

    // Test 1: Extract from empty heap
    FibonacciHeap heap1;
    node* result = heap1.extractMin();
    cout << "Extract from empty heap: " << (result == nullptr ? "NULL (correct)" : "Not NULL") << "\n";

    // Test 2: Single node heap
    FibonacciHeap heap2;
    node* single = new node(42, "Single Task");
    heap2.insert(single);
    node* extracted = heap2.extractMin();
    cout << "Single node extract: " << (extracted->key == 42 ? "✓ Correct" : "✗ Failed") << "\n";
    delete extracted;

    // Test 3: Decrease key validation
    FibonacciHeap heap3;
    node* n = new node(10, "Test");
    heap3.insert(n);
    cout << "Attempting to decrease 10 to 15 (should fail): ";
    heap3.decreaseKey(n, 15);  // Should print error

    cout << "✓ Edge cases tested\n";
}

void testComplexScenario() {
    cout << "TEST 9: Complex Scenario\n";
    cout << string(60, '-') << "\n";

    FibonacciHeap heap;

    cout << "Building a complex heap structure...\n";

    node* n1 = new node(10, "Priority 10");
    node* n2 = new node(20, "Priority 20");
    node* n3 = new node(5, "Priority 5");
    node* n4 = new node(15, "Priority 15");
    node* n5 = new node(30, "Priority 30");

    heap.insert(n1);
    heap.insert(n2);
    heap.insert(n3);
    heap.insert(n4);
    heap.insert(n5);

    cout << "1. Initial min: " << heap.findMin()->key << endl;

    // Extract min
    node* extracted1 = heap.extractMin();
    cout << "2. Extracted: " << extracted1->key << ", new min: " << heap.findMin()->key << endl;
    delete extracted1;

    // Decrease key
    cout << "3. Decreasing Priority 30 to Priority 2\n";
    heap.decreaseKey(n5, 2);
    cout << "   New min: " << heap.findMin()->key << endl;

    // Delete a node
    cout << "4. Deleting Priority 15\n";
    heap.deleteNode(n4);
    cout << "   Current min: " << heap.findMin()->key << endl;

    // Extract remaining
    cout << "5. Extracting remaining nodes:\n";
    int count = 0;
    while (true) {
        node* n = heap.extractMin();
        if (n == nullptr) break;
        cout << "   - Extracted: " << n->key << " (" << n->Taskname << ")\n";
        delete n;
        count++;
    }

    cout << "✓ Test completed: " << count << " nodes extracted\n";
}

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║        FIBONACCI HEAP - COMPREHENSIVE TEST SUITE          ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";

    printSeparator();
    testBasicNodeCreation();

    printSeparator();
    testHeapCreationAndInsert();

    printSeparator();
    testMultipleInserts();

    printSeparator();
    testExtractMin();

    printSeparator();
    testDecreaseKey();

    printSeparator();
    testDeleteNode();

    printSeparator();
    testMultipleExtracts();

    printSeparator();
    testEdgeCases();

    printSeparator();
    testComplexScenario();

    printSeparator();
    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║                  ALL TESTS COMPLETED                       ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n\n";

    return 0;
}

node* FibonacciHeap::insert(node* newNode){
    rootlist->insertLast(newNode);

    if (min == nullptr || newNode->key < min->key) {
        min = newNode;
    }

    return newNode;
}

node* FibonacciHeap::findMin() const{
    return min;
}

node* FibonacciHeap::extractMin() {
    node* z = findMin();
    if (z != nullptr) {

        if (!z->children->isEmpty()) {
            int Children = z->children->size();
            CircularDoublyLinkedList<node *> childrenCopy(*z->children);
            Node<node*>* current = childrenCopy.head;
            for (int i = 0; i < Children; i++) {
                node* x = current->data;
                x->parent = nullptr;
                rootlist->insertLast(x);
                current = current->next;
            }
        }

        rootlist->deleteValue(z);

        if (rootlist->isEmpty()) {
            min = nullptr;
        } else {
            min = rootlist->head->data;
            Consolidate();
        }
    }
    return z;
}

void FibonacciHeap::decreaseKey(node* handle, int newKey){

    if (newKey > handle->key) {
        cout << "Error: new key is greater than current key" << endl;
        return;
    }

    handle->key = newKey;
    node* parent = handle->parent;

    if (parent != nullptr && handle->key < parent->key) {
        Cut(handle, parent);
        cascading_cut(parent);
    }

    if (min == nullptr || handle->key < min->key) {
        min = handle;
    }
}

void FibonacciHeap::deleteNode(node* handle){
    decreaseKey(handle, INT_MIN);
    extractMin();
}

void FibonacciHeap::Consolidate(){
    const int MAX_DEGREE = 64;
    node* A[MAX_DEGREE];
    for (int i = 0; i < MAX_DEGREE; i++){
        A[i] = nullptr;
    }

    int rootSize = rootlist->size();
    if (rootSize == 0) return;


    CircularDoublyLinkedList<node*> RootListCopy(*rootlist);
    Node<node*>* current = RootListCopy.head;

    for (int i = 0; i < rootSize; i++) {
        node* x = current->data;
        int d = x->degree;

        while (A[d] != nullptr) {
            node* y = A[d];
            if (x->key > y->key) {
                node* temp = x;
                x = y;
                y = temp;
            }
            Link(x, y);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
        current = current->next;
    }


    min = nullptr;
    delete rootlist;
    rootlist = new CircularDoublyLinkedList<node*>();
    for (int i = 0; i < MAX_DEGREE; i++){
        if (A[i] != nullptr){
            rootlist->insertLast(A[i]);
            if (min == nullptr || A[i]->key < min->key){
                min = A[i];
            }
        }
    }

}

void FibonacciHeap::Link(node* x, node*y){
    rootlist->deleteValue(y);
    x->children->insertLast(y);
    y->parent = x;
    x->degree++;
    y->mark = false;
}

void FibonacciHeap::Cut(node* x, node*y){
    y->children->deleteValue(x);
    y->degree--;
    insert(x);
    x->parent = nullptr;
    x->mark = false;
}

void FibonacciHeap::cascading_cut(node* y){
    node* z = y->parent;
    if (z != nullptr){
        if (y->mark == false){
            y->mark = true;
        }else{
            Cut(y, z);
            cascading_cut(z);
        }
    }
}
