#include "Indexer.h"


Indexer::Indexer()
{
}

Indexer::~Indexer()
{
}

void Indexer::setIndexerData(const string& data)
{
	// Извлечение тела
	int begin = data.find("<body");
	int end = data.find("</body>");
	page_ = data.substr(begin, end - begin);

	// Приведение к единой строке
	page_.erase(remove(page_.begin(), page_.end(), '\n'), page_.end());

	// Извлечение ссылок

	// Лаконичный, но ООО-чень медленный код
	/*
	regex rx(".*(href=[a-z0-9._]+)>.*"); // Почему-то не срабатывает ".*href=([\w.]+)>.*"
	smatch sm;
	bool found;
	do {
		found = regex_search(page_.cbegin(), page_.cend(), sm, rx);
		if (found)
		{
			links_.push_back(sm.str(1));
			page_.at(sm.position(1)) = ' ';
		}
	} while (found);
	*/

	const char* search_head = "href=";
	const int len_head = 5;
	const char* search_tail = ">";
	begin = 0;
	bool found = false;
	do {
		begin = page_.find(search_head, begin);

		if (begin != std::string::npos)
		{
			end = page_.find(search_tail, begin);
			links_.push_back(page_.substr(begin + len_head, end - begin - len_head));
			begin++;
			found = true;
		}
		else found = false;
	} while (found);

	// Очистка от HTML тегов
	bool tagDetected = false;
	int posHeadTag = 0;
	int posTailTag = 0;
	for (int i = page_.length() - 1; i >= 0; --i)
	{
		if (page_.at(i) == '>')
		{
			tagDetected = true;
			posTailTag = i;
		}
		if (tagDetected && page_.at(i) == '<')
		{
			posHeadTag = i;
			page_.erase(posHeadTag, posTailTag - posHeadTag + 1);
			tagDetected = false;
		}
	}

	// Извлечение слов
	regex w("([а-яА-Я]+)");
	for (int i = 0; i < page_.length(); ++i)
	{
		if (!tagDetected && (page_.at(i) != ' ' && page_.at(i) != '/t'))
		{
			posHeadTag = i;
			tagDetected = true;
		}
		if (tagDetected && (page_.at(i) == ' ' || page_.at(i) == '/t'))
		{
			posTailTag = i;
			cout << '[' << page_.substr(posHeadTag, posTailTag - posHeadTag) << ']' << '\n';
			string substr = page_.substr(posHeadTag, posTailTag - posHeadTag);
			if (regex_match(substr, w))
			{
				if (substr.length() >= 3 && substr.length() <= 24)
					worlds_.push_back(to_lower_copy(substr, std::locale{ "Russian" }));
			}
			tagDetected = false;
		}
	}



	for (auto w : worlds_)
	{
		cout << w.length() << '\t' << '[' << w << ']' << '\n';

		cout << tr.CheckWord(w);
	}
}


