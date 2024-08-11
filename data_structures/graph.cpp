#include<bits/stdc++.h>
using namespace std;

class MinHeapComparator { 
public: 
    int operator() (const pair<int, int>& p1, const pair<int, int>& p2) { 
        return p1.first < p2.first; 
    } 
};

class MinHeapComparatorPrims { 
public: 
    int operator() (const pair<int, pair<int, int>>& p1, const pair<int, pair<int, int>>& p2) { 
        return p1.second.second < p2.second.second; 
    } 
};

class Graph {

public:

	int v;
	vector<pair<int, pair<int, int>>> e;
	vector<vector<pair<int, int>>> adj;

	Graph(int v) {
		this -> v = v;
		this -> prepareAdj();
	}

	Graph(int v, vector<pair<int, pair<int, int>>> e) {
		this -> v = v;
		this -> e = e;
		this -> prepareAdj();
	}

	void prepareAdj() {
		this -> adj.resize(v);
		for(pair<int, pair<int, int>> edge: this -> e) {
			this -> adj[edge.first].push_back(edge.second);
		}
	}

	void addEdge(pair<int, pair<int, int>> edge) {
		this -> e.push_back(edge);
		this -> adj[edge.first].push_back(edge.second);
	}

	void printEdges() {
		cout << "Edges: \n";
		for(pair<int, pair<int, int>> edge: this -> e) {
			cout << edge.first << " --(" << edge.second.second << ")--> " << edge.second.first << "\n";
		}
		cout << "\n";
	}

	void printAdj() {
		cout << "Adjecency List: \n";
		for(int i = 0; i < this -> v; i++) {
			cout << i << " -> ";
			for(pair<int, int> d: this -> adj[i]) {
				cout << "( " << d.first << ", " << d.second << "), ";
			}
			cout << "\n";
		}
		cout << "\n";
	}

	/*
	
	ALGORITHMS

		1 Traversals
			1.1 DFS
			1.2 BFS
			1.3 Topological 
		2 Shortest Path
			2.1 Shortest Path in unweighted graph 
				2.1.1 BFS
			2.2 Shortest Path in weighted graph
				2.2.1 Dijkstra Algorithm
			2.3 Shortest Path in weighted graph with negative edges
				2.3.1 Bellman Ford Algorithm
		3 Minimum Spanning Tree
			3.1 Prim's Algorithm
			3.2 Kruskal Algorithm

	*/

	void dfs(int node, vector<bool> &visited, vector<int> &path) {
		visited[node] = true;
		path.push_back(node);
		for(pair<int, int> next: this -> adj[node]) {
			if(!visited[next.first]) {
				dfs(next.first, visited, path);
			}
		}
	}

	void bfs(int root, vector<bool> &visited, vector<int> &path) {
		queue<int> q;
		q.push(root);
		visited[root] = true;
		while(!q.empty()) {
			int node = q.front();
			q.pop();
			path.push_back(node);
			for(pair<int, int> next: this -> adj[node]) {
				if(!visited[next.first]) {
					visited[next.first] = true;
					q.push(next.first);
				}
			}
		}
	}

	void topologicalSort(vector<int> &path) {
		vector<int> indeg(this -> v, 0);
		for(pair<int, pair<int, int>> edge: this -> e) {
			indeg[edge.second.first]++;
		}
		queue<int> q;
		for(int i = 0; i < this -> v; i++) {
			if(indeg[i] == 0) q.push(i);
		}
		while(!q.empty()) {
			int node = q.front();
			path.push_back(node);
			q.pop();
			for(pair<int, int> next: adj[node]) {
				indeg[next.first];
				if( --indeg[next.first] == 0) {
					q.push(next.first);
				}
			}
		}
	}

	void bfs(int root, vector<vector<int>> &paths) {
		vector<int> parents(this -> v);
		vector<bool> visited(this -> v, false);
		queue<int> q;
		q.push(root);
		paths[root].push_back(root);
		visited[root] = true;
		while(!q.empty()) {
			int node = q.front();
			q.pop();
			for(pair<int, int> next: adj[node]) {
				if(!visited[next.first]) {
					parents[next.first] = node;
					visited[next.first] = true;
					vector<int> path = paths[node];
					path.push_back(next.first);
					paths[next.first] = path;
					q.push(next.first);
				}
			}
		}
	}

	void dijkstra(int root, vector<vector<int>> &paths) {
		vector<int> dist(this -> v, INT_MAX);
		vector<bool> visited(this -> v, false);
		priority_queue<pair<int, int>, vector<pair<int, int>>, MinHeapComparator> pq;
		pq.push({0, root});
		visited[root] = true;
		paths[root].push_back(root);
		while(!pq.empty()) {
			pair<int, int> node = pq.top();
			pq.pop();
			for(pair<int, int> next: adj[node.second]) {
				if(!visited[next.first]) {
					if(dist[next.first] > dist[node.second] + next.second) {
						dist[next.first] = dist[node.second] + next.second;
						vector<int> path = paths[node.second];
						path.push_back(next.first);
						paths[next.first] = path;
					}
					pq.push({next.second, next.first});
				}
			}
		}
	}

