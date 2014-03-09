#include"CCamera.hpp"
#include"CMatStack.hpp"
#include"IViewFactory.h"

namespace xc{
	namespace viewer{
		class CViewFactory:public IViewerFactory{
		public:
		public:
			//! 创建摄像机
			virtual shared_ptr<ICamera> createCamera(){
				return shared_ptr<ICamera>(new CCamera);
			}
			//! 创建矩阵堆栈
			virtual shared_ptr<IMatStack> createMatStack(){
				return shared_ptr<IMatStack>(new CMatStack);
			}

		};

		shared_ptr<IViewerFactory> createViewFactory(){
			return shared_ptr<IViewerFactory>(new CViewFactory);
		}
	}
}