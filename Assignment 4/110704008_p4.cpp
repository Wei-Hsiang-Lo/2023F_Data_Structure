#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int col;
    int value;
    Node* link;
};

typedef Node* NodePtr;

void makeMatrix(vector<NodePtr>& matrix);

void printMatrix(vector<NodePtr>& matrix, int m, int n);

void releaseMem(vector<NodePtr>& makeMatrix, int m, int n);

void matrixAdd(vector<NodePtr>& matrix_A, vector<NodePtr>& matrix_B, vector<vector<int>>& resAdd, int m, int n);

vector<vector<int>> matrixMultiply(vector<NodePtr>& matrix_A, vector<NodePtr>& matrix_B, int l, int m, int n);

vector<NodePtr> transpose(vector<NodePtr>& matrix, int m, int n);

int main(){
    int l, m, n, p, q;
    
    cout << "Input l ,m, n respectively : " << endl;
    cin >> l >> m >> n ;
    vector<NodePtr> matrix_A;
    vector<NodePtr> matrix_B;
    vector<NodePtr> matrix_C;
    vector<NodePtr> matrix_D;
    vector<vector<int>> resAdd(m, vector<int>(n, 0));//intialize the matrix with zero

    cout << "Input two m by n matrices for addition." << endl;
    //call the funciton to save each row of matrices A and B
    for(int tempRow = 0; tempRow < m; tempRow++)
        makeMatrix(matrix_A);
    for(int tempRow = 0; tempRow < m; tempRow++)
        makeMatrix(matrix_B);

    cout << "Input two matrices for multiply." << endl;
    cout << "Input the l by m matrix : " << endl;
    for(int tempRow = 0; tempRow < l; tempRow++)
        makeMatrix(matrix_C);
    cout << "Input the m by n matrix : " << endl;
    for(int tempRow = 0; tempRow < m; tempRow++)
        makeMatrix(matrix_D);
    //call the fucntion to do addition with matrices A and B
    matrixAdd(matrix_A, matrix_B, resAdd, m, n);

    cout << "Matrix A has " << m << " rows and " << n << " columns." << endl;
    printMatrix(matrix_A, m, n);//print the matrix to check whether te input is right or the mathods to save matric is right
    cout << "Matrix B has " << m << " rows and " << n << " columns." << endl;
    printMatrix(matrix_B, m, n);
    cout << "Matrix A + B" << endl;
    //print result of matirces addition
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            cout << resAdd[i][j] << " ";
        cout << endl;
    }
    cout << "Matrix C has " << l << " rows and " << m << " columns." << endl;
    printMatrix(matrix_C, l, m);
    cout << "Matrix D has " << m << " rows and " << n << " columns." << endl;
    printMatrix(matrix_D, m, n);
    //transpose the matrix D to do the mtrix multiplication since it is more easylily to do the multiplication with transpose matrix
    vector<NodePtr> matrix_E = transpose(matrix_D, m, n);//initialize the matrix which used to store the product of the matrices
    cout << "Matrix C x D" << endl;
    vector<vector<int>> resMul = matrixMultiply(matrix_C, matrix_E, l, m, n);
    for(int i = 0; i < l; i++){
        for(int j = 0; j < n; j++)
            cout << resMul[i][j] << " ";
        cout << endl;
    }
    //free memory
    releaseMem(matrix_A, m, n);
    releaseMem(matrix_B, m, n);
    releaseMem(matrix_C, l, p);
    releaseMem(matrix_D, m, n);
    releaseMem(matrix_E, n, m);

    return 0;
}

void makeMatrix(vector<NodePtr>& matrix){
    //with the input format, the methods i used is insert at rear.
    //and i use the skill, dummy node for fear that empty rows occur.
    NodePtr head = new Node;
    NodePtr rear = head;
    head->link = nullptr;
    int col, value;
    while(cin >> col && col != 0){
        cin >> value;
        NodePtr temp = new Node;
        temp->col = col;
        temp->value = value;
        temp->link = nullptr;
        rear->link = temp;
        rear = temp;
    }
    matrix.push_back(head);
}

void printMatrix(vector<NodePtr>& matrix, int m, int n){
    for(int i = 0; i < m; i++){
        NodePtr current = matrix[i]->link;
        int j = 1;
        while(j <= n){
            if(current == nullptr || current->col != j)
                cout << "0" << " ";//if the i row j column is empty, we need to print 0 since the value zero is not save in the lnked list.
            else{
                cout << current->value << " ";
                current = current->link;
            }
            j++;
        }
        cout << endl;
    }
}

void releaseMem(vector<NodePtr>& matrix, int m, int n){
    for(int i = 0; i < m; i++){
        NodePtr current = matrix[i];
        while(current != nullptr){
            NodePtr temp = current;
            current = current->link;
            delete temp;
        }
    }
}

void matrixAdd(vector<NodePtr>& matrix_A, vector<NodePtr>& matrix_B, vector<vector<int>>& resAdd, int m, int n){
    for(int i = 0; i < m; i++){
        NodePtr current1 = matrix_A[i]->link;
        NodePtr current2 = matrix_B[i]->link;
        //if the linked list is not point to the nullptr
        //compare the the indices of the column, if the column of A(or b) is smaller save the value to resAdd.
        //if the indices of the column are equal, sum the value and save IT to resAdd.
        while(current1 != nullptr && current2 != nullptr){
            if(current1->col < current2->col){
                resAdd[i][current1->col - 1] = current1->value;
                current1 = current1->link;
            }
            else if(current1->col > current2->col){
                resAdd[i][current2->col - 1] = current2->value;
                current2 = current2->link;
            }
            else{
                resAdd[i][current1->col - 1] = current1->value + current2->value;
                current1 = current1->link;
                current2 = current2->link;
            }
        }
        while(current1 != nullptr){
            resAdd[i][current1->col - 1] = current1->value;
            current1 = current1->link;
        }
        while(current2 != nullptr){
            resAdd[i][current2->col - 1] = current2->value;
            current2 = current2->link;
        }
    }
}

vector<vector<int>> matrixMultiply(vector<NodePtr>& matrix_A, vector<NodePtr>& matrix_B, int l, int m, int n){
    vector<vector<int>> result(l, vector<int>(n, 0));
    
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < n; j++) {
            NodePtr current1 = matrix_A[i]->link;
            NodePtr current2 = matrix_B[j]->link;
            //compare the indices of the column, if they are equal, multiply the value of matrix A with matrix B 
            //and save it to result and return it to main funciton
            while (current1 != nullptr && current2 != nullptr){
                if(current1->col < current2->col)
                    current1 = current1->link;
                else if(current1->col > current2->col)
                    current2 = current2->link;
                else{
                    result[i][j] += current1->value * current2->value;
                    current1 = current1->link;
                    current2 = current2->link;
                }
            }
        }
    }
    
    return result;
}

vector<NodePtr> transpose(vector<NodePtr>& matrix, int m, int n){
    vector<NodePtr> newMatrix;

    for(int i = 1; i <= n; i++){
        NodePtr head = new Node;
        NodePtr rear = head;
        head->link = nullptr;
        //reverse the value of column and row.
        for(int j = 0; j < m; j++){
            NodePtr cur = matrix[j]->link;
            while(cur != nullptr){
                if(cur->col == i){
                    NodePtr temp = new Node;
                    temp->col = j + 1;
                    temp->value = cur->value;
                    temp->link = nullptr;
                    rear->link = temp;
                    rear = temp;
                }
                cur = cur->link;
            }
        }
        newMatrix.push_back(head);
    }
    return newMatrix;
}