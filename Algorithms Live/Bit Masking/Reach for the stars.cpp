# include <bits/stdc++.h>
# include <iostream>
# include <stdio.h>
using namespace std;

//int dp[9*9][(1<<18)];
bool marked[9][9];
bool can_mark[9][9];   // Default value for boolean is false for global variables.

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
	    vector<vector<int>> dp(10*10,vector<int>((1<<18),INT_MAX));
		int R,C;
		cin>>R>>C;
		for(int i=0;i<R;i++)
		{
			string s;
			cin>>s;
			for(int j=0;j<s.length();j++)
			{
				if(s[j]=='#')
					marked[i][j]=1;
				else
					marked[i][j]=0;
			}
		}

		for(int i=1;i<R-1;i++)
		{
			for(int j=1;j<C-1;j++)
			{
				can_mark[i-1][j]=marked[i-1][j] && marked[i][j] && marked[i+1][j] && marked[i][j-1] && marked[i][j+1];
			}
		}

		int stamp= 1 | (1<<(C-1)) | (1<<C) | (1<<(C+1)) | (1<<(2*C));



		dp[0][0]=0;

		int curr_cell=-1;
		for(int i=0;i<R;i++)
		{
			for(int j=0;j<C;j++)
			{
				curr_cell++;
				int next_cell=curr_cell+1;

				for(int curr_mask=0; curr_mask<=((1<<(2*C))-1);curr_mask++)
				{

					if(dp[curr_cell][curr_mask]<INT_MAX)
					{ // Doing this if condition will take care of the case when we are in  the first row
					  // and we haven't seen a configuration infront of us yet.

						// We choose to mark the current cell
						// We can mark only when it is possible to mark this cell.
						if(can_mark[i][j])
						{
							int nxt_mask = (curr_mask | stamp)>>1; // chamge the state;
							dp[next_cell][nxt_mask] = min(dp[next_cell][nxt_mask], 1+dp[curr_cell][curr_mask]);

						}

						// We can choose not to mark the current cell.

						if(!marked[i][j] || ((curr_mask & 1)>0))
						{
							int nxt_mask = (curr_mask>>1); // We just need to discard the current bit.

							dp[next_cell][nxt_mask]=min(dp[next_cell][nxt_mask],dp[curr_cell][curr_mask]);
						}
					}
				}
			}
		}
        //cout<<can_mark[0][0]<<endl;
		if(dp[R*C][0] <INT_MAX)
			cout<<dp[R*C][0]<<endl;
		else
			cout<<"Impossible"<<endl;
	}
}
