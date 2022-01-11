#include "ObjectCore.h"
#include "File_Reader.h"
#include <iostream>

ObjectCore& ObjectCore::operator[](std::string str)
{
	Selected_Value.clear();
	Value_name = str;
	Statut = SelectedType::None;

	from->operator_path.push_back(str);

	if (Objects.find(str) != std::end(Objects)) {
		Objects.find(str)->second.Statut = SelectedType::Object;
		Objects.find(str)->second.parent = this;
		return Objects.find(str)->second;
	}

	if (Values.find(str) != std::end(Values)) {
		Statut = SelectedType::Value;
		Selected_Value = Values.find(str)->second;
		return *this;
	}

	return *this;
}

void ObjectCore::operator<<(bool b)
{
	if (from->operator_path.empty()) {
		if (parent != nullptr) {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = (b == true) ? "true" : "false";
				parent->Objects.find(parent->Value_name)->second.Erase_This_Object();
				return;
			}
		}
		else {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = (b == true) ? "true" : "false";
				Objects.find(Value_name)->second.Erase_This_Object();
				return;
			}
		}

		Values[Value_name] = (b == true) ? "true" : "false";
	}
	else {
		this->NewCreation(b);
	}

	from->Save();
	from->operator_path = from->Locked_operator_path;
}

void ObjectCore::operator<<(int i)
{
	if (from->operator_path.empty()) {
		if (parent != nullptr) {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = std::to_string(i);
				parent->Objects.find(parent->Value_name)->second.Erase_This_Object();
				return;
			}
		}
		else {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = std::to_string(i);
				Objects.find(Value_name)->second.Erase_This_Object();
				return;
			}
		}

		Values[Value_name] = std::to_string(i);
	}
	else {
		this->NewCreation(i);
	}

	from->Save();
	from->operator_path = from->Locked_operator_path;
}

void ObjectCore::operator<<(float f)
{
	if (from->operator_path.empty()) {
		if (parent != nullptr) {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = std::to_string(f);
				parent->Objects.find(parent->Value_name)->second.Erase_This_Object();
				return;
			}
		}
		else {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = std::to_string(f);
				Objects.find(Value_name)->second.Erase_This_Object();
				return;
			}
		}

		Values[Value_name] = std::to_string(f);
	}
	else {
		this->NewCreation(f);
	}

	from->Save();
	from->operator_path = from->Locked_operator_path;
}

void ObjectCore::operator<<(double d)
{
	if (from->operator_path.empty()) {
		if (parent != nullptr) {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = std::to_string(d);
				parent->Objects.find(parent->Value_name)->second.Erase_This_Object();
				return;
			}
		}
		else {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = std::to_string(d);
				Objects.find(Value_name)->second.Erase_This_Object();
				return;
			}
		}

		Values[Value_name] = std::to_string(d);
	}
	else {
		this->NewCreation(d);
	}

	from->Save();
	from->operator_path = from->Locked_operator_path;
}

void ObjectCore::operator<<(char c)
{
	if (from->operator_path.empty()) {
		if (parent != nullptr) {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = c;
				parent->Objects.find(parent->Value_name)->second.Erase_This_Object();
				return;
			}
		}
		else {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = c;
				Objects.find(Value_name)->second.Erase_This_Object();
				return;
			}
		}

		Values[Value_name] = c;
	}
	else {
		this->NewCreation(c);
	}

	from->Save();
	from->operator_path = from->Locked_operator_path;
}

void ObjectCore::operator<<(const char* str)
{
	if (from->operator_path.empty()) {
		if (parent != nullptr) {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = str;
				parent->Objects.find(parent->Value_name)->second.Erase_This_Object();
				return;
			}
		}
		else {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = str;
				Objects.find(Value_name)->second.Erase_This_Object();
				return;
			}
		}

		Values[Value_name] = str;
	}
	else {
		this->NewCreation(str);
	}

	from->Save();
	from->operator_path = from->Locked_operator_path;
}

void ObjectCore::operator<<(std::string str)
{
	if (from->operator_path.empty()) {
		if (parent != nullptr) {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = str;
				parent->Objects.find(parent->Value_name)->second.Erase_This_Object();
				return;
			}
		}
		else {
			if (Objects.find(Value_name) != std::end(Objects)) {
				Values[Value_name] = str;
				Objects.find(Value_name)->second.Erase_This_Object();
				return;
			}
		}

		Values[Value_name] = str;
	}
	else {
		this->NewCreation(str);
	}

	from->Save();
	from->operator_path = from->Locked_operator_path;
}

