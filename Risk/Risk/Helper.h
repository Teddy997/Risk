#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "tinydir.h"

using std::vector;
using std::string;

class Helper
{
public:
	Helper();
	~Helper();
	void static Split(const string& fullString, char cSplitter, vector<string>& SplitStrings);
	void static Display_formatted(vector<string> to_display);
	void static Move_cursor_y(int column);
	void static Helper::DisplayMapDirectoryContents();

	//This method is defined here because otherwise it causes a linker error
	template <typename T1>
	int static Search_for_duplicate(T1 item, vector<T1> list)
	{
		int return_value = 0;
		if (!list.empty())
		{
			for (unsigned int i = 0; i < list.size(); i++)
			{
				if (list.at(i) == item) {
					return_value = 1;
					break;
				}
			}
		}
		return return_value;
	}
};
