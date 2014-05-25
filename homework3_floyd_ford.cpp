#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <ctime>
const double INF = std::numeric_limits<double>::lowest();
const int MAX = 100;
const int DELTA = 5;
class cycle{
    struct edge {
        int start, finish;
        double cost;
    };
    std::vector<std::vector<double> > w, forans;
    std::vector<std::vector<int> > par;
    std::vector<int> answer, parents;
    std::vector<double> distanse;
    int n;
    std::vector<edge> edges;
    void ford(){
        int x;
        createedges();
        for (int i = 0; i < n; i++) {
            x = -1;
            for (int j = 0; j < edges.size(); j++)
                if (distanse[edges[j].finish] > distanse[edges[j].start] + edges[j].cost) {
                    distanse[edges[j].finish] = std::max (INF, distanse[edges[j].start] + edges[j].cost);
                    parents[edges[j].finish] = edges[j].start;
                    x = edges[j].finish;
                }
        }
        if (x != -1) {
            int y = x;
            for (int i = 0; i < n; i++)
                y = parents[y];
            for (int cur = y; ; cur = parents[cur]) {
                answer.push_back (cur);
                if (cur == y && answer.size() > 1)  break;
            }
            reverse (answer.begin(), answer.end());
        }
    }
    void floyd(){
        int cvertex = -1;
        for (int k = 0; k < n && cvertex < 0; k++)
            for (int i = 0; i < n && cvertex < 0; i++)
                for (int j = 0; j < n && cvertex < 0; j++)
                    if (w[i][j] > w[i][k]+ w[k][j]) {
                        w[i][j] = w[i][k] + w[k][j];
                        par[i][j] = k;
                        if (i == j && w[i][j] < 0) cvertex = i;
                    }
        if (cvertex > 0){
            FindWay(cvertex, cvertex, answer);
            answer.push_back(cvertex);
        }
    }
    void set(){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++){
                w[i][j] = - std::log(w[i][j]);
            }
    }
    void FindWay(int a, int b, std::vector<int> &ans)
    {
        if (par[a][b] == -1 || (a == par[a][b] && b == par[a][b]))
            ans.push_back(a);
        else
        {
            FindWay(a, par[a][b], ans);
            FindWay(par[a][b], b, ans);
        }
    }
    void createedges(){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j) {
                    edge temp;
                    temp.start = i;
                    temp.finish = j;
                    temp.cost = w[i][j];
                    edges.push_back(temp);
                }
    }
    void generate_matrix(int size){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (i == j) w[i][j] = 1;
                else {
                    bool type = rand() % 2;
                    if (type) w[i][j] = 1 / (1 + (double)(rand() % MAX) / DELTA);
                    else w[i][j] = (1 + (double)(rand() % MAX) / DELTA);
                }
            }
        }
    }
public:
    void read(){
        for(int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                std::cin >> w[i][j];
        set();
    }
    void writeanswer(){
        for (int i = 0; i < answer.size(); i++)
            std::cout << answer[i] + 1 << ' ';
    }
   void tester(){
       generate_matrix(n);
       forans = w;
       for (int i = 0; i < n; i++){
           for (int j = 0; j < n; j++)
               std::cout << forans[i][j] << ' ';
           std::cout << "\n";
       }
       set();
       floyd();
       std::cout << "Floyd:\n";
       double result = 1;
       for (int i = 1; i < answer.size(); i++)
           result *= forans[answer[i-1]][answer[i]];
       if (result > 1) std::cout << "It is OK\n";
       else std::cout << "Just cry\n";
       writeanswer();
       std::cout << "\nFord:\n";
       answer.resize(0);
       par.assign(n, std::vector<int> (n, -1));
       w = forans;
       set();
       ford();
       result = 1;
       for (int i = 1; i < answer.size(); i++)
       result *= forans[answer[i-1]][answer[i]];
       if (result > 1) std::cout << "It is OK\n";
       else std::cout << "Just cry\n";
       writeanswer();
    }
    
    cycle(int num):
    w(num, std::vector<double> (num)),
    par(num, std::vector<int> (num, -1)),
    n(num),
    distanse(num, std::numeric_limits<double>::max()),
    parents(num, -1)
    {
        distanse[0] = 0;
    }
};
int main()
{
    srand(time(0));
    cycle work(5);
    //work.read();
    work.tester();
    return 0;
}

