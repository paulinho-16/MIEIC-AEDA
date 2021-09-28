# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> valores;
    stack<T> minimos;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	return valores.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    T *novo = new T();
    *novo = valores.top();
    return *novo;
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    T temp = valores.top();
    valores.pop();
    if (minimos.top() == temp)
        minimos.pop();
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    valores.push(val);
    if (!minimos.empty()) {
        if (val <= minimos.top())
            minimos.push(val);
    }
    else {
        minimos.push(val);
    }
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    T *novo = new T();
    *novo = minimos.top();
    return *novo;
}

