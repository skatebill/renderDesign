#pragma once
#include <draw/IDraw3DBase.h>
#include<GLES2/gl2.h>
namespace xc{
	namespace draw{
		class ESTexture:public ITexture{
		public:
			GLuint m_TexHandle;
			vector2di m_TexSize;
			GLuint m_CurrentSlot;

			ESTexture();
			~ESTexture();
			virtual vector2di getTextureSize();

			virtual void use( int slot );

			virtual void unUse();

		};

		class ESTextureFactory:public ITextureFactory{
		public:

			virtual shared_ptr<ITexture> createTextureFromImage( shared_ptr<fileservice::IImage> );

			virtual shared_ptr<ITextureTarget> createTextureTarget( int width,int height,bool depth=true,bool stencil=true );

		};
	}
}