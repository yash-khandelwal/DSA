#include<bits/stdc++.h>
using namespace std;

void merge_sort(vector<int> &v) {
	int n = v.size(), i = 0, j = 0, k = 0;
	if(n <= 1) return;
	vector<int> v1, v2;
	while(i < n / 2) {
		v1.push_back(v[i]);
		i++;
	}
	while(i < n) {
		v2.push_back(v[i]);
		i++;
	}
	merge_sort(v1);
	merge_sort(v2);
	i = 0;
	while(i < v1.size() && j < v2.size()) {
		if(v1[i] <= v2[j]) {
			v[k] = v1[i];
			i++;
		} else {
			v[k] = v2[j];
			j++;
		}
		k++;
	}
	while(i < v1.size()) {
		v[k] = v1[i];
		i++;
		k++;
	}
	while(j < v2.size()) {
		v[k] = v2[j];
		j++;
		k++;
	}
}

int main() {

	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
	}
	merge_sort(v);
	for(int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	return 0;
}

