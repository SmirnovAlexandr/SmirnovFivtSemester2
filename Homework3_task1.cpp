#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <unordered_map>
#include <ctime>

const int LEN = 30000;
const int MIN_NUM_CHANGES = 20;
const int MAX_NUM_CHANGES = 21;

typedef std::pair<int, std::pair<int, int> > verpair;
typedef std::pair<int, int> pair;

struct hash{
    int operator () (const pair &p) const {
        return p.first + p.second;
    }
};
class Heap{
    std::vector<verpair> array;
    std::unordered_map<pair, int, hash> map;
    
    void sift_up(int v){
        if (v > 0 && array[v].first < array[(v - 1) / 2].first){
            auto a = map.find(array[v].second);
            auto b = map.find(array[(v - 1) / 2].second);
            if (a != map.end()) (*a).second = (v - 1) / 2;
            if (b != map.end()) (*b).second = v;
            std::swap(array[v], array[(v - 1) / 2]);
            sift_up((v - 1) / 2);
        }
    }
    void sift_down(int v){
        int left = 2 * v + 1;
        int right = 2 * v + 2;
        int smallest = v;
        if (left < array.size() && array[left].first < array[smallest].first)
            smallest = left;
        if (right < array.size() && array[right].first < array[smallest].first)
            smallest = right;
        if (smallest != v){
            auto a = map.find(array[v].second);
            auto b = map.find(array[smallest].second);
            if (a != map.end()) (*a).second = smallest;
            if (b != map.end()) (*b).second = v;
            std::swap(array[v], array[smallest]);
            sift_down(smallest);
        }
    }
public:
    verpair top(){
        verpair temp = array[0];
        map.erase(temp.second);
        array[0] = array[array.size() - 1];
        array.pop_back();
        sift_down(0);
        //std::cout << "Heap size: " << array.size() << " Map size: " << map.size() << "\n";
        return temp;
    }
    void push(verpair p){
        auto it = map.find(p.second);
        if (it == map.end()){
            array.push_back(p);
            map[p.second] = array.size() - 1;
            sift_up(array.size() - 1);
        }
        else if (array[(*it).second].first > p.first){
            decrease_key((*it).second, p.first);
        }
        
    }
    
    void decrease_key(int pointer, int new_weight){
        array[pointer].first = new_weight;
        sift_up(pointer);
    }
    bool empty(){
        return array.size() == 0;
    }
};

class Hish{
    std::string s1, s2;
    Heap heap;
    int answer;
    int discard_potentials(pair start, pair finish, int old)
    {
        return old + std::abs(start.first - start.second) - std::abs(finish.first - finish.second);
    }
    
    int apply_potentials  (pair start, pair finish, int old)
    {
        return old + std::abs(finish.first - finish.second) - std::abs(start.first - start.second);
    }
    
public:
    Hish(const std::string &line1, const std::string &line2):
    s1(line1),
    s2(line2)
    {}
    void solve(){
        heap.push(std::make_pair(0, std::make_pair(0, 0)));
        s1 = "0" + s1;
        s2 = "0" + s2;
        while (!heap.empty()){
            verpair top = heap.top();
            pair vertex = top.second;
            if (vertex == std::make_pair((int)s1.length() - 1, (int)s2.length() - 1)){
                answer = discard_potentials(std::make_pair(0, 0), vertex, top.first);
                break;
            }
            if (vertex.second + 1 < s2.length() && s1[vertex.first] != s2[vertex.second + 1]){
                pair temp = vertex;
                temp.second++;
                heap.push(std::make_pair(top.first + apply_potentials(vertex, temp, 1), temp));
            }
            if (vertex.first + 1 < s1.length() && s1[vertex.first + 1] != s2[vertex.second]){
                pair temp = vertex;
                temp.first++;
                heap.push(std::make_pair(top.first + apply_potentials(vertex, temp, 1), temp));
            }
            if (vertex.first + 1 < s1.length() && vertex.second + 1 < s2.length()){
                int weight = 0;
                if (s1[vertex.first + 1] != s2[vertex.second + 1]) weight = 1;
                pair temp = vertex;
                temp.first++;
                temp.second++;
                heap.push(std::make_pair(top.first + apply_potentials(vertex, temp, weight), temp));
            }
        }
    }
    int getanswer(){
        return answer;
    }
};
class WagFish
{
    std::string line1, line2;
public:
    WagFish(const std::string &line1, const std::string &line2):
    line1(line1),
    line2(line2)
    {}
    int getanswer(){
        std::vector<std::vector<int>> d( line1.length() + 1, std::vector<int> (line2.length(), 0));
        for(int i = 0; i <= line1.length();i++)
            for(int j = 0; j <= line2.length(); j++){
                if (i == 0 && j == 0) d[i][j] = 0;
                else if (i > 0 && j == 0) d[i][j] = i;
                else if (i == 0 && j > 0) d[i][j] = j;
                else if (line1[i - 1] == line2[j - 1]) d[i][j] = d[i - 1][j - 1];
                else d[i][j] = std::min(d[i - 1][j], std::min(d[i][j - 1], d[i - 1][j - 1])) + 1;
            }
        return d[line1.length()][line2.length()];
    }
};

std::string genstring(int len){
    std::string ans;
    for (int i = 0; i < len; i++){
        ans.push_back((char) (rand() % 26 + 97));
    }
    return ans;
};
void RandInsert(std::string &str)
{
	long pos = rand() % str.length();
	char ch = rand() % 26 + 65;
    std::string ins_str;
	ins_str += ch;
	str.insert(pos, ins_str);
}
void RandDelete(std::string &str)
{
	if (str.empty()) return;
	long pos = rand() % str.length();
	str.erase(pos, 1);
}

void RandReplace(std::string &str)
{
	if (str.empty()) return;
	long pos = rand() % str.length();
	char ch = rand() % 26 + 65;
    std::string ins_str;
	ins_str += ch;
    
	str.replace(pos, 1, ins_str);
}
void ChangeString(std::string &str, int min_num, int max_num, int &changes)
{
    changes = rand() % (max_num - min_num) + min_num;
	for (long i = 0; i < changes; i++)
	{
		long type = rand() % 3;
		switch (type)
		{
            case 0:
                RandInsert(str);
                break;
            case 1:
                RandDelete(str);
                break;
            case 2:
                RandReplace(str);
                break;
		}
	}
}

int main()
{
    std::string line1;
    std::string line2;
    std::cin >> line1;
    std::cin >> line2;
    Hish hishhish(line1,line2);
    hishhish.solve();
    std::cout << hishhish.getanswer();
    /*srand(time(0));
    std::string line1 = genstring(LEN);
    std::string line2 = line1;
    //std::cout << line1 << "\n";
    int answer;
    ChangeString(line2, MIN_NUM_CHANGES, MAX_NUM_CHANGES, answer);
    //std::cout << line2 << "\n";
    Hish hishhish(line1,line2);
    hishhish.solve();
    std::cout << "It is OK\n";
    WagFish wagwag(line1, line2);
    int ans1 = hishhish.getanswer();
    int ans2 = wagwag.getanswer();
    if (ans1 == ans2) std::cout << "It is OK\n" << "Answer is " << ans1 << "\n";
    else {
        std::cout << "Work: " << ans1 << "\n";
        std::cout << "Test: " << ans2 << "\n";
        std::cout << "Just cry\n";
    }
 */
    return 0;
}

