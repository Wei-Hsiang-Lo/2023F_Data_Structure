#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 1000;//this can change the size of the queue, since the maze is not too big, so i only set 1000.

struct Node{
    //this structuct is used to write down the position of the node
    //and the distance between the start point and the node
    int x, y, dist;
};

class Queue{
public:
    Queue();//constructor
    void push(Node *node);//add new node to the array.
    void pop();//subtracting the value of the index at rear like removing the node from the array.
    Node& peek();//to get the node from the array at front.
    bool empty()const;//check if the queue is empty.
private:
    Node arr[MAX_SIZE];
    int front, rear;
};

//the possible ways of moving
int row[] = {-1, 0, 0, 1};
int col[] = {0, -1, 1, 0};

//check if it can reach the position(row, col).
//return false if the position is not valid or the value is 0 or the positio had been visited.
bool isValid(vector<vector<int>> const &maze, vector<vector<bool>> &visited, int r, int c);

//find the shortest path between the start cell and the end cell.
vector<pair<int, int>> findTheShortestPath(vector<vector<int>> const &maze, pair<int, int> &src, pair<int, int> &dest);

void reverse(vector<pair<int, int>>& path);

int main(){
    int m, n;
    int posCol, posRow;
    char type;

    //construct and m by n maze
    cin >> m >> n;
    //construct an m by n metric and assign 1 as the value of the elements inside.
    vector<vector<int>> maze(m, vector<int>(n, 1));
    
    pair<int, int> src = make_pair(-1, -1);
    pair<int, int> dest = make_pair(-1, -1);
    for(posRow = 0; posRow < m; posRow++){
        while(cin >> posCol && posCol != 0 && posCol <= n){
            cin >> type;
            if(type == 's')
                src = make_pair(posRow, posCol - 1);
            else if(type == 't')
                dest = make_pair(posRow, posCol - 1);
            else if(type == 'x')
                maze[posRow][posCol - 1] = 0;
            else
                maze[posRow][posCol] = 1;
        }
    }
    if(src.first == -1 || dest.first == -1)
        cout << "Destination cannot be reached from a given start cell." << endl;
    vector<pair<int, int>> shortestPath = findTheShortestPath(maze, src, dest);
    if(!shortestPath.empty()){
        for(auto &path : shortestPath){
            cout << "(" << path.first << ", " << path.second << ")" << " ";
        }
        cout << endl;
    }
    else{
        cout << "Destination cannot be reached from a given start cell." << endl;
    }
    maze.clear();

    return 0;
}

bool isValid(vector<vector<int>> const &maze, vector<vector<bool>> &visited, int r, int c){
    return (r >= 0 && r < maze.size()) && (c >= 0 && c < maze[0].size()) && maze[r][c] && !visited[r][c];
}

vector<pair<int, int>> findTheShortestPath(vector<vector<int>> const &maze, pair<int, int> &src, pair<int, int> &dest){
    if(maze.size() == 0 || maze[src.first][src.second] == 0)
        return {}; 
    int M = maze.size();
    int N = maze[0].size();

    //create this 2D vector to records whether the giving position had been visited.
    vector<vector<bool>> visited(M, vector<bool>(N, false));
    vector<vector<pair<int, int>> > parent(M, vector<pair<int, int>>(N, make_pair(-1, -1)));

    //save the node that need to be dealt
    Queue q;
    int i = src.first;
    int j = src.second;
    Node tempNode;
    tempNode.x = i;
    tempNode.y = j;
    tempNode.dist = 0;
    visited[i][j] = true;
    q.push(&tempNode);

    //if the queue q is empty, means there is no node need to be dealt.
    while(!q.empty()){
        Node *node = &q.peek();
        q.pop();//remove the first node that had already been gotten by the above line.
        int i = node->x, j = node->y, dist = node->dist;
        //if the x and y coordinates of the node equal to the x and y coordinates of destination, we have the shortest path.
        if(i == dest.first && j == dest.second){
            vector<pair<int, int>> path;
            while (i != -1 && j != -1) {
                path.push_back(make_pair(i + 1, j + 1));
                int new_i = parent[i][j].first;
                int new_j = parent[i][j].second;
                i = new_i;
                j = new_j;
            }
            reverse(path); 
            return path;
        }
        //since there are as most four ways of the node to go, I used for loop to deal with it.
        for(int k = 0; k < 4; k++){
            if(isValid(maze, visited, i + row[k], j + col[k])){
                Node newNode;
                visited[i + row[k]][j + col[k]] = true;
                parent[i + row[k]][j + col[k]] = make_pair(i, j);
                newNode.x = i + row[k];
                newNode.y = j + col[k];
                newNode.dist = dist + 1;
                q.push(&newNode);
            }
        }
    }
    return {};
}

//by this function, i can record shortest path from the start point to the end point
void reverse(vector<pair<int, int>>& path){
    int start = 0;
    int end = path.size() - 1;

    while(start < end){
        swap(path[start], path[end]);
        ++start;
        --end;
    }
}

Queue::Queue(){
    front = -1;
    rear = -1;
}

void Queue::push(Node* node){
    if(rear == (MAX_SIZE - 1)){
        cout << "Queue is overflow!" << endl;
        return;
    }
    if(empty()){
        front = 0;
        rear = 0;
    }
    else
        rear++;
    arr[rear] = *node;
}

void Queue::pop(){
    if(empty()){
        cout << "Queue is empty!" << endl;
        return; 
    }
    if(front == rear){
        front = -1;
        rear = -1;
    }
    else
        front++;
}
Node& Queue::peek(){
    if(empty())
        cout << "Queue is empty." << endl;
    return arr[front];
}

bool Queue::empty()const{
    return front == -1;
}