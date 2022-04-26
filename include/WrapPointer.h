
#ifndef WRAP_POINTER_H
#define WRAP_POINTER_H

#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>

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
		static std::string replace(const std::string& str, const std::string& str1, const std::string& str2)
		{
			if (str1.empty()) { return str; }

			std::string temp = str;

			for (std::string::size_type i = temp.size() - str1.size(); i >= 0;) {
				i = temp.rfind(str1.c_str(), i);

				if (i == std::string::npos) {
					break;
				}
				else {
					temp.replace(temp.begin() + i, temp.begin() + i + str1.size(), str2.c_str());
					--i;
				}
			}

			return temp;
		}
	public:
		static std::string fileName;

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
		// str <- no \n !
		static void WriteNote(const std::string& str) {
			replace(str, "\n", " ");
			WriteLine(std::string("NOTE = { ") + "#" + str + "\n } ");
		}

	};

	static std::set<long long> removed_tids;
	static std::set<long long> tids;
	static long long tid = 0; // total



	template <class T>
	class WrapPointer
	{
	public:
		void SetName(const std::string& str) {
			this->name = str;
		}
	private:
		bool is_make_static = false;
		bool is_array = false;
		bool is_static = false;
		bool is_make_static2 = false;

		std::string name; // const?
		T* ptr = nullptr;
		long long pid = -2; // const?

		static long long GetId() {
			static bool chk_empty = true;
			if (!removed_tids.empty()) {
				long long x = *removed_tids.begin();
				removed_tids.erase(x);
				tids.insert(x);
				chk_empty = false;
				return x;
			}
			
			if (!chk_empty) {
				tid = 0;
				std::cout << "test " << "\t";
				std::cout << tids.size() << "\t";
			}

			while (tids.end() != tids.find(tid)) {
				tid++;
			}
			
			
			std::cout << "tid " << tid << "\n";
			
			tids.insert(tid);
			
			chk_empty = true;
			return tid;
		}
		void ReturnId() {
			removed_tids.insert(this->pid);
			tids.erase(this->pid);
		}
	private:
		WrapPointer(long long _pid, T* _ptr, const std::string& _name = "", bool no_log = false)
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
			
			is_static = other.is_static;
			
			is_array = other.is_array;

			name = "_" + other.name;

			ptr = other.ptr;

			pid = GetId();

			FileManager::WriteLine(std::string("NewFromOther = { \n") + wiz::toStr(pid) + "\"" + name + "\"" + " = "
				+ wiz::toStr(other.pid) + "\"" + other.name + "\" } \n");

		

			//FileManager::WriteLine(std::string("NewFromOther = { ") + wiz::toStr(pid) + "\"" + name + "\"" + " = "
			//	+ wiz::toStr(other.pid) + "\"" + other.name + "\"" + " }");
		}
		WrapPointer(const std::string& _name = "", bool no_log = false)
			: name(_name)
		{

			if (no_log) { return; }

			pid = GetId();
			FileManager::WriteLine(std::string("NewEmpty = { ") + wiz::toStr(pid) + "\"" + name + "\"" + " }");
		}

		virtual ~WrapPointer() {

			if (is_static && is_make_static) { // PTR x ; NEW(x); PTR<PTR> y = &x;
				if (is_array) {
					DeleteArray();
				}
				else {
					Delete();
				}
			}
			else if (is_static && is_make_static2) { // int x = 5; PTR y = &x;
				ptr = nullptr;

				if (is_array) {
					DeleteArray();
				}
				else {
					Delete();
				}
			}
			ReturnId();
			FileManager::WriteLine(std::string("ReturnId = { ") + wiz::toStr(pid) + "\"" + name + "\"" + " }");
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
		WrapPointer& operator=(const WrapPointer& other);
		bool operator!() const;
		explicit operator bool() const;
		bool operator==(const WrapPointer& other) const;
		bool operator!=(const WrapPointer& other) const;
		
		static void plus(WrapPointer* x, WrapPointer* result, const long long offset) {
			result->pid = GetId();
			result->name = "_" + x->name;
			long long ppid = x->pid;
			result->ptr = x->ptr + offset;

			FileManager::WriteLine(std::string("NewPlus = { \n") + wiz::toStr(result->pid) + "%" + wiz::toStr(ppid) + "%" + wiz::toStr(offset)
				+ "\"" + result->name + "\"" + " } \n");
		}
		static void minus(WrapPointer* x, WrapPointer* result, const long long offset) {
			plus(x, result, -offset);
		}
		T& operator[](const int idx) {
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
		static void NewLocalArray(WrapPointer* x, const std::string& name, size_t n);
		static void NewArray(WrapPointer* x, const std::string& name, size_t n);
		static void NewLocalArray(WrapPointer* x, size_t n);
		static void NewArray(WrapPointer* x, size_t n);
		void Delete();
		void DeleteArray();

		// for int** ?
		static void NewLocal(WrapPointer* x, const T& value = T())
		{
			if (x->pid > 0) {
				auto pid = GetId();

				FileManager::WriteLine(std::string("NewLocal = { \n") + wiz::toStr(pid) + "\"\"" + " = { \n");
				WrapPointer temp("", true);
				new (&temp) WrapPointer<T>(pid, new T(value));
				*x = temp;
				x->is_static = true;
				x->is_make_static = true;
				FileManager::WriteLine(std::string(" } } \n"));
			}
			else {
				auto pid = GetId();

				FileManager::WriteLine(std::string("NewLocal = { \n") + wiz::toStr(pid) + "\"\"" + " = { \n");
				new (x) WrapPointer<T>(pid, new T(value));
				x->is_static = true;
				x->is_make_static = true;
				FileManager::WriteLine(std::string(" } } \n"));
			}
		}

		static void NewLocal(WrapPointer* x, T* ptr) // ptr must be static.
		{
			bool chk = x->pid > 0;

			if (chk) {

				auto pid = GetId();

				WrapPointer temp("", true);
				FileManager::WriteLine(std::string("NewLocal = { \n") + wiz::toStr(pid) + "\"\"" + " = { \n");
				new (&temp) WrapPointer<T>(pid, ptr, "");
				FileManager::WriteLine(std::string(" } } \n"));

				*x = temp;
				x->is_static = true;
				x->is_make_static2 = true;
			}
			else {
				auto pid = GetId();

				FileManager::WriteLine(std::string("NewLocal = { \n") + wiz::toStr(pid) + "\"\"" + " = { \n");
				new (x) WrapPointer<T>(pid, ptr);
				FileManager::WriteLine(std::string(" } } \n"));
				x->is_static = true;
				x->is_make_static2 = true;
			}
		}

		static void New(WrapPointer* x, const T& value = T())
		{
			if (x->pid > 0) {
				auto pid = GetId();
				FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + "\"\"" + " = { \n");
				WrapPointer temp("", true);
				new (&temp) WrapPointer<T>(pid, new T(value));
				*x = temp;
				x->is_make_static = true;
				FileManager::WriteLine(std::string(" } } \n"));
			}
			else {
				auto pid = GetId();
				FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + "\"\"" + " = { \n");
				new (x) WrapPointer<T>(pid, new T(value));
				x->is_make_static = true;
				FileManager::WriteLine(std::string(" } } \n"));
			}
		}

		// for int** ?
		static void NewLocalWithName(WrapPointer* x, const std::string& name = "", const T& value = T())
		{
			if (x->pid > 0) {
				auto pid = GetId();
				FileManager::WriteLine(std::string("NewLocal = { \n") + wiz::toStr(pid) + "\"" + name + "\"" + " = { \n");
				
				WrapPointer temp("", true);
				new (&temp) WrapPointer<T>(pid, new T(value), name);
				
				*x = temp;

				x->is_static = true;
				x->is_make_static = true;
				FileManager::WriteLine(std::string(" } } \n"));
			}
			else {
				auto pid = GetId();
				FileManager::WriteLine(std::string("NewLocal = { \n") + wiz::toStr(pid) + "\"" + name + "\"" + " = { \n");
				new (x) WrapPointer<T>(pid, new T(value), name);
				x->is_static = true;
				x->is_make_static = true;
				FileManager::WriteLine(std::string(" } } \n"));

			}
		}

		static void NewWithName(WrapPointer* x, const std::string& name = "", const T& value = T())
		{
			if (x->pid > 0) {
				auto pid = GetId();
				FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + "\"" + name + "\"" + " = { \n");
				WrapPointer temp("", true);
				new (&temp) WrapPointer<T>(pid, new T(value), name);
				*x = temp;
				FileManager::WriteLine(std::string(" } } \n"));
			}
			else {
				auto pid = GetId();
				FileManager::WriteLine(std::string("New = { \n") + wiz::toStr(pid) + "\"" + name + "\"" + " = { \n");
				new (x) WrapPointer<T>(pid, new T(value), name);
				FileManager::WriteLine(std::string(" } } \n"));
			}
		}

	private:
		//static void* operator new(size_t size) = delete;
		//static void* operator new[](size_t size) = delete;
		//static void operator delete(void* v) = delete;
		//static void operator delete[](void* v) = delete;
	};

	template <class T>
	T& WrapPointer<T>::operator*() {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"" + name + "\"" + " } ");
		return *ptr;
	}
	template <class T>
	const T& WrapPointer<T>::operator*() const {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"" + name + "\"" + " } ");
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
	WrapPointer<T>& WrapPointer<T>::operator=(const WrapPointer& other) {
		FileManager::WriteLine(std::string() + "assign = { \n" + wiz::toStr(this->pid) + "\"" + this->name + "\"" +
			" = " + wiz::toStr(other.pid) + "\"" + other.name + "\"" + "  ");

		FileManager::WriteLine(std::string() + " } ");

		this->ptr = other.ptr;

		this->is_array = other.is_array;



		return *this;
	}
	template <class T>
	bool WrapPointer<T>::operator!() const {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"\"" + " } ");
		return !ptr;
	}
	template <class T>
	WrapPointer<T>::operator bool() const {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"\"" + " } ");
		return ptr;
	}
	template <class T>
	bool WrapPointer<T>::operator==(const WrapPointer& other) const {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"\"" + " } ");
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(other.pid) + "\"\"" + " } ");
		return ptr == other.ptr;
	}
	template <class T>
	bool WrapPointer<T>::operator!=(const WrapPointer& other) const {
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(pid) + "\"\"" + " } ");
		FileManager::WriteLine(std::string() + "access = { " + wiz::toStr(other.pid) + "\"\"" + " } ");
		return ptr != other.ptr;
	}
	template <class T>
	void WrapPointer<T>::NewLocalArray(WrapPointer<T>* x, size_t n) {
		if (x->pid > 0) {
			auto pid = GetId();
			FileManager::WriteLine(std::string() + "NewLocalArray = { " + wiz::toStr(pid) + "\"\"" + " " + wiz::toStr(n) + "\n");
			WrapPointer temp("", true);
			new (&temp) WrapPointer(pid, new T[n]);
			*x = temp;
			x->is_array = true;
			x->is_static = true;
			x->is_make_static = true;
			FileManager::WriteLine(std::string() + " }\n");
		}
		else {
			auto pid = GetId();
			FileManager::WriteLine(std::string() + "NewLocalArray = { " + wiz::toStr(pid) + "\"\"" + " " + wiz::toStr(n) + "\n");
			new (x) WrapPointer(pid, new T[n]);
			x->is_array = true;
			x->is_static = true;
			x->is_make_static = true;
			FileManager::WriteLine(std::string() + " }\n");
		}
	}

	template <class T>
	void WrapPointer<T>::NewArray(WrapPointer<T>* x, size_t n) {
		if (x->pid > 0) {
			auto pid = GetId();
			FileManager::WriteLine(std::string() + "NewArray = { " + wiz::toStr(pid) + "\"\"" + " " + wiz::toStr(n) + "\n");
			WrapPointer temp("", true);

			new (&temp) WrapPointer(pid, new T[n]);
			
			*x = temp;

			x->is_array = true;
			FileManager::WriteLine(std::string() + " }\n");
		}
		else {
			auto pid = GetId();
			FileManager::WriteLine(std::string() + "NewArray = { " + wiz::toStr(pid) + "\"\"" + " " + wiz::toStr(n) + "\n");
			new (x) WrapPointer(pid, new T[n]);
			x->is_array = true;
			FileManager::WriteLine(std::string() + " }\n");
		}
	}
	template <class T>
	void WrapPointer<T>::NewLocalArray(WrapPointer<T>* x, const std::string& name, size_t n) {
		if (x->pid > 0) {
			auto pid = GetId();
			FileManager::WriteLine(std::string() + "NewLocalArray = { " + wiz::toStr(pid) + "\"" + name + "\"" + " " + wiz::toStr(n) + "\n");
			
			WrapPointer temp("", true);
			new (&temp) WrapPointer(pid, new T[n], name);
			*x = temp;
			x->is_array = true;
			x->is_static = true; x->is_make_static = true;
			FileManager::WriteLine(std::string() + " }\n");
		}
		else {
			auto pid = GetId();
			FileManager::WriteLine(std::string() + "NewLocalArray = { " + wiz::toStr(pid) + "\"" + name + "\"" + " " + wiz::toStr(n) + "\n");
			new (x) WrapPointer(pid, new T[n], name);
			x->is_array = true;
			x->is_static = true; x->is_make_static = true;
			FileManager::WriteLine(std::string() + " }\n");
		}
	}
	template <class T>
	void WrapPointer<T>::NewArray(WrapPointer<T>* x, const std::string& name, size_t n) {
		if (x->pid > 0) {
			auto pid = GetId();
			FileManager::WriteLine(std::string() + "NewArray = { " + wiz::toStr(pid) + "\"" + name + "\"" + " " + wiz::toStr(n) + "\n");
			WrapPointer temp("", true);
			new (&temp) WrapPointer(pid, new T[n], name);
			*x = temp;
			x->is_array = true;
			FileManager::WriteLine(std::string() + " }\n");
		}
		else {
			auto pid = GetId();
			FileManager::WriteLine(std::string() + "NewArray = { " + wiz::toStr(pid) + "\"" + name + "\"" + " " + wiz::toStr(n) + "\n");
			new (x) WrapPointer(pid, new T[n], name);
			x->is_array = true;
			FileManager::WriteLine(std::string() + " }\n");
		}
	}
	template <class T>
	void WrapPointer<T>::Delete() {
		FileManager::WriteLine(std::string() + "delete = { " + wiz::toStr(pid) + "\"" + name + "\"" + " }");
		if (ptr) {
			delete ptr;
			ptr = nullptr;
		}
	}
	template <class T>
	void WrapPointer<T>::DeleteArray() {
		FileManager::WriteLine(std::string() + "delete[] = { " + wiz::toStr(pid) + "\"" + name + "\"" + " }");
		if (ptr) {
			delete[] ptr;
			ptr = nullptr;
		}
	}
}


std::string wiz::FileManager::fileName;


#endif
