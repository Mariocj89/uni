#pragma once

#include <queue>
#include "afxwin.h"
#include "afxcmn.h"

using namespace std;

class ErrorConfig
{
public:

	ErrorConfig(void)
	{
		
	}

	void add(CString error)
	{
		problemas.push(error);
	}

	void what()
	{
		while(!problemas.empty())
		{
			AfxMessageBox(problemas.front());
			problemas.pop();
		}
	}

	void check()
	{
		if(!problemas.empty())
			throw this;
	}

	~ErrorConfig(void)
	{

	}


	queue<CString> problemas;
};
