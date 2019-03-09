
#ifndef WRAP_POINTER_H
#define WRAP_POINTER_H

#include <vector>
#include <string>
#include <fstream>
#include "global.h"

class Manager
{
public:
	inline static std::string fileName;
	static void Clear() {
		std::ofstream outFile;
		outFile.open(fileName);
		outFile.close();
	}
	static void Write(const std::string& str)
	{
		std::ofstream outFile;
		outFile.open(fileName, std::ios::app);
		outFile << str;
		outFile.close();
	}
	static void WriteLine(const std::string& str)
	{
		std::ofstream outFile;
		outFile.open(fileName, std::ios::app);
		outFile << str << "\n";
		outFile.close();
	}
};

template <class T>
class WrapPointer
{
private:
	T* ptr;
	long long pid; 
	inline static long long id = 0; // cf) using bigint?
private:
	WrapPointer(T* _ptr)
		: ptr(_ptr) 
	{
		//
	}
public:
	WrapPointer() {
		//
	}
	~WrapPointer() {
		//
	}
public:
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;
	WrapPointer& operator=(const WrapPointer& other);
	bool operator!() const;
	operator bool() const;
	bool operator==(const WrapPointer& other) const;
	bool operator!=(const WrapPointer& other) const;
public:
	static WrapPointer NewArray(size_t n);
	void Delete();
	void DeleteArray();
	
	static WrapPointer New()
	{
		Manager::WriteLine(std::string() + "new = { \n" + wiz::toStr(id) + " = { ");
		long long _pid = id;
		id++;
		auto temp = WrapPointer<T>(new T());
		temp.pid = _pid;
		Manager::WriteLine(std::string() + " } \n} ");
		return temp;
	}

	template <typename... Ts>
	static WrapPointer New(Ts&& ... args) // emplace_new
	{
		Manager::WriteLine(std::string() + "new = { \n" + wiz::toStr(id) + " = { ");
		long long _pid = id;
		id++;
		auto temp = WrapPointer<T>(new T(std::forward<Ts>(args)...));
		temp.pid = _pid;
		Manager::WriteLine(std::string() + " } \n} ");
		return temp;
	}
private:
	static void* operator new(size_t size) = delete;
	static void* operator new[](size_t size) = delete;
	static void operator delete(void* v) = delete;
	static void operator delete[](void* v) = delete;
};

template <class T>
T& WrapPointer<T>::operator*() {

	return *ptr;
}
template <class T>
const T& WrapPointer<T>::operator*() const {

	return *ptr;
}
template <class T>
T* WrapPointer<T>::operator->() {

	return ptr;
}
template <class T>
const T* WrapPointer<T>::operator->() const {

	return ptr;
}
template <class T>
WrapPointer<T>& WrapPointer<T>::operator=(const WrapPointer& other) {

	this->ptr = other.ptr;
	return *this;
}
template <class T>
bool WrapPointer<T>::operator!() const {

	return !ptr;
}
template <class T>
WrapPointer<T>::operator bool() const {

	return ptr;
}
template <class T>
bool WrapPointer<T>::operator==(const WrapPointer& other) const {

	return ptr == other.ptr;
}
template <class T>
bool WrapPointer<T>::operator!=(const WrapPointer& other) const {

	return ptr != other.ptr;
}
template <class T>
WrapPointer<T> WrapPointer<T>::NewArray(size_t n) {

	return WrapPointer(new T[n]);
}
template <class T>
void WrapPointer<T>::Delete() {

	delete ptr;
}
template <class T>
void WrapPointer<T>::DeleteArray() {

	delete[] ptr;
}

#endif
