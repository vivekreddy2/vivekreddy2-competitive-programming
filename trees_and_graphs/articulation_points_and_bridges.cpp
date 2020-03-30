#include <bits/stdc++.h>
#define fr(i, a, n) for (i = a; i <= n; i++)
#define rf(i, n, a) for (i = n; i >= a; i--)
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define mp make_pair
#define pb push_back
#define pp(a, b) pb(mp(a, b))
#define fi first
#define se second
#define ll long long
#define ld long double
#define mem(a, b) memset(a, b, sizeof(a))
#define cl(a) mem(a, 0)
#define all(x) x.begin(), x.end()
#define vi vector<int>
#define wi(x) cerr << #x << " is " << x << endl;
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
#ifndef ONLINE_JUDGE
bool ipfile = freopen("ip.txt", "r", stdin);
bool opfile = freopen("op.txt", "w", stdout);
#endif
using namespace std;

class Graph{
    public:
    vector<vector<int>> g;
    vector<bool> visited;
    vector<int> tin;
    vector<int> low;
    vector<bool> is_articulation_point;
    vector<int> articulation_points;
    vector<pair<int, int>> bridges;

    int n;
    int timer;

    Graph(int n){
        this->n = n;
        g.resize(n+1);
        visited.assign(n, 0);
        tin.resize(n);
        low.resize(n);
        is_articulation_point.assign(n, 0);
    }

    void add_edge(int u, int v){
        g[u].pb(v);
        g[v].pb(u);
    }

    void add_bridge(int u, int v){
        if(u > v) swap(u, v);
        bridges.pb({u,v});
    }

    void dfs(int cur, int par){
        visited[cur] = 1;
        tin[cur] = low[cur] = timer++;
        int cnt = 0;
        for(int child: g[cur]){
            if(child == par) continue;
            if(visited[child]){
                low[cur] = min(low[cur], tin[child]);
                continue;
            }
            
            dfs(child, cur);
            low[cur] = min(low[cur], low[child]);
            if(par == -1) { cnt++;}
            if(low[child] >= tin[cur]){
                
                if(par != -1)is_articulation_point[cur] =1;
                if(low[child] > tin[cur])
                    add_bridge(cur, child);
            }
        }
        if(par == -1 and cnt > 1){ is_articulation_point[cur] = 1;}
    }

    void find_art_bridges(){
        timer = 0;
        bridges.clear();
        is_articulation_point.assign(n, 0);
        articulation_points.clear();
        dfs(0, -1);
        sort(all(bridges));
        for(int i = 0; i < n; i++)
            if(is_articulation_point[i])
                articulation_points.push_back(i);
    }
};

void each_case(int t)
{
    int n, m;
    cin >> n >> m;
    int a, b;
    Graph G(n);
    while(m--){
        cin >> a >> b;
        G.add_edge(a, b);
    }
    // cout << " s" << endl;
    G.find_art_bridges();
    cout << G.articulation_points.size() << endl;
    for(int p: G.articulation_points){
        cout << p << " ";
    }
    cout << endl;

    cout << G.bridges.size() << endl;
    for(auto p: G.bridges){
        cout << p.fi << " " << p.se << endl;
    }
    

}


int main()
{
	
    fastio
    int t = 1, i;
    // cin >> t;
    fr(i, 1, t) each_case(i);
    return 0;
}
