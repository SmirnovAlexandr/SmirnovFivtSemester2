#include <iostream>
#include <vector>
#include <string>

class HashTable
{
    struct node{
        std::string key;
        std::string line;
    };
    
    std::vector<std::vector<node>> table;
    
public:
class Iterator
{
public:
    int x,y;
    std::vector<std::vector<node>> * pointer;
    Iterator (HashTable * p):pointer(&p->table)
    {
        x = begin();
        y = 0;
    }
    Iterator(int xx,int yy):x(xx),
    y(yy)
    {}
    int begin(){
        int x = 0;
        while (x < pointer -> size() -1 && pointer -> at(x).empty()) x++;
        return x;
    }
    int endx(){
        int x = pointer -> size() - 1;
        int start = begin();
        while (pointer -> at(x).empty() && x > start) x--;
        return x;
    }
    int endy(){
        return pointer -> at(endx()).size() - 1;
    }

    Iterator & operator ++(){
        if (x == endx() && y == endy()) throw std::logic_error ("overstep the bounds of the array");
        if (y == pointer -> at(x).size() - 1) {
            x++;
            y = 0;
        }
        else y++;
        while (pointer -> at(x).empty() && !(x == endx())) {
            x++;
        }
            
        return *this;
    }
    Iterator & operator --(){
        if (y == 0 && x == begin()) throw std::logic_error ("overstep the bounds of the array");
        if (y > 0) y--;
        else{
            while (x > begin() && pointer -> at(x).empty()) x--;
            y = pointer -> at(x).size();
        }
        return *this;
    }
    std::string & operator *(){
        return pointer -> at(x)[y].line;
    }
    node & operator -> (){
        return pointer -> at(x)[y];
    }
        
    bool operator == (Iterator temp){
        if (x == temp.x && y == temp.y) return true;
        else return false;
    }
};
    HashTable(int numbers)
    {
        quantbasket = numbers;
        table.resize(quantbasket);
        quantelements = 0;
        
    }

    
    int quantbasket, quantelements;
    
    Iterator begin(){
        Iterator beginit(this);
        beginit.x = beginit.begin();
        beginit.y = 0;
        return beginit;
    }
    Iterator end(){
        Iterator endit(this);
        endit.x = endit.endx();
        endit.y = endit.endy();
        return endit;
    }
    int GenerateHash(std::string &string){
        return string.length() % quantbasket;
    }
    void Add(std::string code, std::string info){
        relocate();
        int hash = GenerateHash(code);
        node temp;
        temp.key = code;
        temp.line = info;
        table[hash].push_back(temp);
        quantelements ++;
    }
    void relocate(){
        if (quantbasket == 0 || quantelements / quantbasket > 4){
            quantbasket++;
            table.resize(quantbasket);
            std::vector<std::vector<node>> table1(quantbasket);
            for (int i = 0; i < table.size(); i++)
                for (int j = 0; j < table[i].size(); j++)
                    table1[GenerateHash(table[i][j].key)].push_back(table[i][j]);
            table = table1;
            
        }
    }
    bool Find(std::string key){
        int i = GenerateHash(key);
        bool answer = false;
        for(int j = 0; j < table[i].size(); j++)
            if (table[i][j].key == key) answer = true;
        return answer;
    }
    
    void Delete(std::string string){
        if (!Find(string)) throw std::logic_error("string is missing");
        else{
            int i = GenerateHash(string);
            for (int j = 0; j < table[i].size(); j++){
                if (table[i][j].key == string){
                    table[i][j] = table[i][table[i].size() - 1];
                    table[i].pop_back();
                }
            }
        }
    }
    
        friend Iterator::Iterator (HashTable  * p);
    
};

void test1()//add, relocate, delete,find
{
    HashTable work(0);
    work.Add("code", "teststring");
    std::cout << work.Find("code") << " Right answer is 1" << '\n';
    std::cout << work.Find("Test") << " Right answer is 0" << '\n';
    work.Delete("code");
    std::cout << work.Find("code") << " Right answer is 0" << '\n';
    
}
void test2() // add, list operators
{
    HashTable work(5);
    work.Add("1","1");
    work.Add("2","2");
    work.Add("03", "03");
    HashTable::Iterator iterator(&work);
    ++iterator;
    std::cout << *iterator << " ";
    --iterator;
    std::cout << *iterator << '\n';
    
    while (!(iterator == work.end())) {
        std::cout << *iterator << '\n';
        ++iterator;
    }
    std::cout << *iterator;
    
    
    
}
int main()
{
    test1();
    test2();
}

