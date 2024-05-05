#include<bits/stdc++.h>
using namespace std;


class AVLNode {

public:
	int val;
	int height;
	AVLNode* left;
	AVLNode* right;

	AVLNode(int val) {
		this -> val = val;
		this -> height = 1;
	}

	static int getHeight(AVLNode* node) {
		if(!node) return 0;
		return node -> height;
	}

	static void inorder(AVLNode* node, vector<AVLNode*> &v) {
		if(!node) return;
		inorder(node -> left, v);
		v.push_back(node);
		inorder(node -> right, v);
	}

	static void preorder(AVLNode* node, vector<AVLNode*> &v) {
		if(!node) return;
		v.push_back(node);
		preorder(node -> left, v);
		preorder(node -> right, v);
	}

	static AVLNode* LLrotation(AVLNode* node) {
		AVLNode* temp = node -> left;
		node -> left = temp -> right;
		temp -> right = node;
		node -> height = max(getHeight(node -> left), getHeight(node -> right)) + 1;
		temp -> height = max(getHeight(temp -> left), getHeight(temp -> right)) + 1;
		return temp;
	}

	static AVLNode* RRrotation(AVLNode* node) {
		AVLNode* temp = node -> right;
		node -> right = temp -> left;
		temp -> left = node;
		node -> height = max(getHeight(node -> left), getHeight(node -> right)) + 1;
		temp -> height = max(getHeight(temp -> left), getHeight(temp -> right)) + 1;
		return temp;
	}

	static AVLNode* LRrotation(AVLNode* node) {
		node -> left = RRrotation(node -> left);
		return LLrotation(node);
	}

	static AVLNode* RLrotation(AVLNode* node) {
		node -> right = LLrotation(node -> right);
		return RRrotation(node);
	}

	static AVLNode* balance(AVLNode *node) {
		if(!node) return node;
		if(getHeight(node -> left) - getHeight(node -> right) == 2) { // L heavy
			if(getHeight(node -> left -> left) > getHeight(node -> left -> right)) { // LL rotation
				node = LLrotation(node);
			} else { // LR rotation
				node = LRrotation(node);
			}
		} else if(getHeight(node -> right) - getHeight(node -> left) == 2) { // R heavy
			if(getHeight(node -> right -> left) > getHeight(node -> right -> right)) { // RL rotation
				node = RLrotation(node);
			} else { // RR rotation
				node = RRrotation(node);
			}
		}
		node -> height = max(getHeight(node -> left), getHeight(node -> right)) + 1;
		return node;
	}

	static AVLNode* insert(AVLNode* node, int val) {
		if(!node) return new AVLNode(val);
		if(node -> val > val) node -> left = insert(node -> left, val);
		else if(node -> val < val) node -> right = insert(node -> right, val);
		return balance(node);
	}

	static AVLNode* remove(AVLNode* node, int val) {
		if(!node) return NULL;
		if(node -> val > val) node -> left = balance(remove(node -> left, val));
		else if(node -> val < val) node -> right = balance(remove(node -> right, val));
		else { // node -> val == val
			if(!node -> left || !node -> right) return node -> left ? node -> left : node -> right;
			AVLNode* pred = node -> left;
			while(pred -> right) pred = pred -> right;
			node -> val = pred -> val;
			node -> left = remove(node -> left, pred -> val);
		}
		return balance(node);
	}

};


int main () {

	int q;
	cin >> q;
	AVLNode* root = NULL;
	while(q--) {
		string operation;
		cin >> operation;
		if(operation == "insert") {
			int val;
			cin >> val;
			root = AVLNode::insert(root, val);
			cout << "After inserting " << val << " new height of the tree = " << (root -> height) << "\n";
		} else if(operation == "delete") {
			int val;
			cin >> val;
			root = AVLNode:: remove(root, val);
			cout << "After deleting " << val << " new height of the tree = " << (root -> height) << "\n";
		} else if(operation == "inorder") {
			vector<AVLNode*> v;
			AVLNode::inorder(root, v);
			cout << "Inorder Traversal = [ ";
			for(AVLNode* node: v) {
				cout << "( " << (node -> val) << ", " << (node -> height) << "), ";
			}
			cout << "]\n";
		} else if(operation == "preorder") {
			vector<AVLNode*> v;
			AVLNode::preorder(root, v);
			cout << "Preorder Traversal = [ ";
			for(AVLNode* node: v) {
				cout << "( " << (node -> val) << ", " << (node -> height) << "), ";
			}
			cout << "]\n";
		} else if(operation == "stop") {
			cout << "Stopped!\n";
			exit(0);
		} else {
			cout << "operation = '" << operation << "' is node supported!\n";
		}
	}
	return 0;
}