#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    char c;
    int freq;
    Node* left;
    Node* right;

    Node() : c('\0'), freq(0), left(nullptr), right(nullptr) {}

    Node(char c, int freq, Node* l = nullptr, Node* r = nullptr)
        : c(c), freq(freq), left(l), right(r) {}
};

void defNodes(Node nodes[]);

void recordFreq(Node nodes[], char c);

void sort(Node nodes[], int left, int right);

Node* buildHuffmanTree(Node nodes[], string encodingArray[]);

void generateHuffmanCodes(Node* root, string code, string encodingArray[]);

void writeHuffmanTree(Node* root, ofstream& outFile);

int main() {
    ifstream inFile("text.txt");
    ofstream outFile("compress_ver.txt", ios::binary);
    int sum = 0;

    if (!inFile.is_open() || !outFile.is_open()) {
        cout << "Error opening input file." << endl;
        return 1;
    }

    char c;
    Node* nodes = new Node[60];
    defNodes(nodes);

    while (inFile.get(c))
        recordFreq(nodes, c);
    for (int i = 0; i < 60; i++)
        sum += nodes[i].freq;

    string* encodingArray = new string[256];  // Assuming ASCII characters
    sort(nodes, 0, 59);
    Node* root = buildHuffmanTree(nodes, encodingArray);

    inFile.clear();  // by this we can read the file again
    inFile.seekg(0, ios::beg);

    string encodedText = "";
    while (inFile.get(c))
        encodedText += encodingArray[static_cast<unsigned char>(c)];

    inFile.close();
    outFile.write(reinterpret_cast<char*>(&sum), sizeof(int));  // write the number of the characters
    writeHuffmanTree(root, outFile);

    unsigned char buffer = 0;
    int bitCount = 0;
    for (size_t i = 0; i < encodedText.length(); ++i) {
        buffer = (buffer << 1) | (encodedText[i] - '0');
        ++bitCount;

        if (bitCount == 8) {
            outFile.put(buffer);
            buffer = 0;
            bitCount = 0;
        }
    }

    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        outFile.put(buffer);
    }

    outFile.close();

    delete[] nodes;
    delete root;

    return 0;
}

void defNodes(Node nodes[]) {
    for (int i = 0; i < 26; i++) {
        nodes[i].c = 'a' + i;
        nodes[i].freq = 0;
    }
    for (int i = 0; i < 26; i++) {
        nodes[i + 26].c = 'A' + i;
        nodes[i + 26].freq = 0;
    }
    nodes[52].c = ' ';
    nodes[52].freq = 0;
    nodes[53].c = '.';
    nodes[53].freq = 0;
    nodes[54].c = ',';
    nodes[54].freq = 0;
    nodes[55].c = '(';
    nodes[55].freq = 0;
    nodes[56].c = ')';
    nodes[56].freq = 0;
    nodes[57].c = '"';
    nodes[57].freq = 0;
    nodes[58].c = '\'';
    nodes[58].freq = 0;
    nodes[59].c = '\n';
    nodes[59].freq = 0;
}

void recordFreq(Node nodes[], char c) {
    if (c >= 'a' && c <= 'z')
        nodes[c - 'a'].freq++;
    else if (c >= 'A' && c <= 'Z')
        nodes[c - 'A' + 26].freq++;
    else if (c == ' ')
        nodes[52].freq++;
    else if (c == '.')
        nodes[53].freq++;
    else if (c == ',')
        nodes[54].freq++;
    else if (c == '(')
        nodes[55].freq++;
    else if (c == ')')
        nodes[56].freq++;
    else if (c == '"')
        nodes[57].freq++;
    else if (c == '\'')
        nodes[58].freq++;
    else if (c == '\n')
        nodes[59].freq++;
    else
        cout << "Error: " << c << " is not a valid character." << endl;
}

void sort(Node nodes[], int left, int right) {
    int i = left, j = right + 1;
    if (left < right) {
        while (i < j) {
            while (nodes[++i].freq < nodes[left].freq)
                ;
            while (nodes[--j].freq > nodes[left].freq)
                ;
            if (i >= j)
                break;
            Node tmp = nodes[i];
            nodes[i] = nodes[j];
            nodes[j] = tmp;
        }
        Node tmp = nodes[j];
        nodes[j] = nodes[left];
        nodes[left] = tmp;
        sort(nodes, left, j - 1);
        sort(nodes, j + 1, right);
    }
}

Node* buildHuffmanTree(Node nodes[], string* encodingArray) {
    int left = 0;
    int right = 59;  // Assuming you have 60 nodes

    // Build the Huffman Tree using a bottom-up approach
    while (left < right) {
        Node* newNode = new Node('\0', nodes[left].freq + nodes[left + 1].freq, new Node(nodes[left]), new Node(nodes[left + 1]));
        nodes[left + 1] = *newNode;
        left++;
        sort(nodes, left, right);
    }

    generateHuffmanCodes(&nodes[right], "", encodingArray);

    return new Node(nodes[right]);
}

void generateHuffmanCodes(Node* root, string code, string encodingArray[]) {
    if (root->left == nullptr && root->right == nullptr) {
        encodingArray[static_cast<unsigned char>(root->c)] = code;  // Store the mapping
        return;
    }

    generateHuffmanCodes(root->left, code + "0", encodingArray);
    generateHuffmanCodes(root->right, code + "1", encodingArray);
}

void writeHuffmanTree(Node* root, ofstream& outFile) {
    if (root->left == nullptr && root->right == nullptr) {
        outFile.put('1');
        outFile.put(root->c);
        return;
    }
    else {
        outFile.put('0');
        writeHuffmanTree(root->left, outFile);
        writeHuffmanTree(root->right, outFile);
    }
}
