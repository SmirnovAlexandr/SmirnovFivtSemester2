#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> ansvalues(n + 1, std::numeric_limits<int>::max());
    std::vector<int> elements(n + 1);
    std::vector<int> parents(n + 1, 0), index(n + 1, 0);
    int a1,k,b,m;
    
    //generate array with elements
    std::cin >> a1 >> k >> b >> m;
    elements[1] = a1;
    for (size_t i = 2; i <= n; i++)
        elements[i] = (k * elements[i - 1] + b) % m;
    //for (int i = 1; i <= n; i++) std::cin >> elements[i];
    ansvalues[0] = std::numeric_limits<int>::min();
    for (int i = 1; i <= n; i++){
        int findvar = int (upper_bound (ansvalues.begin(), ansvalues.end(), elements[i]) - ansvalues.begin());
        if (ansvalues[findvar - 1] < elements[i] && elements[i] < ansvalues[findvar]){
            ansvalues[findvar] = elements[i];
            index[findvar] = i;
            if (findvar == 1) parents[i] = 0;
            else parents[i] = index[findvar - 1];
        }
        
    }
    
    int max = ansvalues.size() - 1;
    while ( ansvalues[max] == std::numeric_limits<int>::max()) max--;
    //std::cout << max << '\n';
    
    std::vector<int> answer;
    int ind = index[max];
    while (ind !=0 ){
        answer.push_back(ind);
        ind = parents[ind];
    }
    for (int i = answer.size() - 1 ; i >= 0; i--){
        std::cout << elements[answer[i]] << ' ';
    }
    return 0;
}

