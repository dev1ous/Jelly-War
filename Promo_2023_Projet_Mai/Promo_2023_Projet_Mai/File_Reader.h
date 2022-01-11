#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <vector>

#include "ObjectCore.h"

class File_Reader
{
	friend class ObjectCore;

public:
	using open_mode = int;

	static constexpr open_mode Read_Only = static_cast<open_mode>(0x0);
	static constexpr open_mode Read_And_Write = static_cast<open_mode>(0x1);

private:
	ObjectCore Main;
	std::string FilePath;
	open_mode mode{ Read_And_Write };

	std::vector<std::string> operator_path;
	std::vector<std::string> Locked_operator_path;

	void Remove_Unwanted_Char(std::string& str);
	void ObjectRead(std::ifstream& Reading, std::string obj_name, ObjectCore& obj);
	void ObjectSave(std::ofstream& File, std::string obj_name, ObjectCore& obj, unsigned int tabs);

	void Save();

public:
	File_Reader(open_mode _mode = File_Reader::Read_And_Write);
	File_Reader(const char* path, open_mode mode = File_Reader::Read_And_Write);
	~File_Reader();

	void Bind(std::string path);
	void Lock_Start_Path() { Locked_operator_path = operator_path; };
	void UnLock_Start_Path() { Locked_operator_path.clear(); };

	inline void ChangeMode(open_mode _mode) { mode = _mode; }
	inline open_mode GetMode() const { return mode; }

	ObjectCore& operator[](std::string str);
};

#endif // !FILE_H