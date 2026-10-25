#include <iostream>
#include <stack>
#include <fstream>
#include <iomanip>

using namespace std;

class TwoStackQueue {
private:
    stack<int> stack_in;
    stack<int> stack_out;

public:
    // Returns the actual cost of this specific enqueue operation.
    // Enqueue is always a straightforward push onto stack_in.
    int enqueue(int val) {
        int actual_cost = 1;
        
        // TODO: [IMPLEMENTATION REQUIRED]
        // 1. Push the 'val' onto 'stack_in'.
        // 2. Return the base cost of 1.
        
        return actual_cost;
    }

    // Returns the actual cost of this specific dequeue operation.
    // Cost = 1 (for final pop) + (number of elements moved from in to out).
    int dequeue() {
        int actual_cost = 0;

        // TODO: [IMPLEMENTATION REQUIRED]
        // 1. Check if BOTH stacks are empty. If so, return 0 (or handle underflow).
        // 2. Check if 'stack_out' is empty.
        //    If 'stack_out' IS empty, you must transfer EVERYTHING from 'stack_in' to 'stack_out':
        //    While 'stack_in' is not empty:
        //        a. Pop from 'stack_in' and push to 'stack_out'.
        //        b. Charge 1 unit of cost for the pop and 1 unit for the push (Total +2 per element).
        // 3. Pop the top element from 'stack_out' (this is the actual dequeue).
        // 4. Charge 1 final unit of cost for this dequeue.
        // 5. Return the accumulated 'actual_cost'.

        return actual_cost;
    }
    
    bool empty() {
        return stack_in.empty() && stack_out.empty();
    }
};

void runSanityCheck() {
    TwoStackQueue q;
    cout << "--- TWO-STACK QUEUE SANITY CHECK ---" << endl;
    
    // Enqueue 5 elements (Each should cost 1)
    for(int i = 1; i <= 5; i++) {
        q.enqueue(i * 10);
    }
    
    // First Dequeue triggers the expensive transfer phase
    // 5 elements moved: 5 pops + 5 pushes = 10 cost. Plus 1 for the final dequeue = 11.
    int cost_deq1 = q.dequeue(); 
    
    // Second Dequeue pulls directly from stack_out without any transfers
    int cost_deq2 = q.dequeue(); 
    
    cout << "1st Dequeue Cost (Expected 11): " << cost_deq1 << endl;
    cout << "2nd Dequeue Cost (Expected 1) : " << cost_deq2 << endl;
    cout << "------------------------------------" << endl;
}

int main() {
    runSanityCheck(); // Validate student logic before processing the massive run
    
    TwoStackQueue myQueue;
    int batches = 10;
    int batch_size = 500;
    long long total_cost = 0;
    int op_index = 1;
    
    ofstream out("data_queue.txt");
    out << "#Op_Index Actual_Cost Running_Average\n";

    // Simulating heavy, alternating burst traffic (500 pushes followed by 500 pops)
    for (int b = 0; b < batches; ++b) {
        // Enqueue Burst Phase
        for (int i = 0; i < batch_size; ++i) {
            int cost = myQueue.enqueue(op_index);
            total_cost += cost;
            double running_avg = (double)total_cost / op_index;
            out << op_index << " " << cost << " " << fixed << setprecision(2) << running_avg << "\n";
            op_index++;
        }
        
        // Dequeue Burst Phase
        for (int i = 0; i < batch_size; ++i) {
            int cost = myQueue.dequeue();
            total_cost += cost;
            double running_avg = (double)total_cost / op_index;
            out << op_index << " " << cost << " " << fixed << setprecision(2) << running_avg << "\n";
            op_index++;
        }
    }
    
    out.close();
    cout << "Simulation complete. Data recorded in 'data_queue.txt'." << endl;
    return 0;
}