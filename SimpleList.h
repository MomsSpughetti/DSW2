#include "stdlib.h"

template <class Data>
struct SimpleNode{Data data; SimpleNode* next; SimpleNode(Data& data) : data(data), next(nullptr) {}};

template <class Data>
class Simplelist
{
    private:
        SimpleNode<Data>* FirstNode;
        SimpleNode<Data>* LastNode;
    public:
        Simplelist() = default;
        SimpleNode<Data>* getFirstNode() {return FirstNode;}
        SimpleNode<Data>* getLastNode() {return LastNode;}
        
        void push_back(Data& data) {
            if(First == nullptr){
                FirstNode = new SimpleNode(data);
                LastNode = FirstNode;
            } else {
                SimpleNode<Data>* newNode = new SimpleNode(data);
                LastNode->next = newNode;
                LastNode = newNode;
            }
        }
        ~Simplelist(){
            SimpleNode<Data>* temp = FirstNode, toDelete;
            while (temp)
            {
                toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
            
        }
};