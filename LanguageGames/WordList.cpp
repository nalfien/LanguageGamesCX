#include "pch.h"
#include "WordList.h"

struct WordNode
{
	std::wstring word;
	WordNode* next;
};

WordList::WordList()
{
}

WordList::WordList(std::wstring sentence, char separator)
{
	size_t pos = 0;
	while ((pos = sentence.find(separator)) != std::wstring::npos)
	{
		add(sentence.substr(0, pos));
		sentence.erase(0, pos + 1);
	}
}

WordList::~WordList()
{
}

WordNode* WordList::add(std::wstring wordToAdd)
{
	WordNode* newNode = new WordNode;
	newNode->word = wordToAdd;
	newNode->next = NULL;

	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = tail->next;
	}

	return newNode;
}

WordNode* WordList::GetHead()
{
	return head;
}