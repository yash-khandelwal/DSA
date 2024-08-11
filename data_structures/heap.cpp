#include<bits/stdc++.h>
using namespace std;


// Implement a Heap from scratch
/*
heap should have maximum capacity
we can 
- insert an element
- get Minimum/Maximum element
- delete Minimum/Maximum element
*/

int MAX_HEAP = 0;
int MIN_HEAP = 1;


class Heap {

public:

	vector<int> arr;
	int capacity;
	int size;
	int heap_type;

	Heap(int capacity, int heap_type) {
		this -> capacity = capacity;
		this -> heap_type = heap_type;
		this -> arr.resize(capacity);
		this -> size = 0;
	}

	// helper functions

	bool empty() {
		return this -> size == 0;
	}

	bool exhausted() {
		return this -> size == this -> capacity;
	}

	bool valid_node(int node) {
		return node < this -> size && node >= 0;
	}

	bool heap_condition(int prnt, int child) {
		if(!this -> valid_node(prnt) || !this -> valid_node(child)) return true;
		if(this -> heap_type == MAX_HEAP) return this -> arr[prnt] >= this -> arr[child];
		else if(heap_type == MIN_HEAP) return this -> arr[prnt] <= this -> arr[child];
		return true;
	}

	int parent(int i) {
		return i == 0 ? -1 : (i - 1) / 2;
	}

	int left_child(int i) {
		int left = 2 * i + 1;
		if(this -> size <= left) return -1;
		return left;
	}

	int right_child(int i) {
		int right = 2 * i + 2;
		if(this -> size <= right) return -1;
		return right;
	}

	void push(int value) {
		if(this -> exhausted()) return;
		this -> arr[this -> size] = value;
		this -> size ++;
		this -> bottom_up_heapify(this -> size - 1);
	}

	void pop() {
		if(this -> empty()) return;
		this -> arr[0] = this -> arr[size - 1];
		this -> size --;
		this -> top_down_heapify(0);
	}

	void top_down_heapify(int node) {
		if(!this -> valid_node(node)) return;
		int left = this -> left_child(node);
		int right = this -> right_child(node);
		int next = node;
		if(!this -> heap_condition(next, left)) next = left;
		if(!this -> heap_condition(next, right)) next = right;
		if(next != node) {
			swap(arr[node], arr[next]);
			top_down_heapify(next);
		}
	}

	void bottom_up_heapify(int node) {
		if(!this -> valid_node(node)) return;
		int prnt = this -> parent(node);
		if(!this -> heap_condition(prnt, node)) {
			swap(this -> arr[prnt], this -> arr[node]);
			bottom_up_heapify(prnt);
		}
	}

	int top() {
		if(this -> empty()) return -1;
		return this -> arr[0];
	}

};


int main () {
	int h_type;
	cin >> h_type;
	Heap heap = Heap(10, h_type);
	int q;
	cin >> q;
	cout << "\n";
	while(q--) {
		string operation;
		cin >> operation;
		if(operation == "push") {
			int value;
			cin >> value;
			heap.push(value);
		} else if(operation == "top") {
			cout << heap.top();
		} else if(operation == "pop") {
			heap.pop();
			// cout << "heap size after pop is " << heap.size << "\n";
		} else if(operation == "stop") {
			cout << "Stopped!";
			exit(0);
		} else {
			cout << "operation '" << operation << "' is not suported!";
		}
		cout << "\n";
	}
	return 0;
}

