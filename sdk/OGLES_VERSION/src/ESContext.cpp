#include"ESContext.h"
#include"ESBuffers.h"
#include"ESTexture.h"
namespace xc{
	namespace draw{


		ESContext::ESContext(){
			mTexFactory = shared_ptr<ITextureFactory>(new ESTextureFactory);
			mBufferFactory = shared_ptr<IDrawBufferFactory>(new ESBufferFactory);
		}
		shared_ptr<ITextureFactory> xc::draw::ESContext::getTextureFactory()
		{
			return mTexFactory;
		}

		shared_ptr<IDrawBufferFactory> xc::draw::ESContext::getBufferFactory()
		{
			return mBufferFactory;
		}

	}
}