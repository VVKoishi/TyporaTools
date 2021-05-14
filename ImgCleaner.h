// 遍历 dirPath 中的所有 .md
// 储存文本中所有 assets/xxx.png 和 <img src="yyy.png"> 图片名称引用到哈希表
// 清除 imgPath 中不在哈希表记录的文件
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


class ImgCleaner {
public:
	ImgCleaner(const path dirPath, const path imgPath) 
		: dirPath(dirPath), imgPath(imgPath) {}
	~ImgCleaner() = default;

	const regex Pattern {"!\\[.*?\\]\\(.*?/(.*?)\\)|<img.*?src=\".*?/(.*?)\""};

	// ִ执行清理
	void Run() {
		try
		{
			initNamesList(dirPath, {".md"}, mdFileNames);
			initNamesList(imgPath, {".jpg", ".png", ".gif", ".svg"}, imgFileNames);
			int mdNums = mdFileNames.size();
			int imgNums = imgFileNames.size();
			uintmax_t imgSizes = computeFilesSize(imgFileNames);

			cout << "//////////////////////////////////////////////////////////////////////////" << "\n"
				<< "Collecting images references..." << "\n";
			scanMDFiles();

			cout << "//////////////////////////////////////////////////////////////////////////" << "\n"
				<< "Cleaning unused images..." << "\n";
			removeUnusedImages();
			uintmax_t imgSizesAfterCleaning = computeFilesSize(imgFileNames);

			cout << "//////////////////////////////////////////////////////////////////////////" << "\n"
				<< "Finished!" << "\n"
				<< "Markdown files num: \t" << mdNums << "\n"
				<< "Image files num: \t" << imgNums << "\n"
				<< "Image files size: \t" << imgSizes << " Bytes" << "\n"
				<< "Size after cleaning: \t" << imgSizesAfterCleaning << " Bytes" << "\n";
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

	const path DirPath() const { return dirPath; }
	const path ImgPath() const { return imgPath; }
private:
	path const dirPath;
	path const imgPath;
	unordered_map<string, int> imgNameTable;
	vector<path> mdFileNames;
	vector<path> imgFileNames;

	// 是否为可接受的后缀名
	bool is_accepted_extension(const path p, vector<string>& acceptedExt) const {
		if (find(acceptedExt.begin(), acceptedExt.end(), p.extension()) != acceptedExt.end())
			return true;
		else return false;
	}

	// 初始化 MD名称列表 和 IMG名称列表
	void initNamesList(const path p, vector<string> acceptedExt, vector<path>& namesList) {
		if (is_directory(p)) 
		{
			for (const directory_entry& x : directory_iterator{p}) 
			{
				if (is_regular_file(x) && is_accepted_extension(x.path(), acceptedExt))
				{
					//cout << x.path() << '\n';
					namesList.emplace_back(x.path());
				}
			}
		}
	}

	// 查找 [](IMG) 和 <IMG> 标签，初始化哈希表
	void scanMDFiles() { 
		for (const path& p : mdFileNames)
		{
			cout << ">>>>" << p << "\n";
			ifstream in{p};
			int lineno = 0;
			for (string line; getline(in,line); ) 
			{
				++lineno;
				smatch matches; // matched strings go here 
				if (regex_search(line, matches, Pattern)) 
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
				}
			}
		}
	}

	// 删除未在哈希表中的图片
	void removeUnusedImages() {
		for (const path& p : imgFileNames)
		{
			if (imgNameTable.find(p.filename().string()) == imgNameTable.end())
			{
				if (remove(p))
				{
					cout << "Removed " << p.filename() << "\n";
				}
			}
		}
	}

	// 计算目录下所有文件大小
	uintmax_t computeFilesSize(vector<path>& pathsList) {
		uintmax_t sz = 0;
		for (const path& p : pathsList)
		{
			if (exists(p))
				sz += file_size(p);
		}
		return sz;
	}
};