#pragma once
#include <conio.h>
#include <cstdlib>

using namespace std;

// The implementation of a doubly linked list of line types (LIFO/FIFO).
template<class T>
class MyDualLinkList{
    class Node{
    public:
        T value;// data field
        Node *prev;// a pointer to the previous element
        Node *next;// a pointer to the next element


        //get index of list's node


    };
    Node* head, *tail;
    int count;

   // Metods of sort.
    void merge(Node *a, Node *b, Node **c);
    void split(Node *src, Node **low, Node **high);
    void mergeSort(Node **head);


    int getIndex(Node * ptr){
        int index = 0;
        while (ptr->prev != nullptr) {
            ptr = ptr->prev;
            ++index;
        }
        return index;
    }
public:

    // Default constructor----------------------------------------------------------------
    MyDualLinkList();

    // The copy constructor
    MyDualLinkList(const MyDualLinkList& sourceList);

    // The assignment operator
    MyDualLinkList & operator=(const MyDualLinkList & list);

    //Destructor
    ~MyDualLinkList();

    //-------------------------------------------------------------------------------------

    // Class iterator.---------------------------------------------------------------------
    class const_iterator{
    private:
        const Node * itPtr;
    public:
        const_iterator()
            : itPtr(0){}
        const_iterator (Node *n)
            : itPtr(n){}


        T operator*(){
            return itPtr->value;
        }

        const_iterator & operator++(){
            itPtr = itPtr->next;
            return *this;
        }

        const_iterator & operator++(int){
            const_iterator tmp = *this;
            itPtr = itPtr->next;
            return tmp;
        }

        const_iterator & operator--(){
            itPtr = itPtr->previous;
            return *this;
        }

        const_iterator & operator--(int){
            const_iterator tmp = *this;
            itPtr = itPtr->previous;
            return tmp;
        }

        bool operator==(const_iterator const & it){
            return itPtr == it.itPtr;
        }

        bool operator!=(const_iterator const & it){
            return itPtr != it.itPtr;
        }
    };



    class iterator{
    private:
        Node * itPtr;
    public:
        iterator(): itPtr(0){}
        iterator(Node * n): itPtr(n){}

        Node * get(int index = 0){
            for (int i = 0; i < index; ++i){
                if (itPtr->next != 0){
                    itPtr = itPtr->next;
                }
                else
                    return itPtr->next;
            }
            return itPtr;
        }


        T & operator*(){
            return itPtr->value;
        }

        T * operator->(){
            return itPtr->value;
        }

        iterator & operator++(){
            itPtr = itPtr->next;
            return *this;
        }

        iterator & operator++(int){
            iterator tmp = *this;
            itPtr = itPtr->next;
            return tmp;
        }

        iterator & operator--(){
            itPtr = itPtr->prev;
            return *this;
        }

        iterator & operator--(int){
            iterator tmp = *this;
            itPtr = itPtr->prev;
            return tmp;
        }

        bool operator==(iterator const & it){
            return itPtr == it.itPtr;
        }

        bool operator!=(iterator const & it){
            return itPtr != it.itPtr;
        }
    };


    // iterator start list
    iterator begin();

    // iterator end list
    iterator end();

    // const iterator start list
    const_iterator const_begin()const;

    // const iterator end list
    const_iterator const_end()const;

    //-----------------------------------------------------------------------------------------

    // Adding an item to the top of the list
    void push_front(T i);

    // Adding an element to the end of the list
    void push_back(T i);

    // Displays a list
    void show();

    // Removing an item from the top of the list
    void pop_front();

    // Removing an item from the end of the list.
    void pop_back();

    // Insert elements in the middle of the list.
    void insert(int index,const T & value);

    // Removing Elements from the middle of the list
    void erase(int index);

    // SubList
    MyDualLinkList & subList(int index, int length);

    // Is the list empty.
    bool empty();

    // The number of elements of the list
    int size();

    // Clear list.
    void clear();

    // Is list equal another list.
    bool isEqual(MyDualLinkList const & list);

    // getting the elemnt in the list on the index
    T & get(int index);

    // Setting elemnt by index
    void set(int index, T value);

    // Get a reference to the first item in the list.
    T & front(){
        return head->value;
    }

    // Sort doubly linked list.
//    void sort(){
//        mergeSort(&head);
//    }
    MyDualLinkList & sort();

    // Overloaded operators---------------------------------------------------------------------

    T & operator[](int i);

    bool operator==(MyDualLinkList const & list);

