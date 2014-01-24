#pragma once
#include<draw/IDrawPath.h>
namespace xc{
	namespace draw{
		class IDrawer3D{
		public:
			virtual void pushRTT(shared_ptr<ITextureTarget> rtt)=0;
			virtual void popRTT()=0;
			virtual void setViewPort(recti viewport)=0;
			virtual void enableFeature()=0;
			virtual void disableFeature()=0;
			//! ‰÷»æ
			virtual void render(shared_ptr<IDrawPath> path,shared_ptr<IDrawVertexBufferOBject> vbo,EnumPrimityType pt=EPT_TRIANGLES)=0;
			virtual void render(shared_ptr<IDrawPath> path,shared_ptr<IDrawBuffer> vbuf,shared_ptr<IDrawIndexBuffer> ibuf,EnumPrimityType pt=EPT_TRIANGLES)=0;
			virtual void render(shared_ptr<IDrawPath> path,shared_ptr<IDrawBuffer> vbuf,u32 num,EnumPrimityType pt=EPT_TRIANGLES)=0;
		};
	}
}