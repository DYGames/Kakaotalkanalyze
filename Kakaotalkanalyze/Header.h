#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <cerrno>

struct Talk
{
	std::string _name;
	std::string _sentence;
	std::string _time;
};

class KakaotalkAnalyze
{
public:
	void Run(std::string);
	void AnalyzeName();
	void AnalyzeTime();

private:
	void Process(std::string);
	std::vector<std::pair<std::string, int>> SortByValue(std::map<std::string, int>);

private:
	std::queue<Talk> _talk;
	std::map<std::string, int> _name;
	std::map<std::string, int> _time;

};