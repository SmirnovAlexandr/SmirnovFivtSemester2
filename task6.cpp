#include <iostream>
#include <vector>
#include <stack>


class Graph{
    int time;
    bool flag = true;
    std::vector<int> color;
    std::vector<int> timein,timeout;
    std::vector<std::vector<int>> matrix;
    std::vector<int> answer;
    struct Node
    {
        int realtop;
        int lasttop;//number of position if vector
    };
public:
    Graph(int numbersoftops, const std::vector<std::vector<int>> & mat):
    color(numbersoftops, 0),
    timein(numbersoftops),
    timeout(numbersoftops),
    matrix(mat),
    time(0)
    {}
    
    void dfs(int top)
    {
        std::stack<Node> stack;
        Node temp;
        temp.realtop = top;
        temp.lasttop = 0;
        stack.push(temp);
        while (stack.size() > 0 && flag){
            if (!visited(stack.top().realtop)){
                time++;
                timein[stack.top().realtop] = time;
                color[stack.top().realtop] = 1;
            }
            if (matrix[stack.top().realtop].size() == stack.top().lasttop){
                time++;
                timeout[stack.top().realtop] = time;
                color[stack.top().realtop] = 2;
                answer.push_back(stack.top().realtop);
                stack.pop();
            }
            else{
                if (color[getvertex(stack)] == 1) flag = false;
                else if (!visited(getvertex(stack))){
                    Node temp;
                    temp.realtop = getvertex(stack);
                    temp.lasttop = 0;
                    stack.top().lasttop++;
                    stack.push(temp);
                }
                else stack.top().lasttop++;
            }
        }
    
    }
    bool visited(int top){
        return timein[top];
    }
    int getvertex(const std::stack<Node> & stack){
        return matrix[stack.top().realtop][stack.top().lasttop];
    }
    void writeanswer(){
        if (flag){
            std::cout << "Yes\n";
            for (int i = answer.size() - 1; i >= 0; i--)
                std::cout << answer[i] << ' ';
        }
        else std::cout<< "No\n";
    }
};
int main()
{
    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> d(n + 1, std::vector<int>(0));
    for (int i = 0; i < m; i++){
        int a,b;
        std::cin >> a >> b;
        d[a].push_back(b);
    }
    Graph graph(n + 1,d);
    for (int i = 1; i <=n; i++)
        if (!graph.visited(i)) graph.dfs(i);
    graph.writeanswer();
    return 0;
}

