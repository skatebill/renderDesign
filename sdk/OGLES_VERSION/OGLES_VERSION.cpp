// OGLES_VERSION.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "OGLES_VERSION.h"
#include"src/ESContext.h"
namespace xc{
	namespace draw{
		OGLES_VERSION_API shared_ptr<IContext3D> createGLES2Context(){
			return createPtr<ESContext>();
		}
		OGLES_VERSION_API shared_ptr<IDrawer3D> createGLES2Drawer(){
			return nullptr;
		}
	}
}