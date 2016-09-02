#include <iostream>
using namespace std;

class binaryTree
{
public:
    binaryTree();
    ~binaryTree(){}
    binaryTree(const binaryTree& other){}
    binaryTree& operator=(const binaryTree& rhs){return *this;}
    void addNode(int value);
    bool deleteNode(int value);
    bool hasNode(int value) const;
    int max() const;
    int min() const;
    void print() const;
    int size() const{return m_size;}
private:
    struct Node
    {
        int m_value;
        Node* m_left;
        Node* m_right;
    };
    
    Node* m_root;
    int deleteNtime;
    int m_size;
    
    void print(const Node* tree) const;
    void find(Node*& deleteNode);
};


binaryTree::binaryTree():m_root(nullptr), deleteNtime(0)
{}

//TODO: Rule of three

void binaryTree::addNode(int value)
{
    Node* newNode = new Node;
    newNode->m_value = value;
    newNode->m_left = nullptr;
    newNode->m_right = nullptr;
    
    if(m_root == nullptr)
    {
        m_root = newNode;
        m_size++;
        return;
    }
    
    Node* p = m_root;
    
    while(true)
    {
        if(p->m_left == nullptr && value <= p->m_value)
        {
            p->m_left = newNode;
            m_size++;
            break;
        }
        
        if(p->m_right == nullptr && value > p->m_value)
        {
            p->m_right = newNode;
            m_size++;
            break;
        }
        
        if(value <= p->m_value)
            p = p->m_left;
        
        else
            p = p->m_right;
    }
}


bool binaryTree::deleteNode(int value)
{
    Node* curr = m_root;
    Node* prev = m_root;
    
    if(m_root == nullptr)
        return false;
    
    while(curr != nullptr && curr->m_value != value)
    {
        prev = curr;
        if(value <= curr->m_value)
            curr = curr->m_left;
        else
            curr = curr->m_right;
    }
    
    if(curr != nullptr)
    {
        if(curr->m_left == nullptr)
        {
            if(curr->m_right == nullptr)
            {
                if(curr == m_root)
                    m_root = nullptr;
                
                else if(curr->m_value <= prev->m_value)
                    prev->m_left = nullptr;
                else
                    prev->m_right = nullptr;
            }
            
            else
            {
                if(curr == m_root)
                    m_root = m_root->m_right;
                
                else if(curr->m_value <= prev->m_value)
                    prev->m_left = curr->m_right;
                else
                    prev->m_right = curr->m_right;
            }
            
            delete curr;
            m_size--;
            deleteNtime++;
            return true;
        }
        
        else if(curr->m_right == nullptr)
        {
            if(curr == m_root)
                m_root = m_root->m_left;
            
            else if(curr->m_value <= prev->m_value)
                prev->m_left = curr->m_left;
            else
                prev->m_right = curr->m_left;
            
            delete curr;
            m_size--;
            deleteNtime++;
            return true;
        }
        
        else
        {
            if(deleteNtime % 2 == 0)
            {
                Node* p = curr;
                prev = p;
                p = curr->m_left;
                while(p->m_right != nullptr)
                {
                    prev = p;
                    p = p->m_right;
                }
                
                if(prev == curr)
                    prev->m_left = p->m_left;
                
                else
                    prev->m_right = p->m_left;
                
                curr->m_value = p->m_value;
                delete p;
                m_size--;
                deleteNtime++;
                return true;
            }
            
            else
            {
                Node* p = curr;
                prev = p;
                p = curr->m_right;
                while(p->m_left != nullptr)
                {
                    prev = p;
                    p = p->m_left;
                }
                
                if(prev == curr)
                    prev->m_right = p->m_right;
                else
                    prev->m_left = p->m_right;
                
                curr->m_value = p->m_value;
                delete p;
                m_size--;
                deleteNtime++;
                return true;
            }
        }
    }
    
    return false;
}

bool binaryTree::hasNode(int value) const
{
    if(m_root == nullptr)
        return false;
    
    Node* p = m_root;
    while(p != nullptr && p->m_value != value)
    {
        if(value <= p->m_value)
            p = p->m_left;
    
        else
            p = p->m_right;
    }
    
    return !(p == nullptr);
}


void binaryTree::print() const
{
    if(m_root != nullptr)
        print(m_root);
}

void binaryTree::print(const Node* tree) const
{
    if(tree != nullptr)
    {
        cout << tree->m_value << endl;
        print(tree->m_left);
        print(tree->m_right);
    }
}


int main()
{
    binaryTree bt;
    bt.addNode(15);
    bt.addNode(7);
    bt.addNode(23);
    bt.addNode(3);
    bt.addNode(10);
    bt.addNode(20);
    bt.addNode(30);
    bt.addNode(2);
    bt.addNode(4);
    bt.addNode(13);
    bt.addNode(18);
    bt.addNode(22);
    bt.addNode(27);
    bt.addNode(35);
    bt.addNode(11);
    bt.addNode(14);
    bt.addNode(29);
    
    bt.print();
    cout << endl;
    
    
    bt.deleteNode(15);
    bt.print();
    
    if(!bt.hasNode(15))
        cout << "No" << endl;
    
    if(bt.hasNode(22))
        cout << "Yes" << endl;
    
}


















