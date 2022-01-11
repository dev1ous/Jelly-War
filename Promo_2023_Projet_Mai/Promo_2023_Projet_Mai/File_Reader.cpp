#include "File_Reader.h"

#include <algorithm>
#include <iostream>

void File_Reader::Remove_Unwanted_Char(std::string& str)
{
	str.erase(std::remove(std::begin(str), std::end(str), '\t'), std::end(str));
}

void File_Reader::ObjectRead(std::ifstream& Reading, std::string obj_name, ObjectCore& obj)
{
	obj.Objects[obj_name].from = this;

	std::string Line;
	while (std::getline(Reading, Line))
	{
		if (Line.find("{") != -1)
		{
			std::string Name(Line.substr(0, Line.find("{") - 1));
			Remove_Unwanted_Char(Name);

			ObjectRead(Reading, Name, obj.Objects[obj_name]);
		}
		else if (Line.find(" : ") != -1)
		{
			std::string valuename = Line.substr(0, Line.find(" : "));
			std::string value = Line.substr(Line.find(" : ") + 3);

			Remove_Unwanted_Char(valuename);
			Remove_Unwanted_Char(value);

			obj.Objects[obj_name].Values[valuename] = value;
		}

		if (Line.find("}") != -1)
		{
			return;
		}
	}
}

void File_Reader::ObjectSave(std::ofstream& File, std::string obj_name, ObjectCore& obj, unsigned int tabs)
{
	if (tabs > 0)
		for (unsigned int i = 0; i < tabs - 1; i++) { File << '\t'; }

	if (obj_name != "")
		File << obj_name << " {" << std::endl;
	else
		File << "{" << std::endl;


	std::for_each(std::begin(obj.Values), std::end(obj.Values), [&](std::pair<const std::string, std::string>& value)
		{
			for (unsigned int i = 0; i < tabs; i++) { File << '\t'; }
			File << value.first << " : " << value.second << std::endl;
		});

	std::for_each(std::begin(obj.Objects), std::end(obj.Objects), [&](std::pair<const std::string, ObjectCore>& Object)
		{
			File << std::endl;
			ObjectSave(File, Object.first, Object.second, tabs + 1);
		});

	for (unsigned int i = 0; i < tabs; i++) { File << '\t'; }
	File << "}" << std::endl;
}

void File_Reader::Save()
{
	if (mode == File_Reader::Read_And_Write)
	{
		std::ofstream File(FilePath);
		if (File.is_open())
		{
			ObjectSave(File, "", Main, 0);

			File.close();
		}
	}
}

File_Reader::File_Reader(open_mode _mode)
	: mode(_mode)
{
	Main.from = this;
}

File_Reader::File_Reader(const char* path, open_mode _mode)
	: mode(_mode)
{
	Main.from = this;

	Bind(path);
}

File_Reader::~File_Reader()
{
}

void File_Reader::Bind(std::string path)
{
	FilePath = path;
	std::ifstream Reading(FilePath);
	if (Reading.is_open())
	{
		bool FileOpen{ false };

		std::string Line;
		while (std::getline(Reading, Line))
		{
			if (Line.find("{") != -1 && FileOpen)
			{
				std::string Name(Line.substr(0, Line.find("{") - 1));
				Remove_Unwanted_Char(Name);

				ObjectRead(Reading, Name, Main);
			}
			else if (Line.find("{") != -1 && !FileOpen)
				FileOpen = true;
			else if (Line.find(" : ") != -1)
			{
				std::string valuename = Line.substr(0, Line.find(" : "));
				std::string value = Line.substr(Line.find(" : ") + 3);

				Remove_Unwanted_Char(valuename);
				Remove_Unwanted_Char(value);

				Main.Values[valuename] = value;
			}
		}

		Reading.close();
	}
	else
		std::cerr << "can't open file" << std::endl;
}

ObjectCore& File_Reader::operator[](std::string str)
{
	operator_path.clear();
	return Main.operator[](str);
}
