#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <cstdio>

class Graph{
    std::vector<std::vector<int> > matrix;
    std::vector<int> color, tin, fup, order;
    std::vector<std::pair<int, int> > edges;
    int time;
    void dfs1(int vertex){
        order.push_back(vertex);
        color[vertex] = 1;
        int i = 0;
        while (i < matrix[vertex].size()){
            if (color[matrix[vertex][i]] == 0){
                int to = matrix[vertex][i];
                matrix[vertex][i] = matrix[vertex][matrix[vertex].size() - 1];
                matrix[vertex].pop_back();
                i--;
                dfs1(to);
            }
            i++;
        }
    }
    void dfs2(int vertex, int colors){
        color[vertex] = colors;
        for (int i = 0; i < matrix[vertex].size(); i++)
            if (color[matrix[vertex][i]] == 0) dfs2(matrix[vertex][i], colors);
    }
public:
    Graph(int numbersofvertexes):
    matrix(numbersofvertexes, std::vector<int> (0)),
    color(numbersofvertexes, 0),
    tin(numbersofvertexes, 0),
    fup(numbersofvertexes, 0),
    time(0)
    {}
    void readgraph(int m){
        for (int i = 0; i < m; i++){
            int start, finish;
            std::cin >> start >> finish;
            matrix[start].push_back(finish);
            matrix[finish].push_back(start);
            edges.push_back(std::make_pair(start, finish));
        }
    }
    
    void solve(){
        for (int i = 0; i < matrix.size(); i++)
            if (color[i] == 0) dfs1(i);
        color.assign(matrix.size(), 0);
        int colors = 0;
        for (int i = 0; i < order.size(); i++)
            if (color[order[i]] == 0)
                dfs2(order[i], ++colors);
        std::vector<int> answer;
        for (int i = 0; i < edges.size(); i++)
            if (color[edges[i].first] != color[edges[i].second])
                answer.push_back(i + 1);
        std::cout << answer.size() << '\n';
        for (int i = 0; i < answer.size(); i++)
            std::cout << answer[i] << '\n';
    }
};
int main(int argc, const char * argv[])
{
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);
    int n,m;
    std::cin >> n >> m;
    Graph graph(n + 1);
    graph.readgraph(m);
    graph.solve();
    return 0;
}

