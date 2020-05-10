//
// Created by Mini Luo on 10/2/19.
//

#ifndef UNTITLED4_LINKEDLIST_H
#define UNTITLED4_LINKEDLIST_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

template<typename T>
class LinkedList {
public:
    class Node {
    public:
        T data;
        Node *prev;
        Node *next;
    };

    /*====Behaviors====*/
    void PrintForward() const {
        Node *printer = head;
        while (printer!= nullptr) {
            cout << printer->data << endl;
            printer = printer->next;
        }
        //delete printer;
    }

    void PrintReverse() const {
        Node *printer = tail;
        while (printer!= nullptr) {
            cout << printer->data << endl;
            printer = printer->prev;
        }
        delete printer;
    }

    void PrintForwardRecursive(const Node *node) const {
        cout << node->data << endl;
        while (node->next != nullptr) {
            node=node->next;
            cout << node->data << endl;
            //PrintForwardRecursive(node);
        }
    }

    void PrintReverseRecursive(const Node *node) const {
        cout << node->data << endl;
        while (node->prev != nullptr) {
            node=node->prev;
            cout << node->data << endl;
            //PrintReverseRecursive(node);
        }
    }

    /*====Accessors====*/
    unsigned int NodeCount() const {
        /*count=0;
        Node* counter=head;
        while(counter!= nullptr){
            count++;
            counter->next;
        }*/
        return count1;
    }

    void FindAll(vector<Node*> &outData, const T &value) const {
        Node *found = head;
        while (found != nullptr) {
            if (found->data == value) {
                outData.push_back(found);
            }
            found = found->next;
        }
    }

    const Node *Find(const T &data) const {
        Node *finder = head;
        for (unsigned int i = 0; i < count1; i++) {
            if (finder == data) {
                return finder;
            }
            finder = finder->next;
        }
        return nullptr;

    }

    Node *Find(const T &data) {
        Node *finder = head;
        for (unsigned int i = 0; i < count1; i++) {
            if (finder->data == data) {
                return finder;
            }
            finder = finder->next;
        }
        return nullptr;
    }

    const Node *GetNode(unsigned int index) const {
        Node *getter = head;
        if (index < count1) {
            //unsigned int counter2;

            for (unsigned int i = 0; i < count1; i++) {
                if (i == index) {
                    return getter;
                } else {
                    getter = getter->next;
                }
            }
        } else {
            string error = "Index is out of range.";
            throw error;
        }
        return getter;
    }

    Node *GetNode(unsigned int index) {
        Node *getter = head;
        if (index < count1) {
            //unsigned int counter2;

            for (unsigned int i = 0; i < count1; i++) {
                if (i == index) {
                    return getter;
                } else {
                    getter = getter->next;
                }
            }
        } else {
            string error = "Index is out of range.";
            throw error;
        }
        return getter;
    }

    Node *Head() {
        return head;
    }

    const Node *Head() const {
        return head;
    }

    Node *Tail() {
        return tail;
    }

    const Node *Tail() const {
        return tail;
    }

    /*==== Insertion====*/
    void AddHead(const T &data) {
        Node *addNode = new Node();
        addNode->data = data;
        if(head!= nullptr){
            addNode->next= head;
            addNode->prev= nullptr;
            head->prev=addNode;
            if (count1==0){
                tail->prev=addNode;
            }
            head=addNode;
        }else{
            head=addNode;
            tail=addNode;
        }

        //addNode->prev = prevPoint;
        //pointHead->prev = addNode;

        count1++;


    }

    void AddTail(const T &data) {
        Node *addNode = new Node();
        addNode->data = data;
        addNode->next= nullptr;
        addNode->prev= nullptr;
        if(tail!= nullptr){
            addNode->prev= tail;
            addNode->next= nullptr;
            tail->next=addNode;
            if (count1==1){
                head->next=addNode;
                addNode->prev=head;
            }
            tail=addNode;
        }else{
            head=addNode;
            addNode->prev= nullptr;
            tail=addNode;
            addNode->next= nullptr;
        }
        count1++;

    }

    void AddNodesHead(const T *data, unsigned int count) {
        unsigned int actualCount=count-1;
        for (unsigned int i = actualCount; i >0; i--) {
            AddHead(data[i]);
            count1++;
        }
        count1++;
        AddHead(data[0]);//why does it not work with i>=0?


    }

    void AddNodesTail(const T *data, unsigned int count) {
        //unsigned int count2=count;
        for (unsigned int i = 0; i < count; i++) {
            AddTail(data[i]);
            count1++;
        }


    }

    void InsertAfter(Node *node, const T &data) {
        Node *temp = new Node();
        Node *next = node->next;
        temp->data = data;
        temp->prev = node;
        temp->next = next;
        node->next = temp;
        next->prev = temp;
        count1++;

    }

    void InsertBefore(Node *node, const T &data) {
        Node *temp = new Node();
        Node *before = node->prev;
        temp->data = data;
        temp->next = node;
        temp->prev=before;
        node->prev = temp;
        before->next = temp;
        count1++;

    }

