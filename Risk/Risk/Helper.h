#pragma once
#include <iostream>
#include <Windows.h>		//for move cursor
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
	template <typename T1>
	int static Search_for_duplicate(T1 item, vector<T1> list);
};

