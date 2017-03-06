#include "Header.h"

int main()
{
	KakaotalkAnalyze kakaotalkanalyze;

	std::cout << "파일명을 입력해주세요.\n\n";

	std::string path;
	std::cin >> path;
	kakaotalkanalyze.Run(path);

	system("cls");
	std::cout << "분석이 완료되었습니다.\n";

	while (true)
	{
		std::cout << "\n1. 가장 많이 말한 사람.\n";
		std::cout << "\n2. 가장 많이 말한 시간대.\n\n";
		int tmp;
		std::cin >> tmp;
		system("cls");

		if (tmp == 1)
		{
			system("cls");
			std::cout << "\n가장 많이 말한 사람.\n\n";
			kakaotalkanalyze.AnalyzeName();
		}

		if (tmp == 2)
		{
			system("cls");
			std::cout << "\n가장 많이 말한 시간대.\n\n";
			kakaotalkanalyze.AnalyzeTime();
		}
	}
}

void KakaotalkAnalyze::Run(std::string path)
{
	std::ifstream kakaotalkfile(path);
	if (kakaotalkfile.is_open())
	{
		std::string line;
		while (std::getline(kakaotalkfile, line))
		{
			if (line[0] == '[')
			{
				Process(line);
			}
		}
	}
	kakaotalkfile.close();
}

void KakaotalkAnalyze::Process(std::string sentence)
{
	int idx = 1;
	std::string tmp;
	Talk talk;

	while (sentence[idx] != ']')
	{
		tmp += sentence[idx];
		idx += 1;
	}

	talk._name = tmp;
	_name[tmp] += 1;
	tmp.clear();
	idx += 3;

	while (sentence[idx] != ':')
	{
		tmp += sentence[idx];
		idx += 1;
	}

	talk._time = tmp;
	_time[tmp] += 1;
	tmp.clear();
	idx += 5;

	while (idx < sentence.size())
	{
		tmp += sentence[idx];
		idx += 1;
	}

	talk._sentence = tmp;

	_talk.push(talk);
}

void KakaotalkAnalyze::AnalyzeName()
{
	for each (auto var in SortByValue(_name))
	{
		std::cout << var.first << " " << var.second << std::endl;
	}
}

void KakaotalkAnalyze::AnalyzeTime()
{
	for each (auto var in SortByValue(_time))
	{
		std::cout << var.first << " " << var.second << std::endl;
	}
}

std::vector<std::pair<std::string, int>> KakaotalkAnalyze::SortByValue(std::map<std::string, int> map)
{
	std::vector<std::pair<std::string, int>> pairs;
	for (auto itr = map.begin(); itr != map.end(); ++itr)
		pairs.push_back(*itr);

	sort(pairs.begin(), pairs.end(), [=](std::pair<std::string, int>& a, std::pair<std::string, int>& b)
	{
		return a.second > b.second;
	}
	);
	return pairs;
}