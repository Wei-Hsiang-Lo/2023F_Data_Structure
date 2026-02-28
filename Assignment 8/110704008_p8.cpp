#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Edge
{
    int src, dest, weight;
};

struct Subset
{
    int parent, rank;
};

class Graph
{
public:
    int V, E;
    vector<Edge> edges;
    Graph(int v, int e);
    void addEdge(int src, int dest, int weight);
    int find(Subset subsets[], int i);
    void Union(Subset subsets[], int x, int y);
    void Sort(int low, int high);
    int partition(int low, int high);
    void generateGraphvizDot(const string &filename);
    void KruskalMST();
};

int main()
{
    int numV, numE;
    int V, E, W;
    string filename;
    cin >> filename;
    ifstream inFile(filename);
    inFile >> numV >> numE;
    Graph graph(numV, numE);

    while(!inFile.eof() && inFile >> V >> E >> W){
        graph.addEdge(V, E, W);
    }

    graph.KruskalMST();
    inFile.close();

    return 0;
}

Graph::Graph(int v, int e) : V(v), E(e) {}

void Graph::addEdge(int src, int dest, int weight)
{
    edges.push_back({src, dest, weight});
}

int Graph::find(Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Graph::Union(Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    //Attach smaller rank tree under root of high rank tree
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Custom sorting function using quicksort
void Graph::Sort(int low, int high)
{
    //Iterate through edges and sort them by weight
    if (low < high)
    {
        int pivot = partition(low, high);
        Sort(low, pivot - 1);
        Sort(pivot + 1, high);
    }
}

int Graph::partition(int low, int high)
{
    int pivot = edges[high].weight;
    int i = low - 1;

    //Iterate through edges
    for (int j = low; j < high; j++)
    {
        if (edges[j].weight <= pivot)
        {
            i++;
            swap(edges[i], edges[j]);
        }
    }
    
    swap(edges[i + 1], edges[high]);
    return i + 1;
}

// this part enables me to visualize the graph
void Graph::generateGraphvizDot(const string &filename)
{
    ofstream dotFile(filename);
    if (!dotFile.is_open())
    {
        cerr << "Error opening DOT file for writing." << endl;
        return;
    }

    dotFile << "graph MST {\n";
    for (const Edge &edge : edges)
    {
        dotFile << edge.src << " -- " << edge.dest << " [label=\"" << edge.weight << "\"];\n";
    }
    dotFile << "}\n";

    dotFile.close();
}

//this function uses Kruskal's algorithm to find the minimum spanning tree
void Graph::KruskalMST()
{
    Sort(0, E - 1);

    vector<Edge> result;
    Subset *subsets = new Subset[V];

    //Initialize subsets
    for (int i = 0; i < V; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    //Iterate through sorted edges
    for (const Edge &edge : edges)
    {
        int x = find(subsets, edge.src);
        int y = find(subsets, edge.dest);

        if (x != y)
        {
            result.push_back(edge);
            Union(subsets, x, y);
        }
    }

    //Print result
    cout << "Minimum Spanning Tree:\n";
    for (const Edge &edge : result)
    {
        cout << edge.src << " -- " << edge.dest << " : " << edge.weight << "\n";
    }

    generateGraphvizDot("graphviz_output.dot");

    delete[] subsets;
}