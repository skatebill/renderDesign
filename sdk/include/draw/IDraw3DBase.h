#pragma once
#include <service/file/IImage.h>
#include <tools/MyTypes.h>
namespace xc{
	namespace draw{
		//! 图元类型枚举
		enum EnumPrimityType
		{
			EPT_DOTS=0,
			EPT_LINES,
			EPT_LINE_STRIP,
			EPT_TRIANGLES,
			EPT_TRIANGLE_STRIP
		};

		//! 比较模式
		enum enumCompare{
			NEVER=0,
			ALWAYS,
			LESS,
			GREATER,
			EQUAL,
			LEQUAL,
			GEQUAL,
			NOTEQUAL
		};
		//! 模板操作
		enum enumStencilOperation{
			KEEP=0,
			ZERO,
			REPLACE,
			INCR,
			DECR,
			INVERT,
			INCR_WRAP,
			DECR_WRAP
		};
		//! 混合方式
		enum enumBlendFunc{
			ZERO,
			ONE,
			SRC_ALPHA,
			SRC_COLOR,
			DST_ALPHA,
			DST_COLOR,
			ONE_MINUS_SRC_ALPHA,
			ONE_MINUS_SRC_COLOR,
			ONE_MINUS_DST_ALPHA,
			ONE_MINUS_DST_COLOR
		};
		//渲染设置
		class SRenderConfig{
			bool stencil_test;
			bool stencil_buffer;
			enumCompare stencil_compare;
			//////////////////////////////////////////////////////////////////////////
			bool alpha_test;
			bool alpha_compare;
			//////////////////////////////////////////////////////////////////////////
			bool depth_test;
			bool depth_buffer;
			//////////////////////////////////////////////////////////////////////////
			bool blend;
			enumBlendFunc blend_func_src;
			enumBlendFunc blend_func_dst;
		};
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
			//! lock out 内部的缓冲区（再更改数据之后）
			virtual unsigned char* lock()=0;
			//! 获取缓冲区大小
			virtual unsigned int getBufferSize()=0;
			//! 重定义缓冲区大小
			virtual void reSizeBuffer(unsigned int size)=0;
			//! 设置内部元素一组有多少个
			virtual void setElemtSize(unsigned int nums)=0;
			//! 在指定位置使用此缓冲
			virtual void use(int slot)=0;
			//! 使用完毕
			virtual void unUse(int slot)=0;
			//! 初始化缓冲区(在数据更改后调用一下可以上传新数据到显存中)
			virtual void uploadBuffer()=0;
			//! 设置数据类型
			virtual void setDataType(EnumDataType t)=0;
		};
		class IDrawIndexBuffer{
		public:
			//! lock out 内部的缓冲区（再更改数据之后）
			virtual unsigned char* lock()=0;
			//! 获取缓冲区大小
			virtual unsigned int getBufferSize()=0;
			//! 重定义缓冲区大小
			virtual void reSizeBuffer(unsigned int size)=0;
			//! 使用此缓冲
			virtual void use()=0;
			//! 使用完毕
			virtual void unUse()=0;
			//! 初始化缓冲区(在数据更改后调用一下可以上传新数据到显存中)
			virtual void uploadBuffer()=0;
			//! 设置绘制的索引个数
			virtual void setIndexNums(unsigned int n)=0;
			//! 获取需要绘制的索引个数
			virtual unsigned int getIndexNums()=0;
			//! 获取数据类型
			virtual EnumIndexType getIndexType()=0;
		};

		class IDrawVertexBufferOBject{
		public:
			//! 使用此缓冲区
			virtual void use()=0;
			//! 使用完毕
			virtual void unUse()=0;
			//! 获取需要绘制的索引个数
			virtual unsigned int getIndexNums()=0;
			//! 获取数据类型
			virtual EnumIndexType getIndexType()=0;
		};
		class IDrawBufferFactory{
		public:
			//! 创建顶点缓冲区
			virtual shared_ptr<IDrawBuffer> createVertexBuffer()=0;
			//! 创建索引缓冲区
			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer()=0;
			//! 创建绘制用VBO
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
			//! 获取纹理大小
			virtual vector2di getTextureSize()=0;
		};
		class ITextureTarget{
		public:
			//! 查询此rtt是否具备各种缓存
			virtual bool hasDepthBuffer()=0;
			virtual bool hasStencilBuffer()=0;
		};
		class ITextureFactory{
		public:
			//! 创建纹理
			shared_ptr<ITexture> createTextureFromImage(shared_ptr<fileservice::IImage>)=0;
			//! 创建rtt
			shared_ptr<ITextureTarget> createTextureTarget(int width,int height,bool depth=true,bool stencil=true)=0;

		};
#pragma endregion TEXTURE
#pragma region LIGHT
		enum enumLightType{
			ELT_POINT=0,
			ELT_SPLOT,
			ELT_DIRECTION
		}
		struct SLight{
			vector3df pos;
			vector3df dir;
			//! 衰减系数
			float decayFactor;
			//! 漫反射光
			colorf ambiColor;
			//! 散射光
			colorf specColor;
			//! 环境光
			colorf envColor;
		};
		struct SMaterial{

			//! 透明度
			float alpha;
			//! 漫反射光
			colorf ambiColor;
			//! 散射光
			colorf specColor;
		};
#pragma endregion LIGHT
		class IContext3D{
		public:
			//!获取纹理工厂
			virtual shared_ptr<ITextureFactory> getTextureFactory()=0;
			//!获取缓冲工厂
			virtual shared_ptr<IDrawBufferFactory> getBufferFactory()=0;
		};
	}
}