#pragma once
#include"appTypes.h"
#include <tools/MyTypes.h>
#include<functional>

namespace xc{
	namespace app{
		static const int rongcha = 3;
		class IApplication{
		public:
			void exitApp();
			//////////////////////////////////////////////////////////////////////////
			//	接口
			//  UI 事件
			//! 初始化窗口信息
			virtual void onInitialWindow(std::function<void(const wchar_t*)> namefun,std::function<void(unsigned int,unsigned int)> sizeFun)=0;
			//! 鼠标事件
			virtual void onMouseEvent(EnumMouse,MouseEvent,vector2di){}
			//! 键盘事件
			virtual void onKeyEvent(KeyEvent key,int keyCode){}
			//! 初始化
			virtual void onInitialData()=0;
			//! 销毁
			virtual void onCleanup()=0;
			//! 绘制
			virtual void onRender()=0;
		};
		shared_ptr<IApplication> createApp();
	}
}