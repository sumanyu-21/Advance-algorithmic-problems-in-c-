# include <iostream>
# include <stdio.h>
# include <vector>
using namespace std;


class BIT
{
	int n;
	vector<int>fenwick;

	public:
		BIT(int n)
		{
			BIT::n = n;
			fenwick.resize(n);
		}

		void update(int i, int delta)
		{
			while (i < n)
			{
				fenwick[i] += delta;
				i += (i & (-i)); //Going up the tree;
			}
		}
		// Compute the prefix sum value[l, i];
		int sum(int i)
		{
			int sum = 0;
			while (i > 0)
			{
				sum+= fenwick[i];
				i -= (i & -i); // Going down the tree.

			}
			return sum;

		}

		int rangeSum(int i, int j)
		{
			return sum(j) - sum(i);
		}


};
int main()
{

}