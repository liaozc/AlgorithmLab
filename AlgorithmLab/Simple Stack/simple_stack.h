#ifndef SIMPLE_STACK_H
#define SIMPLE_STACK_H

template<typename T>
class stack {

protected:
	T* data;
	int m_size;
	int m_curPointer;
	bool allocate(int size) 
	{
		if (size <= 0) return false;
		if (size <= m_size) return true;
		T* newdata = new T[size];
		if (!newdata) return false;
		if (data)
		{
			memcpy(data, newdata, sizeof(T)*m_size);
			delete[] data;
		}
		data = newdata;
		m_size = size;
		return true;
	}
public:
	stack() :data(nullptr), size(0), m_curPointer(-1) {}
	stack(int initSize) :data(nullptr), m_size(0),m_curPointer(-1)
	{
		allocate(initSize);
	}
	
	void push(T t) 
	{
		int pointer = m_curPointer + 1;
		if (pointer >= m_size) allocate(2 * m_size);
		if (pointer >= m_size) return;
		data[pointer] = t;
		++ m_curPointer;
	}
	
	void pop()
	{
		if (m_curPointer >= 0) m_curPointer--;
	}
	
	T top()
	{
		if (m_curPointer != -1)
			return data[m_curPointer];
		
		return T();
	}
	
	bool empty() const
	{
		return m_curPointer == -1;
	}

};


#endif