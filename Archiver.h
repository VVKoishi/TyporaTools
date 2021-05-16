// 检查 .md 文件是否存在
// 储存文本中所有 assets/xxx.png 和 <img src="yyy.png"> 图片名称引用到哈希表
// 移动所有 .md 到目标文件夹
// 移动所有 img 到目标文件夹/assets/
// ** 不能解决多个文件引用相同图片的移动问题 **
// [2021 Voc]
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <filesystem>
#include <regex>
#include <exception>
using namespace std;
using namespace filesystem;


class Archiver {
public:
    Archiver(vector<string>& mdFileNames, const path from, const path to, const path imgPath)
        : from(from), to(to), imgPath(imgPath)
    {
        mdFilePaths.resize(mdFileNames.size());
        for (int i = 0; i < mdFileNames.size(); i++)
        {
            mdFilePaths[i] = /*from.string() +*/ mdFileNames[i];
        }
    }
    ~Archiver() = default;

    const regex Pattern {"!\\[.*?\\]\\(.*?/(.*?)\\)|<img.*?src=\".*?/(.*?)\""};

    // 执行归档
	void Run() {
		try
		{
			if (!is_directory(from))
			{
				cerr << "From path is not a dictionary.\n"
					<< "From: " << from << "\n"
					<< "To: " << to << "\n"
					<< "You can change the paths setting in source code.\n";
				return;
			}
            checkFilePaths( {".md"} );

			cout << "//////////////////////////////////////////////////////////////////////////" << "\n"
				<< "Collecting images references..." << "\n";
			scanMDFiles();

			cout << "//////////////////////////////////////////////////////////////////////////" << "\n"
				<< "Moving markdown files and images..." << "\n";
			moveFilesAndImages();

			cout << "//////////////////////////////////////////////////////////////////////////" << "\n"
				<< "Finished!" << "\n"
				<< "Moved markdown files num: \t" << mdFilePaths.size() << "\n"
				<< "Moved image files num: \t" << imgNameTable.size() << "\n";
        }
        catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

private:
    path const from;
    path const to;
	path const imgPath;
    vector<path> mdFilePaths;
    unordered_map<string, int> imgNameTable;

	// 是否为可接受的后缀名
	bool is_accepted_extension(const path p, vector<string>& acceptedExt) const {
		if (find(acceptedExt.begin(), acceptedExt.end(), p.extension()) != acceptedExt.end())
			return true;
		else return false;
	}

	// 检查 file paths
	void checkFilePaths(vector<string> acceptedExt) {
		for (auto itor = mdFilePaths.begin(); itor != mdFilePaths.end(); )
        {
            if (!is_regular_file(*itor))
            {
                cerr << "Error: " << *itor << " is not a file. \n";
                mdFilePaths.erase(itor);
            }
			else if (!is_accepted_extension(*itor, acceptedExt))
			{
				cerr << "Error: " << *itor << " is not a accepted file type. \n";
                mdFilePaths.erase(itor);
			}
            else
            {
                itor++;
            }
        }
	}

	// 查找 [](IMG) 和 <IMG> 标签，初始化哈希表
	void scanMDFiles() { 
		for (const path& p : mdFilePaths)
		{
			cout << ">>>>" << p << "\n";
			ifstream in{p};
			int lineno = 0;
			for (string line; getline(in,line); ) 
			{
				++lineno;
				smatch matches; // matched strings go here 
				while (regex_search(line, matches, Pattern)) 
				{
					if (matches.size() > 1 && matches[1].matched)
					{
						imgNameTable[matches[1]]++;
						//cout << matches[1] << "\n";
					}
					else if (matches.size() > 2 && matches[2].matched)
					{
						imgNameTable[matches[2]]++;
						//cout << matches[2] << "\n";
					}
					line = matches.suffix().str();
				}
			}
		}
	}

	// 移动 MD 和 IMG 到新路径
	void moveFilesAndImages() {
		// 创建沿途文件夹
		if (!exists(to.string() + imgPath.string()))
		{
			if (!create_directories(to.string() + imgPath.string()))
			{
				cerr << "Can't create directories.\n";
				return;
			}
		}
		// 移动 MD
		for (const path& p : mdFilePaths)
		{
			path p2{ to.string() + p.string().erase(0, from.string().size()) };
			if (!is_regular_file(p)) continue;
			cout << ">>>> Moving " << p << " to " << p2 << "\n";
			if (copy_file(p, p2))
			{
				remove(p);
			}
		}
		// 移动 IMG
		for (auto& [name, count] : imgNameTable)
		{
			path p{ from.string() + imgPath.string() + name };
			path p2{ to.string() + imgPath.string() + name };
			// cout << p << "\n";
			// cout << p2 << "\n";
			if (!is_regular_file(p)) continue;
			cout << ">>>> Moving " << p << " to " << p2 << "\n";
			if (copy_file(p, p2))
			{
				remove(p);
			}
		}
	}
};
