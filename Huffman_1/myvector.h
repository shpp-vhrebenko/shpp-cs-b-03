#pragma once
#include <iostream>

using namespace std;
// Реализация вектора на основе создания динамического масива.
template<class T>
class MyVector{
private:
    int vsize, vcapacity;
    T* ptr_array;
    void reAllocMem();

public:

    // Class iterator------------------------------------------------------------------
    class my_iterator{
    private:
        T * ptr;
    public:
        my_iterator(){}
        my_iterator(T * ptrVec) : ptr(ptrVec){}

        T & operator*(){
            return *ptr;
        }

        T * operator->(){
            return ptr;
        }

        my_iterator & operator++(){
            ++ptr;
            return *this;
        }

        my_iterator & operator++(int){
            my_iterator tmp = *this;
            ++ptr;
            return tmp;
        }

        my_iterator & operator--(){
            --ptr;
            return *this;
        }

        my_iterator & operator--(int){
            my_iterator tmp = *this;
            --ptr;
            return tmp;
        }

        bool operator==(my_iterator it){
            return ptr == it.ptr;
        }

        bool operator!=(my_iterator it){
            return ptr != it.ptr;
        }

    };

    my_iterator begin();
    my_iterator end();

    //-----------------------------------------------------------------------------------------

    // Constructors
    MyVector();
    MyVector(int size);
    MyVector(int size ,const T value);

    // Copy constructor
    MyVector(const MyVector<T>& sourceVec);


    // Destructor
    ~MyVector();

    // SubVector-------------------------------------------------------------------------------
    MyVector & subVector(int index, int length);

    // Operators-------------------------------------------------------------------------------

    MyVector & operator = (const MyVector<T> & sourceVec);
    T& operator[] (int i)const;
    bool operator==(MyVector const & vec);
    bool operator!=(MyVector const & vec);

    // Methods---------------------------------------------------------------------------------
    void add(const T &new_elem);
    void push_back(const T &new_elem);
    void pop_back();

    void insert(int index,const T & value);
    void remove(int index);


    bool isEmpty();
    bool isEqual(MyVector const & vector);
    int size();
    int capacity();


};


template<class T>
MyVector<T>::MyVector():vsize(0),vcapacity(1){
    ptr_array=new T[vcapacity];
}

template<class T>
MyVector<T>::MyVector(int size):vsize(size),vcapacity(size){
    ptr_array=new T[vcapacity];
}

template<class T>
MyVector<T>::MyVector(const MyVector& sourceVec){
    vsize=sourceVec.vsize;
    vcapacity=sourceVec.vcapacity;
    ptr_array=new T[vcapacity];
    for(int i=0;i<vsize;i++)
        ptr_array[i]=sourceVec.ptr_array[i];
}

template<class T>
MyVector<T>::MyVector(int size ,const T value){
    vsize = size;
    vcapacity = size;
    ptr_array = new T[size];
    for(int i = 0;i<size;i++){
        ptr_array[i] = value;
    }
}


template<class T>
MyVector<T>::~MyVector(){
    delete [] ptr_array;
}

template<class T>
void MyVector<T>::push_back(const T &new_elem){
    if(vsize==vcapacity)
        reAllocMem();
    ptr_array[vsize]=new_elem;
    vsize++;
}

template<class T>
T& MyVector<T>::operator[] (int i)const
{
    return ptr_array[i];
}

template<class T>
bool MyVector<T>::operator==(MyVector const & vec){
    return isEqual(vec);
}

template<class T>
bool MyVector<T>::operator!=(MyVector const & vec){
    return !isEqual(vec);
}

template<class T>
int MyVector<T>::size(){
    return vsize;
}

template<class T>
int MyVector<T>::capacity(){
    return vcapacity;
}

template<class T>
void MyVector<T>::reAllocMem(){
    vcapacity *= 2;
    T* ptr_tmp = new T[vcapacity];
    for(int i=0;i<vsize;i++)
        ptr_tmp[i]=ptr_array[i];
    delete[] ptr_array;
    ptr_array=ptr_tmp;
}

template <typename T>
void MyVector<T>::pop_back() {
    vsize--;
}

template <typename T>
void MyVector<T>::add(const T &elem){push_back(elem);}

template <typename T>
void MyVector<T>::insert(int index,const T & value){
    if(vsize==vcapacity){
        reAllocMem();
    }
    int tmpSize = vsize - index;
    T * tmp = new T [tmpSize];
    for(int i = 0, j = index; i < tmpSize; ++i, ++j){
        tmp[i] = ptr_array[j];
    }
    ptr_array[index] = value;
    ++vsize;
    ++index;
    for(int i = index, j = 0; i < vsize; ++i, ++j){
        ptr_array[i] = tmp[j];
    }
    delete [] tmp;

}

template <typename T>
void MyVector<T>::remove(int index){
    int j = index;
    for(int i = ++index; i < vsize; ++i){
        ptr_array[j] = ptr_array[i];
        ++j;
    }
    --vsize;
}

template <typename T>
bool MyVector<T>::isEmpty(){
    return vsize == 0;
}

template <typename T>
bool MyVector<T>::isEqual(MyVector const & vector){
    if(vsize != vector.vsize)
        return false;
    for(int i = 0, j = 0; i < vsize; ++i){
        if(ptr_array[i] != vector.ptr_array[j])
            return false;
    }
    return true;
}

template <typename T>
typename MyVector<T>::MyVector & MyVector<T>::operator = (const MyVector<T> & sourceVec){
    if(ptr_array != sourceVec.ptr_array){
        delete [] ptr_array;
        vsize = sourceVec.vsize;
        vcapacity = sourceVec.vcapacity;
        ptr_array = new T[sourceVec.vsize];
        for(int i(0);i < vsize;i++){
            ptr_array[i] = sourceVec[i];
        }

    }

    return *this;
}

template <typename T>
typename MyVector<T>::MyVector & MyVector<T>::subVector(int index, int length){
    MyVector<T> *subVec = new MyVector<T>(length);
    for (int i = 0; i < length; ++i){
        subVec->ptr_array[i] = ptr_array[index];
        ++index;
    }
    return *subVec;
}

template <typename T>
typename MyVector<T>::my_iterator  MyVector<T>::begin(){
    return my_iterator(ptr_array);
}

template <typename T>
typename MyVector<T>::my_iterator  MyVector<T>::end(){
    return my_iterator(ptr_array + vsize);
}

 //Override operator input output-----------------------------------------------------------
template<class T>
std::istream& operator>>(std::istream & stream, MyVector<T> & vec){
    for (int i = 0; i < vec.size(); ++i){
        stream >> vec[i];
    }
    return stream;
}

template<class T>
std::ostream& operator<<(std::ostream & stream, MyVector<T> & vec){
    stream << "[";
    for (int i = 0; i < vec.size() - 1; ++i){
        stream << vec[i] << ", ";
    }
    stream << vec[vec.size() - 1] << "]";
    return stream;
}

