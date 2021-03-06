#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <bitset>
#include <climits>
#define REP(i,n) for (int i=0;i<(n);i++)
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define RREP(i,n) for (int i=(n)-1;i>=0;i--)
#define RFOR(i,a,b) for (int i=(a)-1;i>=(b);i--)
#define ll long long
#define ull unsigned long long
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
const int INF = 1e9;
const int MOD = 1e9 + 7;

using namespace std;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
	int n;
	cin>>n;
	vector<int> a(n);
	REP(i,n)cin>>a[i];
	vector<int> mp(n,INF);
	queue<pair<int,int> > que;
	que.push(make_pair(0,0));
	while(!que.empty()){
		int x = que.front().first;
		int t = que.front().second;
		que.pop();
		if(a[x] !=0){
			if(t < mp[x + a[x]]){
				mp[x + a[x] ] = t;
				que.push(make_pair(x+a[x],t));
			}
		}else{
			for(int i = 6;i>0;i--){
				if(x+i <n && t+1 < mp[x + i]){
					mp[x+i] = t+1;
					que.push(make_pair(x+i,t+1));
				}
			}
		}
	}
	cout << mp[n-1] << endl;
  return 0;
}