    bool operator!=(MyDualLinkList const & list);

};
template<class T>
std::istream& operator>>(std::istream & stream, MyDualLinkList<T> & list){
    for (int i = 0; i < list.size(); ++i){
        stream >> list.get(i);
    }
    return stream;
}

template<class T>
std::ostream& operator<<(std::ostream & stream, MyDualLinkList<T> & list){
    stream << "(";
    for (int i = 0; i < list.size() - 1; ++i){
        stream << list.get(i) << ", ";
    }
    stream << list.get(list.size() - 1) << ")";
    return stream;
}

template<class T>
MyDualLinkList<T>::MyDualLinkList(){
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<class T>
MyDualLinkList<T>::MyDualLinkList(const MyDualLinkList & sourceList): head(nullptr),tail(nullptr)
{
    Node *tmp = sourceList.head;
    while(tmp != nullptr){

        this->push_back(tmp->value);
        tmp = tmp->next;
    }
}

template<class T>
typename MyDualLinkList<T>::MyDualLinkList & MyDualLinkList<T>::operator=(const MyDualLinkList & list){
    if(this != &list){
        clear();
        head = 0;
        tail = 0;
        count = 0;
        Node * current = list.head;
        for(int i = 0; i < list.count; ++i){
            push_back(current->value);
            current = current->next;
        }

    }
    return *this;
}

template<class T>
MyDualLinkList<T>::~MyDualLinkList(){
    while(head != nullptr){
        Node *temp = head->next;
        delete head;
        head = temp;
    }
}


template<class T>
typename MyDualLinkList<T>::iterator MyDualLinkList<T>::begin(){
    return iterator(head);
}

template<class T>
typename MyDualLinkList<T>::iterator MyDualLinkList<T>::end() {
    return iterator(tail->next);
}

template<class T>
typename MyDualLinkList<T>::const_iterator MyDualLinkList<T>::const_begin() const{
    return const_iterator(head);
}

template<class T>
typename MyDualLinkList<T>::const_iterator MyDualLinkList<T>::const_end() const{
    return const_iterator(tail->next);
}

template<class T>
void MyDualLinkList<T>::push_front(T i){
    Node *tmp = new Node;
    tmp->value = i;
    if(head == nullptr){
        tmp->next = nullptr;
        tmp->prev = nullptr;
        head = tmp;
        tail = tmp;
    }
    else{
        tmp->next =head;
        tmp->prev = nullptr;
        head->prev = tmp;
        head = tmp;

    }

    count++;
}

template<class T>
void MyDualLinkList<T>::push_back(T i){
    Node *tmp = new Node;
    tmp->value = i;
    tmp->next = nullptr;
    if(head==nullptr){
        head = tail = tmp;
    }
    else{
        tail->next=tmp;
        tmp->prev=tail;
        tail = tmp;
    }
    count++;
}

template<class T>
void MyDualLinkList<T>::show(){
    Node *temp = head;
    while(temp != nullptr){
        cout<<temp -> value<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

template<class T>
void MyDualLinkList<T>::pop_front(){
    if(empty()){
        cout<<"Empty List!!!"<<endl;
        exit(EXIT_FAILURE);
    }
    else{
        Node *temp = head->next;
        if(size()>1){
            delete head;
            head = temp;
            temp->prev = nullptr;
            count--;
        }
        else{
            delete head;
            head = nullptr;
            tail = nullptr;
            count = 0;
        }
    }
}

template<class T>
void MyDualLinkList<T>::pop_back(){
    if(empty()){
        cout<<"Empty List!!!"<<endl;
        exit(EXIT_FAILURE);
    }
    else{
        if(size()>1){
            Node *temp;
            temp = tail->prev;
            temp->next=nullptr;
            delete tail;
            tail = temp;
            count--;
        }
        else{
            delete tail;
            head = nullptr;
            tail = nullptr;
            count = 0;
        }

    }


}

template<class T>
bool MyDualLinkList<T>::empty() {
    return (size() == 0);
}

template<class T>
int MyDualLinkList<T>::size(){
    return count;
}

template<class T>
void MyDualLinkList<T>::insert(int index,const T & value){
    if (index == 0){
        push_front(value);
        return;
    }
    if (index >= (count - 1)){
        push_back(value);
        return;
    }
    iterator it = begin();
    Node * current = it.get(index);
    Node * insertNode = new Node;
    insertNode->value = value;
    insertNode->prev = current->prev;
    current->prev->next = insertNode;
    current->prev = insertNode;
    insertNode->next = current;
    ++count;
}

template<class T>
void MyDualLinkList<T>::erase(int index){
    if(empty()){
        cerr<<"Error [remove].Empty List!!!The program will be clossed."<<endl;
        exit(EXIT_FAILURE);
    }
    if (index == 0){
        pop_front();
        return;
    }
    if (index == (count - 1)){
        pop_back();
        return;
    }
    iterator it = begin();
    Node * current = it.get(index);
    if (current != 0){
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete  current;
        --count;
    }
}

template<class T>
typename MyDualLinkList<T>::MyDualLinkList & MyDualLinkList<T>::subList(int index, int length){
    if ((length + index) > count){
        length = count - index;
    }
    MyDualLinkList<T> * subList = new MyDualLinkList<T>;
    iterator it = begin();
    it.get(index);
    for (int i = 0; i < length; ++i){
        subList->push_back(it.get()->value);
        ++it;
    }
    return *subList;

}



template<class T>
void MyDualLinkList<T>::clear() {
    while(!empty())
        pop_back();
}


template<class T>
bool MyDualLinkList<T>::isEqual(MyDualLinkList const & list){
    if(this->count != list.count)
        return false;

    for(const_iterator lIt = const_begin(), rIt = list.const_begin(); lIt != const_end(); ++lIt, ++rIt){
        if(*lIt != *rIt)
            return false;
    }
    return true;
}


template<class T>
T & MyDualLinkList<T>::get(int index){
    iterator it = begin();
    if (it.get(index) == nullptr){
        std::cerr << "Error [get].You try get nonexistent element. The program will be clossed";
        exit (EXIT_FAILURE);
    }
    return *it;
}

template<class T>
void  MyDualLinkList<T>::set(int index, T value){
    iterator it = begin();
    Node * current = it.get(index);
    if (current == nullptr){
        std::cerr << "Error [set].You try set value to nonexistent element. The program will be clossed";
        exit (EXIT_FAILURE);
    }
    current->value = value;
}

template<class T>
T & MyDualLinkList<T>::operator[](int i){
    return get(i);
}

template<class T>
bool MyDualLinkList<T>::operator==(MyDualLinkList const & list){
    return isEqual(list);
}

template<class T>
bool MyDualLinkList<T>::operator!=(MyDualLinkList const & list){
    return !isEqual(list);
}

template<class T>
void MyDualLinkList<T>::merge(Node *a, Node *b, Node **c) {
    Node tmp;
    *c = NULL;
    if (a == NULL) {
        *c = b;
        return;
    }
    if (b == NULL) {
        *c = a;
        return;
    }
    if (a->value < b->value) {
        *c = a;
        a = a->next;
    } else {
        *c = b;
        b = b->next;
    }
    tmp.next = *c;
    while (a && b) {
        if (a->value < b->value) {
            (*c)->next = a;
            a = a->next;
        } else {
            (*c)->next = b;
            b = b->next;
        }
        (*c) = (*c)->next;
    }
    if (a) {
        while (a) {
            (*c)->next = a;
            (*c) = (*c)->next;
            a = a->next;
        }
    }
    if (b) {
        while (b) {
            (*c)->next = b;
            (*c) = (*c)->next;
            b = b->next;
        }
    }
    *c = tmp.next;
}

template<class T>
void MyDualLinkList<T>::split(Node *src, Node **low, Node **high) {
      Node *fast = NULL;
      Node *slow = NULL;

      if (src == NULL || src->next == NULL) {
          (*low) = src;
          (*high) = NULL;
          return;
      }

      slow = src;
      fast = src->next;

      while (fast != NULL) {
          fast = fast->next;
          if (fast != NULL) {
              fast = fast->next;
              slow = slow->next;
          }
      }

      (*low) = src;
      (*high) = slow->next;
      slow->next = NULL;
  }

template<class T>
void MyDualLinkList<T>::mergeSort(Node **head) {
        Node *low  = NULL;
        Node *high = NULL;
        if ((*head == NULL) || ((*head)->next == NULL)) {
            return;
        }
        split(*head, &low, &high);
        mergeSort(&low);
        mergeSort(&high);
        merge(low, high, head);
    }

//template<class T>
//void MyDualLinkList<T>::sort(){
//    Node *cur=head;
//    while(cur->next)
//    {
//        if((cur->value)>(cur->next->value))
//        {
//            //обмен
//            T tmp = cur->next->value;
//            cur->next->value = cur->value;
//            cur->value = tmp;

//            cur=cur->next;
//            sort();
//        }
//        else {cur=cur->next;}


//    }
//}


