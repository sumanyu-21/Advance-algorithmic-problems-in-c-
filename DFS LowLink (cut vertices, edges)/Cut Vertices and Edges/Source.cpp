# include <iostream>
# include <stdio.h>
# include <vector>
# include <unordered_map>
# include <algorithm>
using namespace std;


class Edge // We may have self loops and parallel edges. To handle those cases, we are storing edgeList for each vertex.
{
public:
	int j, id;
	Edge(int jj, int ii)
	{
		j = jj;
		id = ii;
	}
};

class Graph
{
	int V, E;
	int cnt;
	public:
		vector < vector<Edge>>edgeList;
		vector<int>preorder, lowlink, bridges; // Prorder array will be used for visited and backedges;
		vector<bool>cutVertices;
		Graph(int V)
		{
			E = 0;
			cnt = 0;
			Graph::V = V;
			edgeList.resize(V);
			for (int i = 0; i < V; i++)
				edgeList[i].reserve(E);
			preorder.resize(V);
			lowlink.resize(V);
			fill(preorder.begin(), preorder.end(),-1);
		}

		void add(int i, int j, bool undirected = 0)
		{
			Edge e(j, E);
			edgeList[i].push_back(e);
			if (undirected)
			{
				Edge e(i, E);
				edgeList[j].push_back(e);
			}
			E++;   // Will be useful for doing visited array on edges.
			bridges.reserve(E);
			cutVertices.resize(V);
			fill(cutVertices.begin(), cutVertices.end(), false);
		}

		// 
		int dfs(int i, int p, int id)
		{
			//cout << i << endl;
			//*** Updating lowlink value if backedge.
			if (preorder[i] != -1) // We are visiting the same node again, this means this is a BackEdge
			{
				lowlink[p] = min(lowlink[p], preorder[i]);
				return lowlink[p];  // This returned value will help us to classify cut vertices and edges.
			}

			preorder[i] = cnt;
			cnt++;
			lowlink[i] = preorder[i];
			bool hasfwd = false;
			for (Edge e : edgeList[i])
			{
				if (e.id == id) // This will prevent us to move back to the node from which we came from via the same edge,
					continue;	// If there are parallel edges, this condition would not be satisfied and we will visit parent node again via 
								// parallel edge.

				//*****Updating lowlink value if forward edge.
				if (dfs(e.j, i, e.id) < 0)  // Tells me that this us a forward edge.
				{
					lowlink[i] = min(lowlink[i], lowlink[e.j]);
					// Bridge;
					if (lowlink[e.j] == preorder[e.j])
						bridges.push_back(e.id);


					// Finding cut Vertices
					//Case 1 (We are not at root node)
					if (i != p ? lowlink[e.j] >= preorder[i] : hasfwd)// If hasfwd is True, This would mean this is the second child of the root node
					{												  // Which would mean root node is a cut vertex;

						cutVertices[i] = true; // This code will be fired many times. When we go to biconnected
											   // compomemts, this would be useful.
						//cout << i << p << " " << hasfwd << endl;
					}
				}

				
				hasfwd = true;
			}
			//cout << i << endl;
			return -1;
		}

};

int main()
{
	int V, E;
	cin >> V >> E;
	Graph g(V);
	for (int i = 0; i < E; i++)
	{
		int x, y;
		cin >> x >> y;
		g.add(x-1, y-1, 1);
	}

	for (int i = 0; i < V; i++)
	{
		if (g.preorder[i] == -1)
			g.dfs(i, i, -1);
	}

	cout << "Bridges are" << endl;
	for (int i = 0; i < g.bridges.size(); i++)
		cout << g.bridges[i] << " ";
	cout << "Articulation Points are" << endl;
	for (int i = 0; i < V; i++)
	{
		if (g.cutVertices[i] == true)
			cout << i << " ";
	}

}