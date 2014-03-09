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
			//	�ӿ�
			//  UI �¼�
			//! ��ʼ��������Ϣ
			virtual void onInitialWindow(std::function<void(const wchar_t*)> namefun,std::function<void(unsigned int,unsigned int)> sizeFun)=0;
			//! ����¼�
			virtual void onMouseEvent(EnumMouse,MouseEvent,vector2di){}
			//! �����¼�
			virtual void onKeyEvent(KeyEvent key,int keyCode){}
			//! ��ʼ��
			virtual void onInitialData()=0;
			//! ����
			virtual void onCleanup()=0;
			//! ����
			virtual void onRender()=0;
		};
		shared_ptr<IApplication> createApp();
	}
}