﻿#include <fstream>
#include <sstream>
#include <iostream>

#include "AStar.h"
#include "Misc/Duration.h"

int main()
{
	char maps[1000][1000] =
	{
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 0, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
		{ 1, 1, 0, 0, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
	};

	// 搜索参数
	pf::SearchParam param;
	param.total_row = 1000;
	param.total_col = 1000;
	param.can_reach = [&](const pf::Point &point)->bool
	{
		return maps[point.row][point.col] == 0;
	};
	param.start_point = pf::Point(0, 0);
	param.end_point = pf::Point(999, 999);
	param.allow_corner = false;

	// 执行搜索
	pf::AStar astar;
	Duration duration;
	auto path = astar.Search(param);

	std::cout << (path.empty() ? "路径未找到！" : "路径已找到！") << std::endl;
	std::cout << "本次寻路耗时" << duration.NanoSeconds() << "纳秒" << std::endl;

	if (!path.empty())
	{
		std::ofstream file;
		std::stringstream ss;
		file.open("search_path.txt");
		for (auto &value : path)
		{
			ss.str("");
			ss << "row:" << value.row << ", " << "col:" << value.col << "\n";
			file.write(ss.str().c_str(), ss.str().length());
		}
		file.close();
		std::cout << "路径已成功保存到search_path.txt文件!" << std::endl;
	}
	
	std::cout << '\n';
	system("pause");
	return 0;
}