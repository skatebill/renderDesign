#pragma once
#include <draw/IDraw3DBase.h>
namespace xc{
	namespace draw{
		class ESContext:public IContext3D{
		public:
			ESContext();
			shared_ptr<ITextureFactory> mTexFactory;
			shared_ptr<IDrawBufferFactory> mBufferFactory;

			virtual shared_ptr<ITextureFactory> getTextureFactory();

			virtual shared_ptr<IDrawBufferFactory> getBufferFactory();

		};
	}
}