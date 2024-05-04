#include<bits/stdc++.h>
using namespace std;


class BSTNode {
public:
	int val;
	BSTNode* left;
	BSTNode* right;
	BSTNode(int val) {
		this -> val = val;
	}

	BSTNode* predecessor() {
		BSTNode* pred = this -> left;
		while(pred && pred -> right) pred = pred -> right;
		return pred;
	}

	BSTNode* successor() {
		BSTNode* succ = this -> right;
		while(succ && succ -> left) succ = succ -> left;
		return succ;
	}

	static BSTNode* insert(BSTNode* node, int val) {
		if(!node) return new BSTNode(val);
		if(val < node -> val) node -> left = insert(node -> left, val);
		else if(val > node -> val) node -> right =  insert(node -> right, val);
		return node;
	}

	static BSTNode* search(BSTNode* node, int val) {
		if(!node) return NULL;
		if(node -> val > val) return search(node -> left, val);
		else if(node -> val < val) return search(node -> right, val);
		return node;
	}

	static BSTNode* remove(BSTNode* node, int val) {
		if(!node) return NULL;
		if(node -> val > val) {
			node -> left = remove(node -> left, val);
			return node;
		}
		if(node -> val < val) {
			node -> right = remove(node -> right, val);
			return node;
		}
		if(!node -> left && !node -> right) return NULL;
		if(!node -> left || !node -> right) return node -> left ? node -> left : node -> right;
		BSTNode* pred = node -> left;
		BSTNode* pred_parent = node;
		while(pred -> right) {
			pred_parent = pred;
			pred = pred -> right;
		}
		node -> val = pred -> val;
		if(pred_parent -> left == pred) pred_parent -> left = pred -> left;
		else pred_parent -> right = pred -> left;
		return node;
	}

	static void inorder(BSTNode* node, vector<int> &v) {
		if(!node) return;
		inorder(node -> left, v);
		v.push_back(node -> val);
		inorder(node -> right, v);
	}

	static BSTNode* lca(BSTNode* node, BSTNode* p, BSTNode* q) {
		if(!node) return NULL;
		if(node == p || node == q) return node;
		if((node -> val > p -> val && node -> val < q -> val) 
			|| (node -> val > q -> val && node -> val < p -> val)
			) return node;
		if(node -> val > p -> val) return lca(node -> left, p, q);
		return lca(node -> right, p, q);
	}

	static int distance(BSTNode* node, BSTNode* p, BSTNode* q) {
		BSTNode* lcaNode = lca(node, p, q);
		return distance(lcaNode, p) + distance(lcaNode, q);
	}
	static int distance(BSTNode* source, BSTNode* destination) {
		if(!source) return -1;
		if(source == destination) return 0;
		else if(source -> val > destination -> val) {
			int dist = distance(source -> left, destination);
			if(dist == -1) return -1;
			return dist + 1;
		} else {
			int dist = distance(source -> right, destination);
			if(dist == -1) return -1;
			return dist + 1;
		}
		return -1;
	}
	static BSTNode* copy(BSTNode* node) {
		if(!node) return NULL;
		BSTNode* mirrorNode = new BSTNode(node -> val);
		mirrorNode -> left = copy(node -> left);
		mirrorNode -> right = copy(node -> right);
		return mirrorNode;
	}
	static pair<BSTNode*, BSTNode*> bstToDll(BSTNode* node) {
		if(!node) return {NULL, NULL};
		pair<BSTNode*, BSTNode*> left = bstToDll(node -> left);
		pair<BSTNode*, BSTNode*> right = bstToDll(node -> right);
		pair<BSTNode*, BSTNode*> res = {node, node};
		if(left.first) {
			res.first = left.first;
			node -> left = left.second;
			left.second -> right = node;
		}
		if(right.second) {
			res.second = right.second;
			node -> right = right.first;
			right.first -> left = node;
		}
		return res;
	}

};

class Util {


public:

	static int possibleBST(int n) {
		vector<int> dp(n + 1, 0);
		dp[0] = 1;
		dp[1] = 1;
		return helper(n, dp);
	}

	static int helper(int n, vector<int> &dp) {
		if(dp[n] != 0) return dp[n];
		for(int i = 0; i < n; i++) {
			dp[n] += helper(i, dp)*helper(n - 1 - i, dp);
		}
		return dp[n];
	}


};




int main() {


	int q;
	cin >> q;
	BSTNode* root = NULL;
	while(q--) {
		string operation;
		cin >> operation;
		if(operation == "insert") {
			int val;
			cin >> val;
			root = BSTNode::insert(root, val);
		} else if(operation == "delete") {
			int val;
			cin >> val;
			root = BSTNode::remove(root, val);
		} else if(operation == "search") {
			int val;
			cin >> val;
			BSTNode* node = BSTNode::search(root, val);
			cout << (node != NULL) << "\n";
		} else if(operation == "inorder") {
			vector<int> v;
			BSTNode::inorder(root, v);
			for(int i: v) cout << i << " ";
			cout << "\n";
		} else if(operation == "lca") {
			int p, q;
			cin >> p >> q;
			BSTNode* lcaNode = BSTNode::lca(
				root, 
				BSTNode::search(root, p), 
				BSTNode::search(root, q)
			);
			cout << (lcaNode -> val) << "\n";
		} else if(operation == "distance2") {
			int p, q;
			cin >> p >> q;
			int dist = BSTNode::distance(
				root, 
				BSTNode::search(root, p), 
				BSTNode::search(root, q)
			);
			cout << dist << "\n";
		} else if(operation == "possibleBST") {
			int n;
			cin >> n;
			cout << Util::possibleBST(n) << "\n";
		} else if(operation == "bstToDll") {
			BSTNode* mirrorRoot = BSTNode::copy(root);
			pair<BSTNode*, BSTNode*> p = BSTNode::bstToDll(mirrorRoot);
			p.first -> left = p.second;
			p.second -> right = p.first;
			BSTNode* temp = p.first;
			while(temp -> right != p.first) {
				cout << (temp -> val) << " ";
				temp = temp -> right;
			}
			cout << temp -> val << "\n";
		} else if(operation == "stop") {
			cout << "\n";
			break;
		} else {
			cout << "operation = '" << operation << "' is not supported!";
		}
	}
	return 0;
}

