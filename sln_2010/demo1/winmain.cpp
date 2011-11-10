#include <application/paltform/windows.h>

class App:public xc::app::IApplication{


	virtual void onInitialWindow( std::function<void(const wchar_t* ) > namefun,std::function<void(unsigned int,unsigned int)> sizeFun)
	{
		namefun(L"demo 1");
		sizeFun(800,600);
	}

	virtual void onInitialData() 
	{
	}

	virtual void onCleanup() 
	{
	}

	virtual void onRender() 
	{
	}

};


xc::shared_ptr<xc::app::IApplication> xc::app::createApp(){
	return shared_ptr<xc::app::IApplication>(new App);
}