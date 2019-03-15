
#ifndef WRAP_POINTER_H
#define WRAP_POINTER_H

#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <string>

namespace wiz {
	template <typename T> /// x is 10진수..
	inline T pos_1(const T x, const int base = 10) // 1�리 �계산
	{
		if (x >= 0) { return x % base; }// x - ( x / 10 ) * 10; }
		else { return (x / base) * base - x; }
		// -( x - ( (x/10) * 10 ) )
	}

	template <typename T> /// T <- char, int, long, long long...
	std::string toStr(const T x) /// chk!!
	{
		const int base = 10;
		if (base < 2 || base > 16) { return "base is not valid"; }
		T i = x;

		const int INT_SIZE = sizeof(T) << 3; ///*8
		char* temp = new char[INT_SIZE + 1 + 1]; /// 1 nullptr, 1 minus
		std::string tempString;
		int k;
		bool isMinus = (i < 0);
		temp[INT_SIZE + 1] = '\0'; ///문자�시..

		for (k = INT_SIZE; k >= 1; k--) {
			T val = pos_1<T>(i, base); /// 0 ~ base-1
			/// number to ['0'~'9'] or ['A'~'F']
			if (val < 10) { temp[k] = val + '0'; }
			else { temp[k] = val - 10 + 'A'; }

			i /= base;

			if (0 == i) { // �자.
				k--;
				break;
			}
		}

		if (isMinus) {
			temp[k] = '-';
			tempString = std::string(temp + k);//
		}
		else {
			tempString = std::string(temp + k + 1); //
		}
		delete[] temp;

		return tempString;
	}
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

	inline static std::set<long long> removed_tids;
	inline static std::set<long long> tids;
	inline static long long tid = 0; // total



	template <class T>
	class WrapPointer
	{
	public:
		void SetName(const std::string& str) {
			this->name = str;
		}
	private:
		long long offset = 0;
		std::string name; // const?
		T* ptr = nullptr;
		long long ppid = -1;
		long long pid; // const?

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
		WrapPointer(long long _pid, T* _ptr, const std::string& _name = "")
			: ptr(_ptr), name(_name)
		{
			pid = _pid;
		}
		WrapPointer(long long _pid, const std::string& _name = "")
			: name(_name)
		{
			pid = _pid;

		}
	public:
		WrapPointer(const WrapPointer& other) {
			name = "_" + other.name;
			pid = GetId();
			ptr = other.ptr;
			FileManager::WriteLine(std::string("NewFromOther = { ") + wiz::toStr(pid) + "\"" + name + "\"" + " = "
				+ wiz::toStr(other.pid) + "\"" + other.name + "\"" + " }");
		}
		WrapPointer(const std::string & _name = "")
			: name(_name)
		{
			pid = GetId();
			FileManager::WriteLine(std::string("NewEmpty = { ") + wiz::toStr(pid) + "\"" + name + "\"" + " }");
		}

		virtual ~WrapPointer() {
			FileManager::WriteLine(std::string("ReturnId = { ") + wiz::toStr(pid) + "\"" + name + "\"" + " }");
			ReturnId();
		}
	public:
		T* data() {
			//
			return ptr;
		}
		const T* data() const {
			//
			return ptr;
		}
		T& operator*();
		const T& operator*() const;
		T* operator->();
		const T* operator->() const;
		WrapPointer& operator=(const WrapPointer & other);
		bool operator!() const;
		explicit operator bool() const;
		bool operator==(const WrapPointer & other) const;
		bool operator!=(const WrapPointer & other) const;
		WrapPointer operator+(const long long x) const {
			WrapPointer temp;
			temp.pid = GetId();
			temp.name = "_" + this->name;
			temp.ppid = this->pid;
			temp.offset = x;

			FileManager::WriteLine(std::string("NewLocal = { \n") + wiz::toStr(temp.pid) + "%" + wiz::toStr(temp.ppid) + "%" + wiz::toStr(temp.offset)
				+ "\"" + temp.name + "\"" + " } \n");

			return temp;
		}
		WrapPointer operator-(const long long x) const {
			return (*this) + (-x);
		}
		T & operator[](const int idx) {
			FileManager::WriteLine(std::string("access_array = { ") + wiz::toStr(this->pid) + "\"" + this->name + "\"" + " "
				+ wiz::toStr(idx) + " } ");
			return this->ptr[idx];
		}
		const T& operator[](const int idx) const {
			FileManager::WriteLine(std::string("access_array = { ") + wiz::toStr(this->pid) + "\"" + this->name + "\"" + " "
				+ wiz::toStr(idx) + " } ");
			return this->ptr[idx];
		}
	public:
		static WrapPointer NewArray(const std::string & name, size_t n);
		static WrapPointer NewArray(size_t n);
		void Delete();
		void DeleteArray();

