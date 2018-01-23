#pragma once

struct WordNode;

class WordList
{
public:
	WordList();
	WordList(std::wstring sentence, char separator);
	~WordList();
	WordNode* add(std::wstring wordToAdd);
	WordNode * GetHead();
private:
	WordNode* head = NULL;
	WordNode* tail = NULL;
};
