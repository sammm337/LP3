#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>

using namespace std;

struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);
    }
};

void printCodes(MinHeapNode* root, string str) {
    if (!root)
        return;

    if (root->data != '$') {
        cout << root->data << ": " << str << "\n";
    }

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(string text) {
    map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }

    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (auto pair : freqMap) {
        minHeap.push(new MinHeapNode(pair.first, pair.second));
    }

    MinHeapNode *left, *right, *top;
    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    cout << "Huffman Codes:\n";
    printCodes(minHeap.top(), "");
}

int main() {
    string str = "BCAADDDCCACACAC";
    cout << "Input string: " << str << endl;
    HuffmanCodes(str);
    return 0;
}
