//	Application.cpp

#include "Application.h"

namespace neko
{

Application::Application(){}
Application::~Application(){}

bool Application::Init()
{
	{
		//	Set the application path to the executable path
		wchar_t sT[MAX_PATH];
		::GetModuleFileNameW(NULL, sT, MAX_PATH);
		int iP = lstrlenW(sT);
		
		while(iP > 0
			&& (sT[iP - 1] != L'/')
			&& (sT[iP] != L'\\'))
		{
			iP--;
		}

		sT[iP] = L'\0';
		_wchdir(sT);
	}

	::timeBeginPeriod(1);

	return true;
}

void Application::Shut()
{

}

void Application::Start()
{

}

void Application::Run()
{

}

}	//	namespace neko