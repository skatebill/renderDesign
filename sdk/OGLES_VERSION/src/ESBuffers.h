#pragma once
#include<draw/IDraw3DBase.h>
#include<GLES2/gl2.h>
#include <vector>
namespace xc{
	namespace draw{
		class ESVertexBuffer:public IDrawBuffer{
		public:
			unsigned int m_Size;
			unsigned int m_ElementSize;
			unsigned char* m_Buff;
			GLuint m_VBO;
			GLuint mDataType;

			explicit ESVertexBuffer();
			~ESVertexBuffer();

			//lock out 内部的缓冲区
			virtual unsigned char* lock();
			//! 获取缓冲区大小
			virtual unsigned int getBufferSize(){
				return m_Size;
			}
			//! 重定义缓冲区大小
			virtual void reSizeBuffer(unsigned int size);
			//! 在指定位置使用此缓冲
			virtual void use(int slot);

			//! 设置内部元素一组有多少个
			virtual void setElemtSize(unsigned int nums){
				m_ElementSize = nums;
			}
			//! 初始化缓冲区
			virtual void initialBuffer();
			//! 释放资源
			virtual void unUse(int slot);

			//! 设置数据类型
			virtual void setDataType(EnumDataType t);

			virtual void uploadBuffer();

		};
		class ESIndexBuffer:public ESVertexBuffer,public IDrawIndexBuffer{
		public:
			GLuint m_IBO;
			unsigned int m_IndexNum;
			EnumPrimaryType m_EPT;
			EnumIndexType m_EIT;

			explicit ESIndexBuffer();
			~ESIndexBuffer();
			//! 在指定位置使用此缓冲
			virtual void use();
			//! 初始化缓冲区
			virtual void initialBuffer();

			//! lock out 内部的缓冲区
			virtual unsigned char* lock(){
				return ESVertexBuffer::lock();
			}
			//! 获取缓冲区大小
			virtual unsigned int getBufferSize(){
				return ESVertexBuffer::getBufferSize();
			}
			//! 重定义缓冲区大小
			virtual void reSizeBuffer(unsigned int size){
				ESVertexBuffer::reSizeBuffer(size);
			}
			//! 获取需要绘制的索引个数
			virtual unsigned int getIndexNums(){
				return m_IndexNum;
			}
			//! 设置绘制的索引个数
			virtual void setIndexNums(unsigned int n){
				m_IndexNum=n;
			}
			//! 获取需要绘制的图元类型
			virtual EnumPrimaryType getPrimaryType(){
				return m_EPT;
			}
			//! 获取数据类型
			virtual EnumIndexType getIndexType(){
				return m_EIT;
			}
			//! 设置图元类型
			virtual void setPrimityType(EnumPrimaryType type){
				m_EPT = type;
			}

			virtual void unUse(){

			}

			virtual void uploadBuffer();


		};

		class ESVertexBufferObject:public IDrawVertexBufferOBject{
		private:
		public:
			std::vector<shared_ptr<IDrawBuffer>> m_vertexList;
			shared_ptr<IDrawIndexBuffer> m_indexBuffer;
			ESVertexBufferObject();
			~ESVertexBufferObject();
			//! 开始初始化
			void initialStart();
			//! 结束初始化
			void initialEnd();
			//! 绑定顶点缓冲
			void addVertexBuf(shared_ptr<IDrawBuffer> vbuf);
			//! 绑定索引缓冲
			void bindIndexBuf(shared_ptr<IDrawIndexBuffer> ibuf);
			//! 使用此缓冲区
			virtual void use();
			//! 使用完毕
			virtual void unUse();
			//! 获取需要绘制的索引个数
			virtual unsigned int getIndexNums();
			//! 获取默认图元类型
			virtual EnumPrimaryType getPrimaryType();
			//! 获取数据类型
			virtual EnumIndexType getIndexType();
		};
		class ESBufferFactory:public IDrawBufferFactory{
		public:
			virtual shared_ptr<IDrawBuffer> createVertexBuffer();

			virtual shared_ptr<IDrawIndexBuffer> createIndexBuffer();

			virtual shared_ptr<IDrawVertexBufferOBject> createVertexBufferObject( shared_ptr<IDrawBuffer> vbuf, shared_ptr<IDrawIndexBuffer> ibuf, shared_ptr<IDrawBuffer> buf1=0, shared_ptr<IDrawBuffer> buf2=0, shared_ptr<IDrawBuffer> buf3=0, shared_ptr<IDrawBuffer> buf4=0 );

		};
	}
}