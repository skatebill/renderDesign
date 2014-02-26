#include<PVRShell.h>
#include<OGLES_VERSION.h>
#include<GLES2/gl2.h>
#include<fstream>
using namespace xc::draw;
using namespace xc;
class myShell:public PVRShell{
public:
	shared_ptr<IContext3D> mContext;
	shared_ptr<IDrawer3D> mDrawer;

	shared_ptr<IDrawBuffer> mVbuf;
	shared_ptr<IDrawIndexBuffer> mIbuf;

	shared_ptr<IDrawBuffer> mVbuf2;
	long nums;

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

		glClearColor(0,0,0,0);
		std::ifstream inFile("V455-F1-01.vmf");
		inFile>>nums;
		nums = nums;
		mVbuf2 = mContext->getBufferFactory()->createVertexBuffer();
		mVbuf2->reSizeBuffer(sizeof(vector3df)*nums);
		mVbuf2->setElemtSize(3);
		mVbuf2->setDataType(EDT_FLOAT);
		auto buf2 = (vector3df*)mVbuf2->lock();
		float vx,vy;
		float maxx,maxy,minx,miny;
		for(unsigned int i=0;i<nums;++i){
			inFile>>buf2[i].X>>buf2[i].Y>>vx>>vy;
			buf2[i].Z=0;
			if(i == 0){
				maxx = buf2[i].X;
				minx = buf2[i].X;
				maxy = buf2[i].Y;
				miny = buf2[i].Y;
			}else{
				maxx = std::max(maxx,buf2[i].X);
				minx = std::min(minx,buf2[i].X);
				maxy = std::max(maxy,buf2[i].Y);
				miny = std::min(miny,buf2[i].Y);

			}
		}
		float dx=maxx-minx,dy=maxy-miny;
		for(unsigned int i=0;i<nums;++i){
			buf2[i].X = (buf2[i].X - minx)/dx*2-1;
			buf2[i].Y = (buf2[i].Y - miny)/dx*2-1;

		}
		mVbuf2->uploadBuffer();
		return true;

	}
	virtual bool ReleaseView(){
		return true;

	}
	virtual bool QuitApplication(){
		return true;

	}
	virtual bool RenderScene(){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		auto cp = mDrawer->getPathContext()->getColorPath();
		cp->activate();
		cp->setColor(color::GREEN);
		//mDrawer->render(mVbuf,mIbuf,EPT_TRIANGLES);
		mVbuf2->use(0);
		//mIbuf->use();
		//glDrawElements(GL_POINTS,6,GL_UNSIGNED_BYTE,0);
		mDrawer->render(mVbuf2,nums,EPT_DOTS);
		//glDrawArrays(GL_POINTS,0,nums);
		cp->deActivate();
		return true;

	}
};
PVRShell* NewDemo()
{
	return new myShell();
}