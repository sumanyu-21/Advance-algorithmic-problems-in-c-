# include <iostream>
# include <stdio.h>
# include <unordered_map>
# include <vector>
# include <algorithm> // For sort
using namespace std;
# define ll long long int

vector<ll> arr;
class INV_BIT
{
	ll n;
	vector<ll>BIT;
	
	public:
		unordered_map<ll, ll> mapping;
		INV_BIT(ll n)
		{
			INV_BIT::n = n;
			BIT.resize(n+1, 0);
		}
		void create_mapping()
		{
			vector<ll>a = arr;
			std::sort(a.begin()+1,a.end());
//			for (ll i = 1; i < n+1; i++)
//				cout << a[i] << " ";
//			cout << endl;
			for (ll i = 1; i < n+1; i++)
			{
				if (mapping.find(a[i]) == mapping.end())
					mapping[a[i]] = i;
			}

//			for (ll i = 1; i < n+1; i++)
//				cout << mapping[a[i]] << " ";
//			cout << endl;
		}
		void print_BIT()
		{
			for (ll i = 1; i < n+1; i++)
				cout << BIT[i] << " ";
			cout << endl;
		}
		void updateBit(ll k)
		{
			
			while (k < n+1)
			{
				
				BIT[k] += 1;
				//cout << k << " " <<BIT[k]<< endl;
				k += k & (-k);
			}
			//cout <<" -------- "<< endl;
		}

		ll Query(ll k)
		{
			ll sum = 0;
			while (k > 0)
			{
				//cout << k <<" "<<BIT[k]<<endl;
				sum += BIT[k];
				k -= k & (-k);
			}
			return sum;
		}

		ll count_inversions(ll i, ll j )
		{
			//cout << j << " " << endl;
			//if (j < n)
				return Query(i) - Query(j);
			//else
				//return 0;
		}

};

int main()
{
	ll n;
	cin >> n;
	arr.resize(n+1);
	for (ll i = 1; i < n+1; i++)
		cin >> arr[i];
	ll inversions = 0;
	INV_BIT ob(n);
	ob.create_mapping();
	for (ll i = 1; i < n+1; i++)
	{
		//cout <<"hey"<<ob.mapping[arr[i]] << endl;
		ob.updateBit(ob.mapping[arr[i]]);
		inversions += ob.count_inversions(n, ob.mapping[arr[i]]);
	}

	cout << inversions << endl;
		

}
