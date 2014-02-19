// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� OGLES_VERSION_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// OGLES_VERSION_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef OGLES_VERSION_EXPORTS
#define OGLES_VERSION_API __declspec(dllexport)
#else
#define OGLES_VERSION_API __declspec(dllimport)
#endif

#include<draw/IDraw3DBase.h>
#include<draw/IDrawer3D.h>
namespace xc{
	namespace draw{
		OGLES_VERSION_API shared_ptr<IContext3D> createGLES2Context();
		OGLES_VERSION_API shared_ptr<IDrawer3D> createGLES2Drawer();
	}
}
