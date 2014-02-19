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

			//lock out �ڲ��Ļ�����
			virtual unsigned char* lock();
			//! ��ȡ��������С
			virtual unsigned int getBufferSize(){
				return m_Size;
			}
			//! �ض��建������С
			virtual void reSizeBuffer(unsigned int size);
			//! ��ָ��λ��ʹ�ô˻���
			virtual void use(int slot);

			//! �����ڲ�Ԫ��һ���ж��ٸ�
			virtual void setElemtSize(unsigned int nums){
				m_ElementSize = nums;
			}
			//! ��ʼ��������
			virtual void initialBuffer();
			//! �ͷ���Դ
			virtual void unUse(int slot);

			//! ������������
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
			//! ��ָ��λ��ʹ�ô˻���
			virtual void use();
			//! ��ʼ��������
			virtual void initialBuffer();

			//! lock out �ڲ��Ļ�����
			virtual unsigned char* lock(){
				return ESVertexBuffer::lock();
			}
			//! ��ȡ��������С
			virtual unsigned int getBufferSize(){
				return ESVertexBuffer::getBufferSize();
			}
			//! �ض��建������С
			virtual void reSizeBuffer(unsigned int size){
				ESVertexBuffer::reSizeBuffer(size);
			}
			//! ��ȡ��Ҫ���Ƶ���������
			virtual unsigned int getIndexNums(){
				return m_IndexNum;
			}
			//! ���û��Ƶ���������
			virtual void setIndexNums(unsigned int n){
				m_IndexNum=n;
			}
			//! ��ȡ��Ҫ���Ƶ�ͼԪ����
			virtual EnumPrimaryType getPrimaryType(){
				return m_EPT;
			}
			//! ��ȡ��������
			virtual EnumIndexType getIndexType(){
				return m_EIT;
			}
			//! ����ͼԪ����
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
			//! ��ʼ��ʼ��
			void initialStart();
			//! ������ʼ��
			void initialEnd();
			//! �󶨶��㻺��
			void addVertexBuf(shared_ptr<IDrawBuffer> vbuf);
			//! ����������
			void bindIndexBuf(shared_ptr<IDrawIndexBuffer> ibuf);
			//! ʹ�ô˻�����
			virtual void use();
			//! ʹ�����
			virtual void unUse();
			//! ��ȡ��Ҫ���Ƶ���������
			virtual unsigned int getIndexNums();
			//! ��ȡĬ��ͼԪ����
			virtual EnumPrimaryType getPrimaryType();
			//! ��ȡ��������
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