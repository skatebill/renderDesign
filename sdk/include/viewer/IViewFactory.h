#pragma once
#include "IMatrixStack.h"
#include"ICamera.h"
namespace xc{
	namespace viewer{
		class IViewerFactory{
		public:
			//! 创建摄像机
			virtual shared_ptr<ICamera> createCamera()=0;
			//! 创建矩阵堆栈
			virtual shared_ptr<IMatStack> createMatStack()=0;
		};
	}
}