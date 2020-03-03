# include <iostream>
# include <stdio.h>
# include <unordered_map>
# include <vector>
using namespace std;


class DisjointSet 
{
	int n;
	vector<int>rank;
	vector<int>parent;
	vector<int>size;

	public:

		// Create set with only one element
		DisjointSet(int n)
		{
			DisjointSet::n = n;
			rank.resize(n);
			parent.resize(n);
			size.resize(n);
		}

		void makeSet(int v)
		{
			parent[v] = v;
			rank[v] = 0;
			size[v] = 1;

		}

		int findSet(int v)
		{
			int x = v;
			while (parent[x] != x)
				x = parent[x];

			//Path Compression
			parent[v] = x;
			return x;
		}
		void union_sets(int u,int v)
		{
			u = findSet(u);
			v = findSet(v);
			if (u == v)
				return;

			// Make u always the bigger rank node;
			if (rank[u] < rank[v])
				swap(u, v);

			parent[v] = u;
			if (rank[u] == rank[v])
				rank[u]++;
		}

		void union_sets_size(int u, int v)
		{
			u = findSet(u);
			v = findSet(v);
			if (u == v)
				return;

			if (size[u] < size[v])
				swap(u, v);

			parent[v] = u;
			size[u] += size[v];
		}


};

int main()
{
	int n;
	cin >> n;
	DisjointSet ds(n+1);
	for (int i = 1; i <=n; i++)
		ds.makeSet(i);

	//cout << ds.findSet(5)<< endl;
	ds.union_sets(1, 2);
	ds.union_sets(2, 3);
	ds.union_sets(4, 5);
	ds.union_sets(6, 7);
	ds.union_sets(5, 6);
	ds.union_sets(3, 7);

	cout << ds.findSet(1) << endl;
	cout << ds.findSet(2) << endl;
	cout << ds.findSet(3) << endl;
	cout << ds.findSet(4) << endl;
	cout << ds.findSet(5) << endl;
	cout << ds.findSet(6) << endl;
	cout << ds.findSet(7) << endl;


	
}