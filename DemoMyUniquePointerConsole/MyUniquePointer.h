#pragma once

template <typename TypeName>
class MyUniquePointer final
{
public:
	// 1. Constructor
	MyUniquePointer(TypeName* addressPtr) : m_MyPointer(addressPtr)
	{}

	// 2. Disable copy behavior
	MyUniquePointer(const MyUniquePointer<TypeName>& other) = delete;
	MyUniquePointer<TypeName>& operator=(const MyUniquePointer<TypeName>& other) = delete;

	// 3. Implement move behavior: MyUniquePointer objects can be duplicated, 
	//							   but the duplicate takes over the address and the original set to zero
	MyUniquePointer(MyUniquePointer<TypeName>&& other) noexcept : m_MyPointer{ other.m_MyPointer }
	{
		other.m_MyPointer = nullptr;
	}
	MyUniquePointer<TypeName>& operator=(MyUniquePointer<TypeName>&& other)
	{
		if (this != &other)
		{
			m_MyPointer = other.m_MyPointer;
			other.m_MyPointer = nullptr;
		}
	}

	// 4. Destructor: very important, this is what it's all about
	~MyUniquePointer()
	{
		delete m_MyPointer;
	}

	// 5. Implement pointer operations, and just pass the operation on to the address
	TypeName* operator->()
	{
		return m_MyPointer;
	}

	MyUniquePointer<TypeName>& operator=(TypeName* addressPtr)
	{
		delete m_MyPointer;
		m_MyPointer = addressPtr;
	}

	TypeName* get()
	{
		return m_MyPointer;
	}

	void reset()
	{
		delete m_MyPointer;
		m_MyPointer = nullptr;
	}

	TypeName* release()
	{
		return m_MyPointer;
		m_MyPointer = nullptr;
	}

private:
	TypeName* m_MyPointer{};
};
