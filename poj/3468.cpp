/*
 * sを加算前の累積和、s'を加算後の累積和とすると
 * i < l s'[i] = s[i]
 * l <= i <= r s'[i] = s[i] + x*i - x*(l-1)
 * r < i s'[i] = s[i] + x*(r-l+1)
 * これをBITを二つ用いて実装
 * 詳細は蟻本
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <bitset>
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

//BIT
struct BIT{
	int N;
	ll data[200100];
	void init(int n){
		N = n;
	}
void add(int a,ll w){
	for(int x = a;x <= N;x += x & -x) data[x] +=w;
}
//bit[1] + ... + bit[a]
ll sum(int a){
	ll ret = 0;
	for(int x = a; x > 0; x -= x & -x) ret+= data[x];
	return ret;
}
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
	int n,q;
	cin >> n >> q;
	BIT bit0,bit1;
	bit0.init(n+1);
	bit1.init(n+1);
	REP(i,n){
		int a;cin >> a;
		bit1.add(i+1,a);
	}
	REP(i,q){
		char c;cin >> c;
		int l,r;cin >> l >> r;
		if(c == 'C'){
			int x;cin >> x;
			bit0.add(l,x);
			bit0.add(r+1,-x);
			bit1.add(l,-(l-1)*x);
			bit1.add(r+1,r*x);
		}else{
			//			cout << "r,l" << r << ' ' << l << endl;
			cout << bit0.sum(r)*r + bit1.sum(r) - (bit0.sum(l-1)*(l-1) + bit1.sum(l-1)) << endl;
		}
	}
  return 0;
}
