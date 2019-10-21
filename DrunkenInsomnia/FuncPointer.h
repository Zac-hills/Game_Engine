#pragma once
#include <utility>

template<typename ...ARGS>
class BasePointer
{
public:
	virtual ~BasePointer() {};
	void exe(ARGS &&... args)
	{
		call(std::forward<ARGS>(args)...);
	}
private:
	virtual void call(ARGS &&...) = 0;
};

template<>
class BasePointer <void>
{
public:
	virtual ~BasePointer() {};
	void exe()
	{
		call();
	}
private:
	virtual void call() = 0;
};

template<typename ...ARGS>
class FuncPointer : public BasePointer<ARGS...> 
{
public:
	typedef void(*FuncPtr)(ARGS...);
	FuncPointer(FuncPtr a_FunctionToPointTo)
	{
		m_fp = a_FunctionToPointTo;
	}
		
	~FuncPointer() { m_fp = nullptr; }
	void call(ARGS &&... args)
	{
		m_fp(std::forward<ARGS>(args)...);
	}
private:
	FuncPtr m_fp;
};

template<>
class FuncPointer<void> : public BasePointer<void>
{
public:
	typedef void(*FuncPtr)();
	FuncPointer(FuncPtr a_FunctionToPointTo)
	{
		m_fp = a_FunctionToPointTo;
	}

	~FuncPointer() { m_fp = nullptr; }

	void call()
	{
		m_fp();
	}
private:
	FuncPtr m_fp;
};

template<class T, typename ...ARGS>
class MemFuncPointer : public BasePointer<ARGS...> 
{
public:
	typedef void(T::*FuncPtr)(ARGS...);
	MemFuncPointer(T *a_Object, FuncPtr a_FunctionToPointTo)
	{
		m_Object = a_Object;
		m_fp = a_FunctionToPointTo;
	}
	~MemFuncPointer()
	{
		m_Object = nullptr;
		m_fp = nullptr;
	}
	void call(ARGS &&... args)
	{
		(m_Object->*m_fp)(std::forward<ARGS>(args)...);
	}
private:
	T* m_Object;
	FuncPtr m_fp;
};