void ObjectCore::operator>>(bool& i)
{
	if (this->Statut == SelectedType::None) {
		std::cout << "No value Here" << std::endl;
		i = false;
	}

	else if (this->Statut == SelectedType::Object) {
		std::cout << "Object not a value" << std::endl;
		i = false;
	}

	if (this->Selected_Value == "true") {
		i = true;
	}

	if (this->Selected_Value == "false") {
		i = false;
	}


	std::cout << "Not a boolean value" << std::endl;
	i = false;
}

void ObjectCore::operator>>(int& i)
{
	if (this->Statut == SelectedType::None)	{
		std::cout << "No value Here" << std::endl;
		i = 0;
		return;
	}

	else if (this->Statut == SelectedType::Object) {
		std::cout << "Object not a value" << std::endl;
		i = 0;
		return;
	}

	i = std::stoi(this->Selected_Value);
}

void ObjectCore::operator>>(float& i)
{
	if (this->Statut == SelectedType::None)	{
		std::cout << "No value Here" << std::endl;
		i = 0.0f;
		return;
	}

	else if (this->Statut == SelectedType::Object) {
		std::cout << "Object not a value" << std::endl;
		i = 0.0f;
		return;
	}

	i = std::stof(this->Selected_Value);
}

void ObjectCore::operator>>(double& i)
{
	if (this->Statut == SelectedType::None)	{
		std::cout << "No value Here" << std::endl;
		i = 0.0;
		return;
	}

	else if (this->Statut == SelectedType::Object) {
		std::cout << "Object not a value" << std::endl;
		i = 0.0;
		return;
	}

	i = std::stod(this->Selected_Value);
}

void ObjectCore::operator>>(char& i)
{
	if (this->Statut == SelectedType::None)	{
		std::cout << "No value Here" << std::endl;
		i = 0;
		return;
	}

	else if (this->Statut == SelectedType::Object) {
		std::cout << "Object not a value" << std::endl;
		i = 0;
		return;
	}

	i = this->Selected_Value[0];
}

void ObjectCore::operator>>(std::string& i)
{
	if (this->Statut == SelectedType::None) {
		std::cout << "No value Here" << std::endl;
		i = "";
		return;
	}

	else if (this->Statut == SelectedType::Object) {
		std::cout << "Object not a value" << std::endl;
		i = "";
		return;
	}

	i = this->Selected_Value;
}

void ObjectCore::Erase_This_Object()
{
	if (Statut == SelectedType::Object)	{
		if (parent != nullptr) {
			parent->Erase_Selected_Object();
		}
	}
}

void ObjectCore::Erase_This_Value()
{
	if (Statut == SelectedType::Value) {
		Values.erase(Values.find(this->Value_name));
	}
}

void ObjectCore::Erase_Selected_Object()
{
	Objects.erase(Objects.find(Value_name));
	from->Save();
}

void ObjectCore::erase()
{
	this->Erase_This_Object();
	this->Erase_This_Value();
}

void ObjectCore::Lock_Start_Path()
{
	from->Locked_operator_path = from->operator_path;
}

void ObjectCore::UnLock_Start_Path()
{
	from->Locked_operator_path.clear();
}

template<typename T>
inline void ObjectCore::NewCreation(T value)
{
	ObjectCore* current(&from->Main);

	for (size_t i = 0; i < from->operator_path.size(); i++)
	{
		if (i == from->operator_path.size() - 1) // value
		{
			current->operator[](from->operator_path[i]);
			from->operator_path.clear();
			*current << value;
		}
		else // objects
		{
			if (current->Values.find(from->operator_path[i]) != std::end(current->Values))
			{
				current->Values.erase(current->Values.find(from->operator_path[i]));
			}

			current->Objects.insert({ from->operator_path[i], ObjectCore() });
			current->Objects[from->operator_path[i]].from = from;
			current->Objects[from->operator_path[i]].parent = current;
			current = &current->Objects[from->operator_path[i]];
		}
	}

}