	void bellmanFord(int root, vector<vector<int>> &paths) {
		vector<int> dist(this -> v, -1);
		vector<bool> visited(this -> v, false), inQueue(this -> v, false);
		queue<pair<int, int>> q;
		q.push({0, root});
		dist[root] = 0;
		inQueue[root] = true;
		visited[root] = true;
		paths[root].push_back(root);
		while(!q.empty()) {
			pair<int, int> node = q.front();
			q.pop();
			inQueue[node.second] = false;
			for(pair<int, int> next: adj[node.second]) {	
				if(dist[next.second] == -1 || dist[next.first] > dist[node.second] + next.second) {
					dist[next.first] = dist[node.second] + next.second;
					vector<int> path = paths[node.second];
					path.push_back(next.first);
					paths[next.first] = path;
					if(!inQueue[next.first]) {
						q.push({next.second, next.first});
						inQueue[next.first] = true;
					}
				}
			}
		}
	}

	vector<pair<int, int>> prims() {
		vector<pair<int, int>> stree;
		priority_queue<int> pq;
		vector<int> dist(this -> v, -1);
		pq.push(0);
		dist[0] = 0;
		vector<int> parents(this -> v, 0);
		parents[0] = -1;
		while(!pq.empty()) {
			int node = pq.top();
			for(pair<int, int> next: adj[node]) {
				int d = dist[node] + next.second;
				if(dist[next.first] == -1 || dist[next.first] > d) {
					dist[next.first] = d;

				}
			}
		}

	}

};



int main() {


	int q;
	cin >> q;
	cout << "\n";
	Graph *graph = new Graph(10);
	while(q--) {
		string operation;
		cin >> operation;
		if(operation == "graph") {
			int v;
			cin >> v;
			graph = new Graph(v);
		} else if(operation == "addEdge") {
			int u, v, w;
			cin >> u >> v >> w;
			pair<int, pair<int, int>> edge{u, {v, w}};
			graph -> addEdge(edge);
		} else if(operation == "printEdges") {
			graph -> printEdges();
		} else if(operation == "printAdj") {
			graph -> printAdj();
		} else if(operation == "dfs") {
			vector<bool> visited(graph -> v, false);
			for(int i = 0; i < graph -> v; i++) {
				if(!visited[i]) {
					vector<int> path;
					graph -> dfs(i, visited, path);
					cout << "DFS path for root = " << i << "\n";
					for(int node: path) {
						cout << node << ", ";
					}
					cout << "\n";
				}
			}
		} else if(operation == "bfs") {
			vector<bool> visited(graph -> v, false);
			for(int i = 0; i < graph -> v; i++) {
				if(!visited[i]) {
					vector<int> path;
					graph -> bfs(i, visited, path);
					cout << "BFS path for root = " << i << "\n";
					for(int node: path) {
						cout << node << ", ";
					}
					cout << "\n";
				}
			}
		} else if(operation == "topo") {
			vector<int> path;
			graph -> topologicalSort(path);
			cout << "Topological path\n";
			for(int node: path) {
				cout << node << ", ";
			}
			cout << "\n";
		} else if(operation == "spuw") {
			int root;
			cin >> root;
			vector<vector<int>> paths(graph -> v);
			graph -> bfs(root, paths);
			cout << "Shortest paths for unweighted graph from root " << root << "\n";
			for(int i = 0; i < graph -> v; i++) {
				cout << "for destination " << i << ": ";
				if(i == root) cout << "ROOT";
				else if(paths[i].size() == 0) cout << "No Path";
				else {
					for(int node: paths[i]) {
						cout << node << ", ";
					}
				}
				cout << "\n";
			}
			cout << "\n";
		} else if(operation == "dijkstra") {
			int root;
			cin >> root;
			vector<vector<int>> paths(graph -> v);
			graph -> dijkstra(root, paths);
			cout << "Shortest paths for weighted graph from root " << root << "\n";
			for(int i = 0; i < graph -> v; i++) {
				cout << "for destination " << i << ": ";
				if(i == root) cout << "ROOT";
				else if(paths[i].size() == 0) cout << "No Path";
				else {
					for(int node: paths[i]) {
						cout << node << ", ";
					}
				}
				cout << "\n";
			}
			cout << "\n";
		} else if(operation == "bellmanFord") {
			int root;
			cin >> root;
			vector<vector<int>> paths(graph -> v);
			graph -> bellmanFord(root, paths);
			cout << "Shortest paths for weighted graph with negative edges from root " << root << "\n";
			for(int i = 0; i < graph -> v; i++) {
				cout << "for destination " << i << ": ";
				if(i == root) cout << "ROOT";
				else if(paths[i].size() == 0) cout << "No Path";
				else {
					for(int node: paths[i]) {
						cout << node << ", ";
					}
				}
				cout << "\n";
			}
			cout << "\n";
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