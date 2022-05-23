#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <io.h>                             
#include <fcntl.h>                          
#include <Windows.h>
#include <vector>

namespace fs = std::filesystem;
using namespace std;

vector<string> expansions_true_list = vector<string>();
vector<string> expansions_list = vector<string>();

bool checkExpansion(filesystem::path path)
{
	for(string n : expansions_true_list) {
		if (n == path.extension())
		{
			expansions_list.push_back(path.u8string());
			return true;
		}
	}

	return false;
}

void getFiles(filesystem::path path)
{
	for (auto& path_item : fs::directory_iterator(path))
	{
		if (!path_item.is_directory())
		{
			checkExpansion(path_item.path());			
			continue;
		}
			getFiles(path_item);
		
	}
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	expansions_true_list.push_back(".css");
	expansions_true_list.push_back(".js");
	expansions_true_list.push_back(".html");
	expansions_true_list.push_back(".php");
	string path = "D:\\OpenServer\\domains\\test.ru";
	getFiles(path);
		int size = expansions_list.size();
		std::ofstream out;
		out.open("D:\\code.txt");
		if (out.is_open())
		{
			std::string line;
			for (string n : expansions_list) {
				std::ifstream in(n);
				if (in.is_open())
				{
					while (getline(in, line))
					{
						out << line << std::endl;
					}
					system("cls");
					cout << "Размер:" << expansions_list.size() << endl;
					cout << --size << endl;
				}
				else {
					cout << "Error:" << n << endl;
				}
				in.close();
			}
		}
		std::cout << "Завершенно!" << std::endl;
	return;
}
