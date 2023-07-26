// Young0Bin Byun
// FSUID: YB23E
// EMPLID: 201093220

#include <iostream>
using namespace std;

class Node{
public:
    Node(){
        x = 0;
        y = 0;
        isLeaf = false;
        TopLeft = NULL;
        TopRight = NULL;
        BottomLeft = NULL;
        BottomRight = NULL;
    };
    Node(float x_in, float y_in){
        x = x_in;
        y = y_in;
        isLeaf = true;
        TopLeft = NULL;
        TopRight = NULL;
        BottomLeft = NULL;
        BottomRight = NULL;
    };

private:
    float x;
    float y;
    bool isLeaf;
    Node *TopLeft;
    Node *TopRight;
    Node *BottomLeft;
    Node *BottomRight;
};

class QuadTree{
public:
    QuadTree(){
        side = 0;
    };
    QuadTree(float side_in){
        side = side_in;
    };
    void insert(Node* n){
        if(root == NULL){
            root = n;
        }
    }
    void print(){
        // print all the Nodes in the tree in the post-order traversal
        // order - Top-Left, Top-Right, Bottom-Left, Bottom-Right

    };
private:
    float side;
    Node *root;
};

int main() {
    cout << "Enter the length of a side of the square: " ;
    float side;
    cin >> side;
    cout << "Enter the number of points: " ;
    int numPoints;
    cin >> numPoints;

    QuadTree tree(side);

    for(int i = 0 ; i < numPoints ; i++){
        float x;
        float y;
        cin >> x >> y;
        Node n(x, y);
        tree.insert(&n);
    }
}

