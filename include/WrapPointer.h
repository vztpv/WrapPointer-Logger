
#ifndef WRAP_POINTER_H
#define WRAP_POINTER_H

#include <vector>
#include <string>
#include <fstream>
#include <set>
#include "global.h"

class FileManager
{
public:
	inline static std::string fileName;
	static void ClearFile() {
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
	T* ptr = nullptr;
	long long pid;

	inline static std::set<long long> removed_tids;
	inline static std::set<long long> tids;
	inline static long long tid = 0; // total
	static long long GetId() {
		if (!removed_tids.empty()) {
			long long x = *removed_tids.begin();
			removed_tids.erase(x);
			tids.insert(x);
			return x;
		}
		tids.insert(tid);
		tid++;
		return tid;
	}
	void ReturnId() {
		removed_tids.insert(this->pid);
		tids.erase(this->pid);
	}
private:
	WrapPointer(T* _ptr)
		: ptr(_ptr)
	{
		pid = GetId();
		FileManager::WriteLine(std::string("New = { ") + wiz::toStr(pid) + " }");
	}
	WrapPointer(long long _pid, T* _ptr)
		: ptr(_ptr)
	{
		pid = _pid;
	}
	WrapPointer(long long _pid) {
		pid = _pid;
	}
public:
	WrapPointer(const WrapPointer& other) {
		pid = GetId();
		ptr = other.ptr;
		FileManager::WriteLine(std::string("NewFromOther = { ") + wiz::toStr(pid) + " = " + wiz::toStr(other.pid) + " }");
	}
	WrapPointer() {
		pid = GetId();
		FileManager::WriteLine(std::string() + wiz::toStr(pid) + " = { }");
	}
	
	virtual ~WrapPointer() {
		FileManager::WriteLine(std::string("ReturnId = { ") + wiz::toStr(pid) + " }");
		ReturnId();
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
		auto pid = GetId();
		FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + " = { \n");
		auto x = WrapPointer<T>(new T(), pid);
		FileManager::WriteLine(std::string(" } } \n"));
		return x;
	}

	template <typename... Ts>
	static WrapPointer New(Ts&& ... args) // emplace_new
	{
		auto pid = GetId();
		FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + " = { \n");
		auto temp = WrapPointer<T>(pid, new T(std::forward<Ts>(args)...));
		FileManager::WriteLine(std::string(" } } \n"));
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
	FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(this->pid) + " } ");
	return ptr;
}
template <class T>
const T* WrapPointer<T>::operator->() const {
	FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(this->pid) + " } ");
	return ptr;
}
template <class T>
WrapPointer<T>& WrapPointer<T>::operator=(const WrapPointer& other) {
	FileManager::WriteLine(std::string() + "assign = { \n" + wiz::toStr(this->pid) + " = " + wiz::toStr(other.pid) + "  ");

	this->ptr = other.ptr;

	FileManager::WriteLine(std::string() + " } ");

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
	FileManager::WriteLine(std::string() + "delete = { " + wiz::toStr(pid) + " }");
	delete ptr;
}
template <class T>
void WrapPointer<T>::DeleteArray() {
	FileManager::WriteLine(std::string() + "delete[] = { " + wiz::toStr(pid) + " }");
	delete[] ptr;
}

#endif
