#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9; // Represents infinity

// Define a structure to represent an edge in the graph
struct Edge {
    int destination;
    int weight;

    Edge(int dest, int w) : destination(dest), weight(w) {}
};

// Define a structure to represent a vertex in the graph
struct Vertex {
    int id;
    int distance;

    Vertex(int i) : id(i), distance(INF) {}
};

// Custom comparison function for the binary heap
struct CompareVertices {
    bool operator()(const Vertex& v1, const Vertex& v2) const {
        return v1.distance > v2.distance;
    }
};

// Manually implemented min-heap
class MinHeap {
public:
    vector<Vertex> heap;

    // Push a vertex onto the heap
    void push(Vertex v) {
        heap.push_back(v);
        int index = heap.size() - 1;
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent].distance <= heap[index].distance) {
                break;
            }
            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    // Get the vertex with the smallest distance without removing it
    Vertex top() const {
        return heap[0];
    }

    // Pop the vertex with the smallest distance from the heap
    void pop() {
        if (heap.empty()) {
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        int index = 0;
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;
            if (leftChild < heap.size() && heap[leftChild].distance < heap[smallest].distance) {
                smallest = leftChild;
            }
            if (rightChild < heap.size() && heap[rightChild].distance < heap[smallest].distance) {
                smallest = rightChild;
            }
            if (smallest == index) {
                break;
            }
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }
    
    // Check if the heap is empty
    bool empty() const {
        return heap.empty();
    }
};

// Dijkstra's algorithm function with a manually implemented min-heap
void dijkstra(vector<vector<Edge>>& graph, int source, int destination) {
    int numVertices = graph.size();

    // Create a manually implemented min-heap for vertices
    MinHeap pq;

    // Create an array to store distances from source to each vertex
    vector<int> distance(numVertices, INF);

    // Initialize source vertex
    distance[source] = 0;
    pq.push(Vertex(source));

    while (!pq.empty()) {
        Vertex currentVertex = pq.top();
        pq.pop();

        int u = currentVertex.id;
        // Explore neighboring vertices
        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            int w = edge.weight;

            // Relaxation step
            if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                pq.push(Vertex(v));
            }
        }
    }

    // Output the shortest path distance from source to destination
    cout << "Shortest path distance from " << source << " to " << destination << ": " << distance[destination] << endl;
}

int main() {
    int numVertices, vertex_1 = 0, vertex_2, weight, source, destination;
    cout << "Enter the number of vertices:";
    cin >> numVertices;
    // Create a vector of vectors to represent the graph
    vector<vector<Edge>> graph(numVertices);

    // Input the edges and its weight of the graph
    for(int i = 0; i < numVertices; i++){
        while(cin >> vertex_2 && vertex_2 != 0){
            cin >> weight;
            graph[vertex_1].push_back(Edge(vertex_2, weight));
        }
        vertex_1++;
    }
    
    cout << "Enter the start vertex and the end vertex: ";
    cin >> source >> destination;

    dijkstra(graph, source, destination);

    return 0;
}
