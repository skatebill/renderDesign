#include<PVRShell.h>
#include<OGLES_VERSION.h>
#include<GLES2/gl2.h>
using namespace xc::draw;
using namespace xc;
class myShell:public PVRShell{
public:
	shared_ptr<IContext3D> mContext;
	shared_ptr<IDrawer3D> mDrawer;

	shared_ptr<IDrawBuffer> mVbuf;
	shared_ptr<IDrawIndexBuffer> mIbuf;

	virtual bool InitApplication(){
		return true;
	}
	virtual bool InitView(){
		mDrawer = createGLES2Drawer();
		mContext = createGLES2Context();

		mVbuf = mContext->getBufferFactory()->createVertexBuffer();
		mVbuf->reSizeBuffer(sizeof(vector3df)*4);
		mVbuf->setElemtSize(3);
		mVbuf->setDataType(EDT_FLOAT);

		auto buf = (vector3df*)mVbuf->lock();
		buf[0]=vector3df(-0.5f,-0.5f,0);
		buf[1]=vector3df(0.5f,-0.5f,0);
		buf[2]=vector3df(0.5f,0.5f,0);
		buf[3]=vector3df(-0.5f,0.5f,0);

		mVbuf->uploadBuffer();

		mIbuf = mContext->getBufferFactory()->createIndexBuffer();
		mIbuf->setIndexNums(6);
		mIbuf->reSizeBuffer(6);
		auto ibuf = mIbuf->lock();
		ibuf[0]=0;
		ibuf[1]=1;
		ibuf[2]=2;
		ibuf[3]=0;
		ibuf[4]=2;
		ibuf[5]=3;
		mIbuf->uploadBuffer();

		glClearColor(1,0,0,1);
		return true;

	}
	virtual bool ReleaseView(){
		return true;

	}
	virtual bool QuitApplication(){
		return true;

	}
	virtual bool RenderScene(){
		glClear(GL_COLOR_BUFFER_BIT);

		mVbuf->use(0);
		mIbuf->use();
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);
		return true;

	}
};
PVRShell* NewDemo()
{
	return new myShell();
}