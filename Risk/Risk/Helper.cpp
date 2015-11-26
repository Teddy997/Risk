#include "Helper.h"

using std::cout;
using std::endl;

Helper::Helper()
{
}


Helper::~Helper()
{
}

void Helper::Split(const string& fullString, char cSplitter, vector<string>& SplitStrings) {
	int i = 0;
	int j = fullString.find(cSplitter);

	while (j >= 0) {
		SplitStrings.push_back(fullString.substr(i, j - i));
		i = ++j;
		j = fullString.find(cSplitter, j);

		if (j < 0) {
			SplitStrings.push_back(fullString.substr(i, fullString.length()));
		}
	}
}

void Helper::Display_formatted(vector<string> to_display)
{
	int n_of_columns = 4;
	int space_between_columns = 25;
	int size = to_display.size();
	int rows = (size / n_of_columns);
	int current_id;
	//to get the ceiling
	rows += (size % n_of_columns == 0) ? 0 : 1;

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < n_of_columns; j++)
		{
			current_id = (i * n_of_columns) + j;
			if (current_id >= size)
				break;
			cout << current_id << ": " << to_display.at(current_id);
			Move_cursor_y(space_between_columns * (j + 1));
		}
		cout << endl; //at the end of each row
	}
}

void Helper::Move_cursor_y(int column)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	coord.X = column;
	coord.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(hConsole, coord);
}

void Helper::DisplayMapDirectoryContents() {
	string display = "";
	tinydir_dir dir;
	tinydir_open(&dir, "Maps");

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		string filename = file.name;
		if (filename.compare("Thumbs.db") == 0 || filename.compare(".") == 0 || filename.compare("..") == 0) {
			display += "";
		}
		else {
			if (file.is_dir && (filename.compare("default") != 0))
			{
				display += filename;
				display += "\n";
			}
			else {
				display += "";
			}
		}
		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	if (display.length() == 0) {
		cout << "There are currently no user created maps!" << endl;
	}
	else {
		cout << display << endl;
	}
}
