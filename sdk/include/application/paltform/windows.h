#include <windows.h>
#include<application/IApplication.h>
#include<application/appTypes.h>
//#include<gl/glew.h>
//#include<COpenglFactory.h>
//#include<site/site.h>
//#include<service/CFileService.h>
//#include<viewer/CViewFactory.hpp>
//#include<phraser/CAssimpPhraser.h>
//#pragma comment (lib, "winmm.lib")     /* link with Windows MultiMedia lib */
//#pragma comment (lib, "opengl32.lib")  /* link with Microsoft OpenGL lib */
//#pragma comment (lib, "glu32.lib")     /* link with OpenGL Utility lib */
namespace temp{
	HWND hwnd;
	const wchar_t* windowName=L"";
	xc::shared_ptr<xc::app::IApplication> appInti;
	unsigned int width=800;
	unsigned int height=600;

	void setWindowName(const wchar_t* name){
		windowName = name;
	}
	void setWindowSize(unsigned int w,unsigned int h){
		width = w;
		height = h;
	}
}
bool lButtonDown;
bool rButtonDown;
LPARAM oldLButton;
LPARAM oldRButton;
void xc::app::IApplication::exitApp(){
	PostQuitMessage(0);
}
//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	using namespace xc::app;
	using namespace xc;
	using namespace temp;
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	case WM_LBUTTONDOWN:
		lButtonDown = true;
		oldLButton = lParam;
		{
			int x=LOWORD(lParam);
			int	y=HIWORD(lParam);
			appInti->onMouseEvent(Mouse_L,Mouse_Down,vector2di(x,y));
		}
		break;
	case WM_RBUTTONDOWN:
		rButtonDown = true;
		oldRButton = lParam;
		{
			int x=LOWORD(lParam);
			int	y=HIWORD(lParam);
			appInti->onMouseEvent(Mouse_R,Mouse_Down,vector2di(x,y));
		}
		break;
	case WM_LBUTTONUP:
		{
			int x=LOWORD(lParam);
			int	y=HIWORD(lParam);
			appInti->onMouseEvent(Mouse_L,Mouse_Up,vector2di(x,y));
			if(lButtonDown){
				int ox=LOWORD(oldLButton);
				int oy=HIWORD(oldLButton);
				if(abs(ox-x)<xc::app::rongcha && abs(oy-y)<xc::app::rongcha){
					appInti->onMouseEvent(Mouse_L,Mouse_Click,vector2di(x,y));
				}
			}
			lButtonDown=false;
		}
		break;
	case WM_RBUTTONUP:
		{
			int x=LOWORD(lParam);
			int	y=HIWORD(lParam);
			appInti->onMouseEvent(Mouse_R,Mouse_Up,vector2di(x,y));
			if(rButtonDown){
				int ox=LOWORD(oldRButton);
				int oy=HIWORD(oldRButton);
				if(abs(ox-x)<xc::app::rongcha && abs(oy-y)<xc::app::rongcha){
					appInti->onMouseEvent(Mouse_R,Mouse_Click,vector2di(x,y));
				}
			}
			rButtonDown=false;
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			int x=LOWORD(lParam);
			int	y=HIWORD(lParam);
			appInti->onMouseEvent(Mouse_L,Mouse_DClick,vector2di(x,y));
		}
		break;
	case WM_RBUTTONDBLCLK:
		{
			int x=LOWORD(lParam);
			int	y=HIWORD(lParam);
			appInti->onMouseEvent(Mouse_R,Mouse_DClick,vector2di(x,y));
		}
		break;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}
void create( HINSTANCE hInstance ,int w,int h)
{

	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )107 );
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MyWindowClass";
	wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )107 );
	if( !RegisterClassEx( &wcex ) )
		return;
	DWORD styles = (CS_OWNDC|WS_OVERLAPPEDWINDOW) & ~(WS_SIZEBOX |WS_MAXIMIZEBOX|WS_MINIMIZEBOX) ;
	RECT rc = { 0, 0, w, h };
	AdjustWindowRect( &rc, styles , FALSE);

	int screenW=GetSystemMetrics(SM_CXSCREEN);
	int screenH=GetSystemMetrics(SM_CYSCREEN);
	int newposx= (screenW>>1)-((rc.right - rc.left)>>1);
	int newposy= (screenH>>1)-((rc.bottom - rc.top)>>1);

	temp::hwnd = CreateWindow( L"MyWindowClass", temp::windowName, styles,
		newposx, newposy, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL );
	if( !temp::hwnd )
		return;
	//xc::ISiteEdieable* s=new xc::ISiteEdieable;
	//temp::appInti->installSite(xc::shared_ptr<xc::ISite>(s));
	//auto df = new xc::drawBasement::COpenglFactory;
	//df->createDrawContext(temp::hwnd);
	//s->installDrawFactory(xc::shared_ptr<xc::drawBasement::IDrawFactory>(df));
	//s->installFileService(xc::shared_ptr<xc::fileservice::IFileService>(new xc::fileservice::CFileService));
	//s->installViewerFactory(xc::shared_ptr<xc::viewer::IViewerFactory>(new xc::viewer::CViewFactory));
	//s->installPhraser(xc::phraser::createAssimpPhraserService(s->getFileService(),s->getDrawFactory()));

	ShowWindow( temp::hwnd, SW_SHOW );
}

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	temp::appInti = xc::app::createApp();
	temp::appInti->onInitialWindow(temp::setWindowName,temp::setWindowSize);
	create(hInstance,temp::width,temp::height);
	temp::appInti->onInitialData();
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			temp::appInti->onRender();
		}

	}
}
