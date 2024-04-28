#include<bits/stdc++.h>
using namespace std;

void insertion_sort(vector<int> &v) {
	int n = v.size();
	for(int i = 0; i < n; i++) {
		int elem = v[i];
		int j = i;
		while(j > 0 && v[j - 1] > elem) {
			v[j] = v[j - 1];
			j--;
		}
		v[j] = elem;
	}
}

int main() {

	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
	}
	insertion_sort(v);
	for(int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	return 0;
}

