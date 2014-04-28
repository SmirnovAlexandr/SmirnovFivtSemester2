#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <cstdio>
class Graph{
    std::vector<std::vector<int> > matrix;
    std::vector<std::vector<int> > tmatrix;
    std::vector<int> visited;
    std::vector<int> orderdfs2;
    std::vector<int> color;
    int n,m;
    
    void dfs1(int v){
        visited[v] = 1;
        for (int i = 0; i < matrix[v].size(); i++)
            if (visited[matrix[v][i]] == 0) dfs1(matrix[v][i]);
        orderdfs2.push_back(v);
    }
    void dfs2(int v, int vcolor){
        visited[v] = 1;
        color[v] = vcolor;
        for (int i = 0; i < tmatrix[v].size();i++)
            if (visited[tmatrix[v][i]] == 0) dfs2(tmatrix[v][i], vcolor);
    }
    void solve(){
        for (int i = 1; i <= n; i++)
            if (visited[i] == 0) dfs1(i);
        visited.assign(n + 1, 0);
        int vcolor = 0;
        for (int i = orderdfs2.size() - 1; i >= 0; i--)
            if (visited[orderdfs2[i]] == 0) {
                vcolor++;
                dfs2(orderdfs2[i], vcolor);
            }
    }

public:
    Graph (int n, int m):n(n),
    m(m),
    matrix(n + 1,std::vector<int> (0)),
    tmatrix(n + 1, std::vector<int> (0)),
    visited(n + 1, 0),
    color(n + 1, 0)
    {}
    
    void readgraph(){
        for(int i = 0; i < m; i++)
        {
            int a,b;
            std::cin >> a >> b;
            matrix[a].push_back(b);
            tmatrix[b].push_back(a);
        }
    }
    int getanswer(){
        solve();
        std::set<std::pair<int,int> > set;
        for (int i = 1; i <= n; i ++){
            for (int j = 0; j < matrix[i].size(); j++){
                if (color[i] != color[matrix[i][j]] && !set.count(std::make_pair(color[i], color[matrix[i][j]])))
                    set.insert(std::make_pair(color[i], color[matrix[i][j]]));
            }
        }
        return set.size();
    }
};
int main()
{
    int n,m;
    freopen("condense2.in", "r", stdin);
    freopen("condense2.out", "w", stdout);
    std::cin>> n >> m;
    Graph graph(n,m);
    graph.readgraph();
    std::cout << graph.getanswer();
    return 0;
}

