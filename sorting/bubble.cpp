#include<bits/stdc++.h>
using namespace std;

void bubble_sort(vector<int> &v) {
	int n = v.size(), temp;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n - i - 1; j++) {
			if(v[j] > v[j + 1]) {
				temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
}

int main() {

	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
	}
	bubble_sort(v);
	for(int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	return 0;
}

