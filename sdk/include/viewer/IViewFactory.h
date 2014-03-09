#pragma once
#include "IMatrixStack.h"
#include"ICamera.h"
namespace xc{
	namespace viewer{
		class IViewerFactory{
		public:
			//! ���������
			virtual shared_ptr<ICamera> createCamera()=0;
			//! ���������ջ
			virtual shared_ptr<IMatStack> createMatStack()=0;
		};
	}
}