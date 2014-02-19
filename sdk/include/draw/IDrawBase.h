#pragma once
#include <tools/MyTypes.h>
#include <draw/IDraw3DBase.h>
namespace xc{
	namespace draw{
		class IDrawer2D{

		};
		class IRenderToolSet{
		public:
			//! ��ѯ�����Ƿ�֧��
			virtual bool isFunctionSupported(EnumDrawFunctions request)=0;
			//! ��ȡ3d������
			virtual IDrawer3D* getDrawer3D()=0;
			//! ��ȡ2d������
			virtual IDrawer2D* getDrawer2D()=0;
			//! ��ȡ3d��context
			virtual IContext3D getConext3D()=0;
		};
	}
}