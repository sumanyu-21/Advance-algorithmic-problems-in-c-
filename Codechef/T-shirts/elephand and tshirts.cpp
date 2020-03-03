# include <bits/stdc++.h>
# include <iostream>
# include <stdio.h>
using namespace std;
# define ll long long int

vector<vector<int>> person_map(10,vector<int>(100,0));
vector<vector<int>> tshirt_map(100,vector<int>(0,0));

int dp[1025][100];
int max_tshirt=0;
int persons;

ll calculate(int current_state, int tshirt_id )
{
    cout<<current_state<<endl;
	ll ans=0;
	// We are moving from curent state to next state.

	if(current_state == 1<<(persons)-1)
	{
		// We have assigned tshirts to every person.
        dp[current_state][tshirt_id]=1;
		return 1;
	}
	if(tshirt_id> max_tshirt)
	{
		return 0;
	}
    if(dp[current_state][tshirt_id]!=-1)
        return dp[current_state][tshirt_id];

	ans+= calculate(current_state,tshirt_id+1); // Do not assign this tshirt to anyone

	 vector<int>::iterator itr;
	for(itr=tshirt_map[tshirt_id].begin();itr<tshirt_map[tshirt_id].end();itr++)
	{
		if( (1<<(*itr) & current_state)!=0)  //If this person has not been assigned the tshirt
			continue;        			  // That is the bit is not set to 1;
		int next_state=current_state | (1<<(*itr)); // Set bit equal to 1 and assign tshirt to this person.
		ans+=calculate(next_state,tshirt_id+1);
	}
    dp[current_state][tshirt_id]=ans;
	return ans;
}

int main()
{

    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n;
        cin>>n;
        persons=n;
        
        string s;
        cin.get();
        for(int i=0;i<n;i++)
        {
            getline(cin,s);
        }
        ll ans=calculate(0,0);
        printf("%ll\n",ans);



    }
}

/*# include <stdio.h>
# include <iostream>
# include <string>
using namespace std;
int main(void)
{
    string sc="hell0";
    sc.append("a");
    cout<<sc<<endl;
    std::string s;
    cin>>s;
    std::string current_int;
    int tshirt_id=-1;
    for(int index=0;index<s.length();index++)
    {

        if(s[index]==' ')
        {
            tshirt_id=stoi(current_int);
            current_int.clear();
        }
        else
        {
            if(current_int.empty())
                current_int=s[index];
            else
                current_int.append(s[index]);
        }

        cout<<tshirt_id<<endl;
    }
}
*/
