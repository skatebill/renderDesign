#pragma once
#include <tools/MyTypes.h>
namespace xc{
	namespace draw{
		enum EnumDrawFunctions{
			EDF_2d_base=0,
			EDF_3d_base,
			EDF_3d_more_pipeline,
			EDF_3d_feedbackBuffer
		};
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
		};
	}
}