		static WrapPointer New()
		{
			auto pid = GetId();
			FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + "\"\"" + " = { \n");
			auto x = WrapPointer<T>(pid, new T());
			FileManager::WriteLine(std::string(" } } \n"));
			return x;
		}


		static WrapPointer NewWithName(const std::string & name = "")
		{
			auto pid = GetId();
			FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + "\"" + name + "\"" + " = { \n");
			auto x = WrapPointer<T>(pid, new T(), name);
			FileManager::WriteLine(std::string(" } } \n"));
			return x;
		}

		template <typename... Ts>
		static WrapPointer New(Ts && ... args) // emplace_new
		{
			auto pid = GetId();
			FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + "\"\"" + " = { \n");
			auto temp = WrapPointer<T>(pid, new T(std::forward<Ts>(args)...));
			FileManager::WriteLine(std::string(" } } \n"));
			return temp;
		}
		template <typename... Ts>
		static WrapPointer NewWithName(const std::string & _name, Ts && ... args) // emplace_new
		{
			auto pid = GetId();
			FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + "\"" + _name + "\"" + " = { \n");
			auto temp = WrapPointer<T>(pid, new T(std::forward<Ts>(args)...), _name);
			FileManager::WriteLine(std::string(" } } \n"));
			return temp;
		}
	private:
		//static void* operator new(size_t size) = delete;
		//static void* operator new[](size_t size) = delete;
		//static void operator delete(void* v) = delete;
		//static void operator delete[](void* v) = delete;
	};

	template <class T>
	T& WrapPointer<T>::operator*() {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"\"" + " } ");
		return *ptr;
	}
	template <class T>
	const T& WrapPointer<T>::operator*() const {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"\"" + " } ");
		return *ptr;
	}
	template <class T>
	T* WrapPointer<T>::operator->() {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(this->pid) + "\"" + name + "\"" + " } ");
		return ptr;
	}
	template <class T>
	const T* WrapPointer<T>::operator->() const {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(this->pid) + "\"" + name + "\"" + " } ");
		return ptr;
	}
	template <class T>
	WrapPointer<T>& WrapPointer<T>::operator=(const WrapPointer & other) {
		FileManager::WriteLine(std::string() + "assign = { \n" + wiz::toStr(this->pid) + "\"" + this->name + "\"" +
			" = " + wiz::toStr(other.pid) + "\"" + other.name + "\"" + "  ");

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
	bool WrapPointer<T>::operator==(const WrapPointer & other) const {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"\"" + " } ");
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(other.pid) + "\"\"" + " } ");
		return ptr == other.ptr;
	}
	template <class T>
	bool WrapPointer<T>::operator!=(const WrapPointer & other) const {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"\"" + " } ");
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(other.pid) + "\"\"" + " } ");
		return ptr != other.ptr;
	}
	template <class T>
	WrapPointer<T> WrapPointer<T>::NewArray(size_t n) {
		auto pid = GetId();
		FileManager::WriteLine(std::string() + "NewArray = { " + wiz::toStr(pid) + "\"\"" + " " + wiz::toStr(n) + "\n");
		auto temp = WrapPointer(pid, new T[n]);
		FileManager::WriteLine(std::string() + " }\n");
		return temp;
	}
	template <class T>
	WrapPointer<T> WrapPointer<T>::NewArray(const std::string & name, size_t n) {
		auto pid = GetId();
		FileManager::WriteLine(std::string() + "NewArray = { " + wiz::toStr(pid) + "\"" + name + "\"" + " " + wiz::toStr(n) + "\n");
		auto temp = WrapPointer(pid, new T[n], name);
		FileManager::WriteLine(std::string() + " }\n");
		return temp;
	}
	template <class T>
	void WrapPointer<T>::Delete() {
		FileManager::WriteLine(std::string() + "delete = { " + wiz::toStr(pid) + "\"" + name + "\"" + " }");
		if (ptr) {
			delete ptr;
		}
	}
	template <class T>
	void WrapPointer<T>::DeleteArray() {
		FileManager::WriteLine(std::string() + "delete[] = { " + wiz::toStr(pid) + "\"" + name + "\"" + " }");
		if (ptr) {
			delete[] ptr;
		}
	}
}

#endif
