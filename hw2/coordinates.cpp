// Young0Bin Byun
// FSUID: YB23E
// EMPLID: 201093220

#include <iostream>
using namespace std;

// class Node{
// public:
//     Node(){
//         x = 0;
//         y = 0;
//         isLeaf = true;
//         TopLeft = NULL;
//         TopRight = NULL;
//         BottomLeft = NULL;
//         BottomRight = NULL;
//     };
//     Node(float x_in, float y_in){
//         x = x_in;
//         y = y_in;
//         isLeaf = true;
//         TopLeft = NULL;
//         TopRight = NULL;
//         BottomLeft = NULL;
//         BottomRight = NULL;
//     };
//     float x(){
//         return x;
//     }
//     float y(){
//         return y;
//     }
//     bool get_isLeaf(){
//         return isLeaf;
//     }
//     void set_x(float x_in){
//         x = x_in;
//     }
//     void set_y(float y_in){
//         y = y_in;
//     }
//     void set_isLeaf(bool isLeaf_in){
//         isLeaf = isLeaf_in;
//     }

// private:
//     float x;
//     float y;
//     bool isLeaf;
//     Node *TopLeft;
//     Node *TopRight;
//     Node *BottomLeft;
//     Node *BottomRight;
// };

struct Node{
    float x;
    float y;
    bool isLeaf;
    struct Node *TopLeft;
    struct Node *TopRight;
    struct Node *BottomLeft;
    struct Node *BottomRight;
} ;

class QuadTree{
public:
    QuadTree(){
        side = 0;
    };
    QuadTree(float side_in){
        side = side_in;
    };

    int findQuadrant(struct Node* n, float limit){
        if((limit/2 > n->x) && (limit/2 > n->y)){
            return 1;
        }
        else if((limit/2 < n->x) && (limit/2 > n->y)){
            return 2;
        }
        else if((limit/2 > n->x) && (limit/2 < n->y)){
            return 3;
        }
        else if((limit/2 < n->x) && (limit/2 < n->y)){
            return 4;
        }
    }

    void insert(Node* n, float limit, Node *Location){
        if(!root->isLeaf){
            root = n;
        }
        else
        {
            // need to split
            int newQuadrantforNode = findQuadrant(n,limit);
            int newQuadrantforRoot = findQuadrant(root,limit);

            if(newQuadrantforNode == 1){
                // insert to TopLeft
                insert(n, limit/2, n->TopLeft);
            }
            else if(newQuadrantforNode == 2){
                // insert to TopRight
                insert(n, limit/2, n->TopRight);
            }
            else if(newQuadrantforNode == 3){
                // insert to BottomLeft
                insert(n, limit/2, n->BottomLeft);
            }
            else if(newQuadrantforNode == 4){
                // insert to BottomRight
                insert(n, limit/2, n->BottomRight);
            }

            if(newQuadrantforRoot == 1){
                // insert to TopLeft
                insert(n, limit/2, n->TopLeft);31
            }
            else if(newQuadrantforRoot == 2){
                // insert to TopRight
                insert(n, limit/2, n->TopRight);
            }
            else if(newQuadrantforRoot == 3){
                // insert to BottomLeft
                insert(n, limit/2, n->BottomLeft);
            }
            else if(newQuadrantforRoot == 4){
                // insert to BottomRight
                insert(n, limit/2, n->BottomRight);
            }
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
        tree.insert(&n, side);
    }
}

