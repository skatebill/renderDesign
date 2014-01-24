#pragma once
#include"appTypes.h"
#include <tools/MyTypes.h>
//#include<site/site.h>
#include<functional>

namespace xc{
	namespace app{
		static const int rongcha = 3;
		class IApplication{
		private:
			//shared_ptr<ISite> mSite;
			void* m_Extra;
		public:
			//! 安装站点
		//	void installSite(shared_ptr<ISite> site){
		//		mSite=site;
		//	}
		//	inline shared_ptr<ISite> getSite(){
		//		return mSite;
		//	}
			inline void* getExtraData(){
				return m_Extra;
			}
			void setExtra(void* ex){
				m_Extra = ex;
			}
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