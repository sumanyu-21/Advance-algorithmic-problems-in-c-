# include <iostream>
# include <stdio.h>
# include <queue>
# include <list>
# include <vector>
# include <unordered_map>
# include <cstring>
# include <typeinfo>
using namespace std;


class Graph
{
		int V, D;
		vector<list<pair<int,int>>> adjList;
		vector<int>depth;
		vector<vector<int>> sparseTable;

	public:
		Graph(int V)
		{
			Graph::V = V;
			adjList.resize(V);
			depth.resize(V);

			sparseTable.resize(V);
			D = (int)log2(V) + 1;
			for (int i = 0; i < V; i++)
			{
				sparseTable[i].resize(D+1);
				fill(sparseTable[i].begin(), sparseTable[i].end(), -1);
			}

		}

		void addEdge(int u, int v, int cost)
		{
			pair<int, int> p;
			p.first = v;
			p.second = cost;
			adjList[u].push_back(p);
			p.first = u;
			adjList[v].push_back(p);
		}

		void prindAdjList()
		{
			int i = 0;
			for (auto node : adjList)
			{
				list < pair<int, int>>::iterator itr;
				cout << i << " : ";
				for (itr = node.begin(); itr != node.end(); itr++)
					cout << itr->first << " " << itr->second << endl;
				cout << endl;
				i++;
			}
		}

		void printSparseTable()
		{
			for (int i = 0; i < V; i++)
			{
				cout << i << " : ";
				for (int d = 0; d <=D; d++)
					cout << sparseTable[i][d] << " ";
				cout << endl;
			}
		}

		void bfs(int src)
		{
			depth[src] = 0;
			queue<int>q;
			vector<bool>visited(V,false);
			
			visited[src] = true;
			q.push(src);

			while (!q.empty())
			{
				int node = q.front();
				q.pop();
				for (auto x : adjList[node])
				{
					pair<int, int>p;
					if (!visited[x.first])
					{
						depth[x.first] = depth[node] + 1;
						sparseTable[x.first][0] = node;  // reach parent when jump size is  2^0;
						visited[x.first] = true;
						q.push(x.first);
					}
				}
			}
		}


		void constructBinaryLifting()
		{
			for (int d = 1; d <= D; d++)
			{
				for (int i = 0; i < V; i++)
				{
					int mid = sparseTable[i][d - 1];
					if(mid!=-1) // If we dont jump out of the table
						sparseTable[i][d] = sparseTable[mid][d - 1];
				}
			}
		}

		int walk(int i, int k)
		{
			for (int d = 0; d <= D; d++)  // Traverse all bits of k
			{
				// If dth bit is set;
				if (((1 << d) & k) > 0)
					i = sparseTable[i][d];
			}

			return i;
		}

		int LCA(int i, int j)
		{
			if (depth[i] > depth[j])
				i = walk(i, depth[i]-depth[j]);   
			if (depth[j] > depth[i])
				j = walk(j, depth[j]-depth[i]);

			if (i == j)
				return i;

			for (int d = D; d >= 0; d--)
			{
				// Make largest jump first
				if (sparseTable[i][d] != sparseTable[j][d])
				{
					i = sparseTable[i][d];
					j = sparseTable[j][d];
				}
			}

			// Now we are just short of LCA;
			return sparseTable[i][0];
		}

		int dist(int i, int j)
		{
			return (depth[i] + depth[j] - 2 * depth[LCA(i, j)]);
		}

};
int main()
{
	int V;
	cin >> V;
	Graph ob(V);
	for (int i = 1; i < V; i++)
	{
		int u, v;
		cin >> u >> v;
		ob.addEdge(u-1, v-1, 1);
	}
	//ob.prindAdjList();
	ob.bfs(0);
	ob.constructBinaryLifting();
	//ob.printSparseTable();
	long int result = 0;
	for (int i = 1; i <= V; i++)
	{
		for (int j = 2; j * i <= V; j++)
			result += ob.dist(i - 1, i * j - 1)+1;
	}
	cout << result << endl;

}
