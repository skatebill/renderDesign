#include<PVRShell.h>
#include<OGLES_VERSION.h>
#include<GLES2/gl2.h>
#include<fstream>
#include<waterParticle.h>
using namespace xc::draw;
using namespace xc;
class myShell:public PVRShell{
public:
	shared_ptr<IContext3D> mContext;
	shared_ptr<IDrawer3D> mDrawer;

	shared_ptr<IDrawBuffer> mVbuf;
	typedef water::waterParticle<6000> particle_type;
	shared_ptr<particle_type> m_WaterParc;

	virtual bool InitApplication(){
		return true;
	}
	virtual bool InitView(){
		mDrawer = createGLES2Drawer();
		mContext = createGLES2Context();
		m_WaterParc = 	shared_ptr<particle_type>(new particle_type(WaterRasterize::createWorld("V455-F1-01.vmf")));
		mVbuf = mContext->getBufferFactory()->createVertexBuffer();
		m_WaterParc->mRenderFunc = [this](){
			auto cp = mDrawer->getPathContext()->getColorPath();
			cp->setColor(color::RED);
			vector3df* buf =  (vector3df*)mVbuf->lock();
			int n=0;
			double l = m_WaterParc->left;
			double t = m_WaterParc->top;
			double w = m_WaterParc->width;
			double h = m_WaterParc->height;
			for (auto ite = m_WaterParc->m_Particles.begin();ite != m_WaterParc->m_Particles.end();++ite)
			{
				buf[n].X = (float((ite->p.X-l)/w)-0.5f)*2;
				buf[n].Y = (float((ite->p.Y-t)/h)-0.5f)*2;
				buf[n].Z = 0;
				n++;
			}
			mVbuf->uploadBuffer();
			cp->activate();
			mDrawer->render(mVbuf,m_WaterParc->m_Particles.size(),draw::EPT_DOTS);
			cp->deActivate();
		};
		mVbuf->reSizeBuffer(3*4*particle_type::maxParticles);
		mVbuf->setElemtSize(3);
		mVbuf->setDataType(EDT_FLOAT);
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
		m_WaterParc->update(10);
		m_WaterParc->mRenderFunc();
		return true;

	}
};
PVRShell* NewDemo()
{
	return new myShell();
}