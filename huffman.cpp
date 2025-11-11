#include<iostream>
#include <vector>
#include<unordered_map>
#include<map>
#include<queue>
using namespace std;

struct Node{
    char data;
    int freq;
    Node * left, * right;
    Node(char d , int f){
        data = d;
        freq = f;
    }
};
struct Compare{
    bool operator()(Node * left ,  Node * right){
        return left -> freq > right -> freq;
    }
};

void StoreCodes(Node * root, unordered_map<char, string> & Codes, string code){
    if(!root) return ;
    if(!root -> left && ! root -> right){
        Codes[root -> data] = code;
        return ;
    }
    StoreCodes(root -> left , Codes, code + "0");
    StoreCodes(root -> right , Codes, code + "1");
}

void Build(string text){
    map<char, int> frequency;
    for(auto i : text){
        frequency[i] ++;
    }
    priority_queue<Node * , vector<Node*> , Compare> pq;

    for(auto i : frequency){
        pq.push(new Node(i.first , i.second));
    }

    while(pq.size() > 1){
        Node * left = pq.top();
        pq.pop();
        Node * right = pq.top();
        pq.pop();

        Node *internalNode = new Node('x' , left -> freq + right -> freq);
        internalNode -> left = left;
        internalNode -> right = right;
        pq.push(internalNode);
    }

    Node * root = pq.top();
    unordered_map<char, string> Codes;
    StoreCodes(root, Codes, "");

    for(auto i : Codes){
        cout << i.first << " " << i.second << endl;
    }
}
int main (){
    string s;
    cin >> s;
    Build(s);
}