    void InsertAt(const T &data, unsigned int index) {
        if (index <=count1) {
            Node *insert = new Node();
            insert->data = data;
            Node *place = head;
            for (unsigned int i = 0; i <=index; i++) {
                if(i==index){
                    if(index==0){
                        insert->next= head;
                        insert->prev= nullptr;
                        head->prev=insert;
                        if (count1==0){
                            tail->prev=insert;
                        }
                        head=insert;
                        count1++;
                    }else if(index==count1){
                        insert->prev= tail;
                        insert->next= nullptr;
                        tail->next=insert;
                        if (count1==0){
                            head->next=insert;
                        }
                        tail=insert;
                        count1++;

                    }else{
                        Node* before=place->prev;
                        insert->next = place;
                        insert->prev=before;
                        place->prev = insert;
                        before->next=insert;
                        count1++;

                    }


                    break;
                }
                place = place->next;
            }

        } else {
            string error = "Index is out of range.";
            throw error;
        }

    }

    /*====Removal====*/
    bool RemoveHead() {
        if (NodeCount() == 0) {
            return false;
        } else if (head->next == nullptr) {
            delete head;
            head= nullptr;
            tail= nullptr;
            count1--;
            return true;
        } else {
            Node *ref = head;
            Node *temp=head->next;
            temp->prev = nullptr;
            delete ref;
            head = temp;
            count1--;
            return true;
        }

    }

    bool RemoveTail() {
        if (NodeCount() == 0) {
            return false;
        } else if (tail->prev == nullptr) {
            delete tail;
            count1--;
            head= nullptr;
            tail= nullptr;
            return true;
        } else {
            Node *ref = tail;
            Node *temp=tail->prev;
            temp->next = nullptr;
            delete ref;
            tail = temp;
            count1--;
            return true;
        }

    }

    unsigned int Remove(const T &data) {
        unsigned int removeCounter = 0;
        Node *finder = head;
        Node *temp;
        for (unsigned int i = 0; i < count1; i++) {
            if (finder->data == data) {
                temp=finder->prev;
                finder=finder->next;
                delete finder->prev;
                finder->prev=temp;
                temp->next =finder;
                removeCounter++;
            }else {
                finder = finder->next;
            }
        }
        count1-=removeCounter;
        //cout<<count<<endl;
        return removeCounter;

    }

    bool RemoveAt(int index) {
        if ((unsigned int)index > count1) {
            return false;
        }
        Node *remove = head;
        Node *temp;
        //Node *temp2;
        if (index == 0) {
            remove=remove->next;
            temp=remove->next;
            delete remove->prev;
            count1--;
            //head=remove;
            remove->prev= nullptr;
            remove->next =temp;
            return true;
        } else {
            for (int i = 0; i <=index; i++) {
                if (i== index) {
                    temp=remove->prev;
                    //temp2=remove->next->next;
                    remove=remove->next;
                    delete remove->prev;
                    count1--;
                    remove->prev=temp;
                    temp->next =remove;
                    //remove->next=temp2;
                    //temp2->prev=remove;
                    break;
                }else {
                    remove = remove->next;
                }
            }
            return true;
        }
    }

    void Clear() {
        while(RemoveTail()==true){
            RemoveTail();
        }
        tail=nullptr;
        head=nullptr;
        count1=0;
    }

    /*====Operators ====*/
    const T &operator[](unsigned int index) const {
        Node *temp = head;
        for (unsigned int i = 0; i < index; i++) {
            temp = temp->next;

        }
        return temp->data;
    }

    T &operator[](unsigned int index) {
        Node *temp = head;
        for (unsigned int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;

    }

    bool operator==(const LinkedList<T> &rhs) const {
        bool same = true;
        if (rhs.count1 != count1) {
            return false;
        } else {
            Node *temp = rhs.head;
            Node *temp2 = this->head;
            //T rhsData = temp->data;
            //T tempData = temp2->data;
            for (unsigned int i = 0; i < count1; i++) {

                if (temp->data != temp2->data) {
                    return false;
                }
                temp2=temp2->next;
                temp=temp->next;
                //tempData = temp2->data;
                //rhsData = temp->data;
            }

        }
        return same;

    }

    LinkedList<T> &operator=(const LinkedList<T> &rhs) {
        count1=0;
        //Node *listHead = rhs.Head();
        //Node* listTail=rhs.Tail();
        for(unsigned int i=0;i<rhs.NodeCount();i++){
            AddTail(rhs.GetNode(i)->data);
            /*if(i==rhs.NodeCount()-1){
                tail=rhs.GetNode(i)->data;
            }*/
        }

        return *this;

    }

    /*==== Construction/ Destruction ====*/
    LinkedList() {
        head = nullptr;
        tail = nullptr;



    }

    LinkedList(const LinkedList<T> &list) {

        //count1=0;
        Node* listHead = new Node();
        Node* listTail=new Node();
        listHead->prev=nullptr;
        listTail->next=nullptr;
        //Node* listTail=list.Tail();
        for(unsigned int i=0;i<list.NodeCount();i++){
            AddTail(list.GetNode(i)->data);
        }




    }
    ~LinkedList() {
        Clear();

    }

private:

    Node *head;
    Node *tail;
    unsigned int count1 = 0;

};





#endif //UNTITLED4_LINKEDLIST_H
