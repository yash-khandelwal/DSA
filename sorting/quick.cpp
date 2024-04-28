#include<bits/stdc++.h>
using namespace std;

void quick_sort(vector<int> &v, int l = 0, int r = -1) {
	if(r == -1) r = v.size();
	if(r - l <= 1) return;
	int pivot = v[l];
	int left = l, right = r - 1;
	while(left <= right) {
		while(left < r && v[left] <= pivot) left++;
		while(right > l && v[right] > pivot) right--;
		if(left < right) {
			int temp = v[left];
			v[left] = v[right];
			v[right] = temp;
		}
	}
	v[l] = v[right];
	v[right] = pivot;
	quick_sort(v, l, right);
	quick_sort(v, left, r);
}

int main() {

	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
	}
	quick_sort(v);
	for(int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	return 0;
}

