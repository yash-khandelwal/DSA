#include<bits/stdc++.h>
using namespace std;

void shell_sort(vector<int> &v) {
	int n = v.size();
	for(int gap = n / 2; gap > 0; gap /= 2) {
		for(int i = gap; i < n; i++) {
			int temp = v[i], j = i;
			while(j >= gap && v[j - gap] > temp) {
				v[j] = v[j - gap];
				j -= gap;
			}
			v[j] = temp;
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
	shell_sort(v);
	for(int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	return 0;
}

