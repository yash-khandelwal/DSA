#include<bits/stdc++.h>
using namespace std;


class DisjointSet {

public:

	vector<int> s;
	int size;

	DisjointSet(int size) {
		this -> s = vector<int>(size, -1);
	}

	int find(int x) {
		if(this -> s[x] < 0) return x;
		return find(s[x]);
	}

	int unionBySize(int x, int y) {
		int rootX = find(x), rootY = find(y);
        if(rootX == rootY) return rootX;
		if(s[rootX] < s[rootY]) {
			int temp = rootX;
			rootX = rootY;
			rootY = temp;
		}
		s[rootY] += s[rootX];
		s[rootX] = rootY;
		return s[rootX];
	}


};


int main() {

	int q;
	cin >> q;
	cout << "\n";
	int n;
	cin >> n;
	cout << "\n";
	DisjointSet *djs = new DisjointSet(n);
	while(q--) {
		string operation;
		cin >> operation;
		if(operation == "find") {
			int x;
			cin >> x;
			int rootX = djs -> find(x);
			cout << "Root of node of " << x << " is " << rootX << "\n";
		} else if(operation == "union") {
			int x, y;
			cin >> x >> y;
			int rootXY = djs -> unionBySize(x, y);
			cout << "Root of node of " << x << " and " << y << " is " << rootXY << "\n";
		} else if(operation == "print") {
			cout << "{ ";
			for(int i = 0; i < n; i++) {
				cout << "( " << i << ", " << djs -> s[i] << "), ";
			}
			cout << "}\n";
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