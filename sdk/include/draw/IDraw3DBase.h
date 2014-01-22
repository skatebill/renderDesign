#pragma once
#include <service/file/IImage.h>
namespace xc{
	namespace draw{
#pragma region BUFFERS
		enum EnumIndexType{
			EIT_UBYTE=1,
			EIT_USHORT=2,
			EIT_UINT=4
		};
		enum EnumDataType{
			EDT_FLOAT,
			EDT_UINT,
			EDT_INT,
			EDT_DOUBLE,
			EDT_USHORT,
			EDT_SHORT,
			EDT_UBYTE,
			EDT_BYTE
		};
		class IDrawBuffer{
		public:
			//! lock out �ڲ��Ļ��������ٸ�������֮��
			virtual unsigned char* lock()=0;
			//! ��ȡ��������С
			virtual unsigned int getBufferSize()=0;
			//! �ض��建������С
			virtual void reSizeBuffer(unsigned int size)=0;
			//! �����ڲ�Ԫ��һ���ж��ٸ�
			virtual void setElemtSize(unsigned int nums)=0;
			//! ��ָ��λ��ʹ�ô˻���
			virtual void use(int slot)=0;
			//! ʹ�����
			virtual void unUse(int slot)=0;
			//! ��ʼ��������(�����ݸ��ĺ����һ�¿����ϴ������ݵ��Դ���)
			virtual void uploadBuffer()=0;
			//! ������������
			virtual void setDataType(EnumDataType t)=0;
		};
		class IDrawIndexBuffer{
		public:
			//! lock out �ڲ��Ļ��������ٸ�������֮��
			virtual unsigned char* lock()=0;
			//! ��ȡ��������С
			virtual unsigned int getBufferSize()=0;
			//! �ض��建������С
			virtual void reSizeBuffer(unsigned int size)=0;
			//! ʹ�ô˻���
			virtual void use()=0;
			//! ʹ�����
			virtual void unUse()=0;
			//! ��ʼ��������(�����ݸ��ĺ����һ�¿����ϴ������ݵ��Դ���)
			virtual void uploadBuffer()=0;
			//! ���û��Ƶ���������
			virtual void setIndexNums(unsigned int n)=0;
			//! ��ȡ��Ҫ���Ƶ���������
			virtual unsigned int getIndexNums()=0;
			//! ��ȡ��������
			virtual EnumIndexType getIndexType()=0;
		};

		class IDrawVertexBufferOBject{
		public:
			//! ʹ�ô˻�����
			virtual void use()=0;
			//! ʹ�����
			virtual void unUse()=0;
			//! ��ȡ��Ҫ���Ƶ���������
			virtual unsigned int getIndexNums()=0;
			//! ��ȡ��������
			virtual EnumIndexType getIndexType()=0;
		};
		class IDrawBufferFactory{
		public:
			//! �������㻺����
			virtual shared_ptr<IDrawBuffer> createVertexBuffer()=0;
			//! ��������������
			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer()=0;
			//! ����������VBO
			virtual shared_ptr<IDrawVertexBufferOBject> createVertexBufferObject(shared_ptr<IDrawBuffer> vbuf,
				shared_ptr<IDrawIndexBuffer> ibuf,
				shared_ptr<IDrawBuffer> buf1=0,
				shared_ptr<IDrawBuffer> buf2=0,
				shared_ptr<IDrawBuffer> buf3=0,
				shared_ptr<IDrawBuffer> buf4=0)=0;

		};
#pragma endregion BUFFERS
#pragma region TEXTURE
		class ITexture{
		public:
			//! ��ȡ������С
			virtual vector2di getTextureSize()=0;
		};
		class ITextureTarget{
		public:
			//! ��ѯ��rtt�Ƿ�߱����ֻ���
			virtual bool hasDepthBuffer()=0;
			virtual bool hasStencilBuffer()=0;
		};
		class ITextureFactory{
		public:
			//! ��������
			shared_ptr<ITexture> createTextureFromImage(shared_ptr<fileservice::IImage>)=0;
			//! ����rtt
			shared_ptr<ITextureTarget> createTextureTarget(int width,int height,bool depth,bool stencil)=0;

		};
#pragma endregion TEXTURE
		class IContext3D{
		public:
			//!��ȡ��������
			shared_ptr<ITextureFactory> getTextureFactory()=0;
			//!��ȡ���幤��
			shared_ptr<IDrawBufferFactory> getBufferFactory()=0;
		};
		class IDrawer3D{

		};
	}
}