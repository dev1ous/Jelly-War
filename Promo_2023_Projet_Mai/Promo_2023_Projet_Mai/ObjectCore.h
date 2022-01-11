#ifndef OBJECTCORE_H
#define OBJECTCORE_H

#include <string>
#include <map>

class File_Reader;

class ObjectCore
{
public:
	enum class SelectedType { None, Value, Object };

private:
	friend class File_Reader;

	File_Reader* from = nullptr;

	SelectedType Statut{ SelectedType::None };
	std::string Value_name;
	std::string Selected_Value;
	ObjectCore* parent = nullptr;
	std::map<std::string, std::string> Values;
	std::map<std::string, ObjectCore> Objects;

	void Erase_This_Object();
	void Erase_This_Value();

	void Erase_Selected_Object();
	
	template <typename T>
	void NewCreation(T value);

public:
	ObjectCore& operator[](std::string str);

	void operator<<(bool i);
	void operator<<(int i);
	void operator<<(float i);
	void operator<<(double i);
	void operator<<(char i);
	void operator<<(const char* i);
	void operator<<(std::string i);

	void operator>>(bool& i);
	void operator>>(int& i);
	void operator>>(float& i);
	void operator>>(double& i);
	void operator>>(char& i);
	void operator>>(std::string& i);

	bool found() const { return Statut != SelectedType::None; }
	SelectedType Type() const { return Statut; }
	std::string ValueName() const { return Value_name; }
	void erase();
	void Lock_Start_Path();
	void UnLock_Start_Path();

	ObjectCore() = default;
	~ObjectCore() = default;
};

#endif // !OBJECTCORE_H