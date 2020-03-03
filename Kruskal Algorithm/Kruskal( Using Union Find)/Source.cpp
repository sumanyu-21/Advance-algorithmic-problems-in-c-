# include <iostream>
# include <stdio.h>
# include <vector>
# include <unordered_map>
# include<math.h>
# include<algorithm>
using namespace std;

class DisjointSet
{
	int n;
	vector<int>parent;
	vector<int>rank;
	
	public:

		DisjointSet(int n)
		{
			DisjointSet::n = n;
			parent.resize(n);
			rank.resize(n);
		}

		void make_set(int v)
		{
			parent[v] = v;
			rank[v] = 0;
		}

		int find_set(int v)
		{
			int x = v;
			while (parent[x] != x)
				x = parent[x];

			parent[v] = x;
			return x;
		}

		void union_sets(int u, int v)
		{
			u = find_set(u);
			v = find_set(v);
			if (u == v)
				return;

			if (rank[u] < rank[v])
				swap(u, v);
			
			parent[v] = u;
			if (rank[u] == rank[v])
				rank[u]++;
		}
	
};

struct Edge {
	
	int u, v, weight;
	bool operator<(Edge const& other) {
		return weight < other.weight;
	}
};

int main()
{
	int n;
	cin >>n;
	vector<Edge> edges;
	vector<Edge>MST;
	int cost = 0;

	DisjointSet ds(n);

	for (int i = 0; i < n; i++)
		ds.make_set(i);

	sort(edges.begin(), edges.end());
	for (Edge e : edges)
	{
		if (ds.find_set(e.u) != ds.find_set(e.v)) // If they dont belong tho the same set, make them belong to same set.
		{
			cost += e.weight;// Storing the cost for minimum spanning tree.
			MST.push_back(e);
			ds.union_sets(e.u, e.v);
		}

	}

}

