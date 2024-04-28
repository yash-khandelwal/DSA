#include<bits/stdc++.h>
using namespace std;

void selection_sort(vector<int> &v) {
    int n = v.size(), temp;
    for(int i = 0; i < n; i++) {
        int mini = i;
        for(int j = i + 1; j < n; j++) {
            if(v[mini] > v[j]) mini = j;
        }
        temp = v[mini];
        v[mini] = v[i];
        v[i] = temp;
    }
}


int main() {

	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
	}
	selection_sort(v);
	for(int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	return 0;
}

