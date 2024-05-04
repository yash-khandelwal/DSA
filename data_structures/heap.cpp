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

	vector<int> arr;
	int capacity;
	int size;
	int heap_type;

public:

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
		if(!this -> valid_node(prnt)) return true;
		if(this -> valid_node(child)) {
			if(this -> heap_type == MAX_HEAP) {
				return this -> arr[prnt] >= this -> arr[child];
			} else if(heap_type == MIN_HEAP) {
				return this -> arr[prnt] <= this -> arr[child];
			}
		}
		return true;
	}

	int parent(int i) {
		return (i - 1) / 2;
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

	void insert(int value) {
		if(this -> exhausted()) return;
		this -> arr[this -> size] = value;
		this -> size ++;
		this -> heapify(this -> parent(this -> size - 1));
	}

	void heapify(int node) {
		if(!this -> valid_node(node)) return;
		int left = this -> left_child(node);
		int right = this -> right_child(node);
		bool swapped = false;
		if(!this -> heap_condition(node, left)) {
			swapped = true;
			int temp = this -> arr[node];
			this -> arr[node] = this -> arr[left];
			this -> arr[left] = temp;
		}
		if(!this -> heap_condition(node, right)) {
			swapped = true;
			int temp = this -> arr[node];
			this -> arr[node] = this -> arr[right];
			this -> arr[right] = temp;
		}
		if(swapped) heapify(this -> parent(node));
	}

	int top() {
		if(this -> empty()) return -1;
		return this -> arr[0];
	}

	void pop() {
		if(this -> empty()) return;
		this -> size--;
		this -> arr[0] = this -> arr[size];
		int left = this -> left_child(0);
		int right = this -> right_child(0);
		bool swapped = false;
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
		if(operation == "insert") {
			int value;
			cin >> value;
			heap.insert(value);
		} else if(operation == "top") {
			cout << heap.top();
		}
		cout << "\n";
	}
	return 0;
}