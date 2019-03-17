#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#include "Fatal.h"

#include <iostream>

template<typename T> 
class LinkListNode
{
public:
	T element;
	LinkListNode<T> *next;
};

#define PLinkListNode LinkListNode<T>*

template<typename T>
class LinkList
{
private:
	PLinkListNode _head;

public:
	LinkList()
	{
		_head = new LinkListNode<T>();
		if (_head == nullptr)
		{
			Error("out of memory");
		}
		//_head->element = nullptr;
		_head->next = nullptr;
	}

	~LinkList()
	{
		PLinkListNode pos;
		PLinkListNode tmp;
		pos = _head->next;
		_head->next = nullptr;
		while (pos != nullptr)
		{
			tmp = pos->next;
			delete pos;
			pos = tmp;
		}
		delete _head;
	}

	bool IsEmpty()
	{
		return _head->next == nullptr;
	}

	bool IsLast(PLinkListNode L)
	{
		return L->next == nullptr;
	}

	void MakeEmpty()
	{
		PLinkListNode tmp;
		PLinkListNode pos = _head->next;
		_head->next = nullptr;
		while (pos != nullptr)
		{
			tmp = pos->next;
			delete pos;
			pos = tmp;
		}
	}

	PLinkListNode Find(T ele, PLinkListNode L)
	{
		PLinkListNode pos;
		pos = L->next;
		while (pos != nullptr && pos->element != ele) pos = pos->next;
		return pos;
	}

	PLinkListNode FindPrevious(T ele, PLinkListNode L)
	{
		PLinkListNode pos;
		pos = L;
		while (pos->next != nullptr && pos->next->element != ele) pos = pos->next;
		return pos;
	}

	void Delete(T ele, PLinkListNode L)
	{
		PLinkListNode pos, tmpPos;
		pos = FindPrevious(ele, L);
		if (!IsLast(pos, L))
		{
			tmpPos = pos->next;
			pos->next = tmpPos->next;
			delete tmpPos;
		}
	}

	void Push(T ele)
	{
		PLinkListNode tmpNode = new LinkListNode<T>();
		if (tmpNode == nullptr) Error("out of memory");
		tmpNode->next = nullptr;
		tmpNode->element = ele;
		PLinkListNode pos;
		pos = _head;
		while (pos->next != nullptr) pos = pos->next;
		pos->next = tmpNode;
	}

	void Insert(T ele, PLinkListNode pos)
	{
		if (pos == null)  Error("error pos");
		PLinkListNode tmpNode = new LinkListNode<T>();
		if (tmpNode == nullptr) Error("out of memory");
		tmpNode->element = ele;
		tmpNode->next = pos->next;
		pos->next = tmpNode;
	}

	/*
	PLinkListNode Header(PLinkListNode L);
	PLinkListNode First(PLinkListNode L);
	PLinkListNode Advance(PLinkListNode P);
	T Retrieve(PLinkListNode P);
	*/
};

#endif //!__LINK_LIST_H__