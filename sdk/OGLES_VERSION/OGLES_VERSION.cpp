// OGLES_VERSION.cpp : ���� DLL Ӧ�ó���ĵ���������
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