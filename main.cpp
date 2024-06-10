// Integrantes 
// Chavez Ayme, Anthony
// Alferez Vicente, Bladimir
// Valdivia Schreiber, Mauricio Guillermo Manuel

#include <iostream>
using namespace std;

struct NodeBT {
    int data;
    NodeBT *left = nullptr;
    NodeBT *right = nullptr;
    NodeBT *padre = nullptr;
    NodeBT *next = nullptr;
};

class AVL{
public:
    NodeBT *root;

    AVL() {
        root = nullptr;
    }

    void insert(int value, NodeBT *treenode) {
        NodeBT *nodo = new NodeBT;
        nodo->data = value;
        if(!buscar(root, value)){
            if (root == nullptr) {
                root = nodo;
            } else {
                if (treenode->data > value) {
                    if (treenode->left == nullptr) {
                        treenode->left = nodo;
                        nodo->padre = treenode;
                    } else {
                        this->insert(value, treenode->left);
                    }
                } else {
                    if (treenode->right == nullptr) {
                        treenode->right = nodo;
                        nodo->padre = treenode;
                    } else {
                        this->insert(value, treenode->right);
                    }
                }
            }
    
            balance(nodo);
        }
    }

    void balance(NodeBT* nodo) {
        while (nodo != nullptr) {
            int balance = get_hb(nodo);
            if (balance > 1) {
                if (get_hb(nodo->left) < 0) {
                    nodo->left = rotate_left(nodo->left);
                }
                nodo = rotate_right(nodo);
            } else if (balance < -1) {
                if (get_hb(nodo->right) > 0) {
                    nodo->right = rotate_right(nodo->right);
                }
                nodo = rotate_left(nodo);
            }
            nodo = nodo->padre;
        }
    }

    NodeBT* rotate_left(NodeBT* x) {
        NodeBT* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->padre = x;
        }
        y->padre = x->padre;
        if (x->padre == nullptr) {
            root = y;
        } else if (x == x->padre->left) {
            x->padre->left = y;
        } else {
            x->padre->right = y;
        }
        y->left = x;
        x->padre = y;
        return y;
    }

    NodeBT* rotate_right(NodeBT* x) {
        NodeBT* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->padre = x;
        }
        y->padre = x->padre;
        if (x->padre == nullptr) {
            root = y;
        } else if (x == x->padre->right) {
            x->padre->right = y;
        } else {
            x->padre->left = y;
        }
        y->right = x;
        x->padre = y;
        return y;
    }

    void eliminar(int value) {
        NodeBT* nodo = buscarNodo(root, value);
        if (nodo == nullptr) return;  

        NodeBT* parent = nodo->padre;  

        if (nodo->left == nullptr || nodo->right == nullptr) {
            NodeBT* newChild = (nodo->left != nullptr) ? nodo->left : nodo->right;

            if (parent == nullptr) {  
                root = newChild;
            } else if (parent->left == nodo) {
                parent->left = newChild;
            } else {
                parent->right = newChild;
            }

            if (newChild != nullptr) {
                newChild->padre = parent;
            }

            delete nodo;
        } else { 
            NodeBT* successor = minValueNode(nodo->right);
            int successorValue = successor->data;
            eliminar(successor->data);  
            nodo->data = successorValue;  
        }

        if (parent != nullptr) {
            balance(parent);
        } else if (root != nullptr) {  
            balance(root);
        }
    }


    NodeBT* minValueNode(NodeBT* node) {
        NodeBT* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    NodeBT* buscarNodo(NodeBT* nodo, int value) {
        while (nodo != nullptr && nodo->data != value) {
            if (value < nodo->data) {
                nodo = nodo->left;
            } else if (value > nodo->data) {
                nodo = nodo->right;
            }
        }
        return nodo;
    }

    int get_hb(NodeBT* nodo) {
        return get_altura(nodo->left) - get_altura(nodo->right);
    }

    int get_altura(NodeBT* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        return 1 + max(get_altura(nodo->left), get_altura(nodo->right));
    }

    bool buscar(NodeBT* a, int elemento) {
        if (a == nullptr) {
            return false;
        } else {
            if (elemento > a->data) {
                return buscar(a->right, elemento);
            } else if (elemento < a->data) {
                return buscar(a->left, elemento);
            } else {
                return true;
            }
        }
    }

    void imprimirarbol(NodeBT* a, int cont = 0) {
        if (a == nullptr) {
            return;
        } else {
            imprimirarbol(a->right, cont + 1);
            for (int i = 0; i < cont; i++) {
                cout << "   ";
            }
            cout << a->data << endl;
            imprimirarbol(a->left, cont + 1);
        }
    }
};

int main() {
    AVL a;
    a.insert(20, a.root);
    a.insert(10, a.root);
    a.insert(30, a.root);
    a.insert(5, a.root);
    a.insert(15, a.root);
    a.insert(25, a.root);
    a.insert(35, a.root);
    a.insert(3, a.root);
    a.insert(8, a.root);
    a.insert(13, a.root);
    a.insert(18, a.root);
    a.insert(23, a.root);
    a.insert(28, a.root);
    a.insert(38, a.root);

    cout << "Altura del arbol: " << a.get_altura(a.root) << endl;
    cout << "Buscar un elemento no existente (10000): " << a.buscar(a.root, 10000) << endl;
    cout << "Factor de balance de la raiz: " << a.get_hb(a.root) << endl << endl;
    
    cout << "Arbol original:" << endl;
    a.imprimirarbol(a.root);
    cout << endl;

    cout << "Eliminar nodo con dos hijos (10):" << endl;
    a.eliminar(10);
    a.imprimirarbol(a.root);
    cout << endl;

    cout << "Eliminar nodo con un solo hijo (30):" << endl;
    a.eliminar(30);
    a.imprimirarbol(a.root);
    cout << endl;

    cout << "Eliminar nodo hoja (38):" << endl;
    a.eliminar(38);
    a.imprimirarbol(a.root);
    cout << endl;

    return 0;
}
