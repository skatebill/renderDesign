#include "stdafx.h"
#include "ESBuffers.h"
namespace xc{
	namespace draw{

		ESVertexBuffer::ESVertexBuffer():m_Buff(nullptr),m_Size(0),m_VBO(0),m_ElementSize(0),mDataType(GL_FLOAT){

		}
		ESVertexBuffer::~ESVertexBuffer(){
			if(m_Buff) free(m_Buff);
			m_Buff = nullptr;
			if(m_VBO) glDeleteBuffers(1,&m_VBO);
		}

		//lock out 内部的缓冲区
		unsigned char* ESVertexBuffer::lock(){
			if(m_Buff == nullptr) throw std::exception();
			return m_Buff;
		}

		//重定义缓冲区大小
		void ESVertexBuffer::reSizeBuffer(unsigned int size){
			if(m_Buff) free(m_Buff);
			m_Buff = (unsigned char*)malloc(size);
			m_Size = size;
		}
		void ESVertexBuffer::use(int slot){
			glEnableVertexAttribArray(slot);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			//if(mDataType == GL_UNSIGNED_INT){
			//glVertexAttribPointer(slot, m_ElementSize, mDataType,0, 0);

			//}else{
			glVertexAttribPointer(slot, m_ElementSize, mDataType, GL_FALSE, 0, 0);
			//}
		}
		void ESVertexBuffer::initialBuffer(){
			if(m_Buff == nullptr) throw std::exception();
			if(!m_VBO) glGenBuffers(1,&m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			if(mDataType == GL_UNSIGNED_INT){
				mDataType = GL_FLOAT;
				u32* ptri = (u32*)this->lock();
				f32* ptrf = (f32*)this->lock();
				int n = m_Size/sizeof(u32);
				while(n){
					n--;
					*ptrf=f32(*ptri);
					ptrf++;
					ptri++;
				}
			}
			glBufferData(GL_ARRAY_BUFFER, m_Size, m_Buff, GL_STATIC_DRAW);
		}
		void ESVertexBuffer::unUse(int slot){
			glDisableVertexAttribArray(slot);
		}
		void ESVertexBuffer::setDataType(EnumDataType t)
		{
			switch (t)
			{
			case xc::draw::EDT_FLOAT:
				mDataType = GL_FLOAT;
				break;
			case xc::draw::EDT_UINT:
				mDataType = GL_UNSIGNED_INT;
				break;
			case xc::draw::EDT_INT:
				mDataType = GL_INT;
				break;
			case xc::draw::EDT_USHORT:
				mDataType = GL_UNSIGNED_SHORT;
				break;
			case xc::draw::EDT_SHORT:
				mDataType = GL_SHORT;
				break;
			case xc::draw::EDT_UBYTE:
				mDataType = GL_UNSIGNED_BYTE;
				break;
			case xc::draw::EDT_BYTE:
				mDataType = GL_BYTE;
				break;
			default:
				break;
			}
		}

		void ESVertexBuffer::uploadBuffer()
		{
			initialBuffer();
		}
		//////////////////////////////////////////////////////////////////////////
		ESIndexBuffer::ESIndexBuffer():
			m_IBO(0),m_IndexNum(0),m_EPT(EPT_TRIANGLES),m_EIT(EIT_USHORT)
		{

		}
		ESIndexBuffer::~ESIndexBuffer(){
			if(m_IBO) glDeleteBuffers(1,&m_IBO);
		}
		//! 在指定位置使用此缓冲
		void ESIndexBuffer::use(){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		}
		//! 初始化缓冲区
		void ESIndexBuffer::initialBuffer(){
			if(!m_IBO) glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, ESIndexBuffer::getBufferSize(),ESIndexBuffer::lock(), GL_STATIC_DRAW);
		}

		void ESIndexBuffer::uploadBuffer()
		{
			initialBuffer();
		}

		//////////////////////////////////////////////////////////////////////////
		ESVertexBufferObject::ESVertexBufferObject(){

		}
		ESVertexBufferObject::~ESVertexBufferObject(){
		}
		//! 开始初始化
		void ESVertexBufferObject::initialStart(){
		}
		//! 结束初始化
		void ESVertexBufferObject::initialEnd(){
			if(m_vertexList.size()==0 || m_indexBuffer == 0){
				throw std::exception();
			}
		}
		//! 绑定顶点缓冲
		void ESVertexBufferObject::addVertexBuf(shared_ptr<IDrawBuffer> vbuf){
			unsigned int slot = m_vertexList.size();
			vbuf->use(slot);
			m_vertexList.push_back(vbuf);
		}
		//! 绑定索引缓冲
		void ESVertexBufferObject::bindIndexBuf(shared_ptr<IDrawIndexBuffer> ibuf){
			m_indexBuffer=ibuf;
			m_indexBuffer->use();
		}
		//! 使用此缓冲区
		void ESVertexBufferObject::use(){
			m_indexBuffer->use();
			for(u32 i=0;i<m_vertexList.size();++i){
				m_vertexList[i]->use(i);
			}
		}
		//! 使用完毕
		void ESVertexBufferObject::unUse(){
			m_indexBuffer->unUse();
			for(u32 i=0;i<m_vertexList.size();++i){
				m_vertexList[i]->unUse(i);
			}
		}
		//! 获取需要绘制的索引个数
		unsigned int ESVertexBufferObject::getIndexNums(){
			return m_indexBuffer->getIndexNums();
		}
		//! 获取需要绘制的图元类型
		EnumPrimaryType ESVertexBufferObject::getPrimaryType(){
			return m_indexBuffer->getPrimaryType();
		}
		//! 获取数据类型
		EnumIndexType ESVertexBufferObject::getIndexType(){
			return m_indexBuffer->getIndexType();
		}

		shared_ptr<IDrawBuffer> ESBufferFactory::createVertexBuffer()
		{
			return createPtr<ESVertexBuffer>();
		}

		shared_ptr<IDrawIndexBuffer> ESBufferFactory::createIndexBuffer()
		{
			return createPtr<ESIndexBuffer>();
		}

		shared_ptr<IDrawVertexBufferOBject> ESBufferFactory::createVertexBufferObject( shared_ptr<IDrawBuffer> vbuf, shared_ptr<IDrawIndexBuffer> ibuf, shared_ptr<IDrawBuffer> buf1/*=0*/, shared_ptr<IDrawBuffer> buf2/*=0*/, shared_ptr<IDrawBuffer> buf3/*=0*/, shared_ptr<IDrawBuffer> buf4/*=0 */ )
		{
			auto vbo = new ESVertexBufferObject;
			vbo->initialStart();
			vbo->bindIndexBuf(ibuf);
			vbo->addVertexBuf(vbuf);
			if(buf1){
				vbo->addVertexBuf(buf1);
			}
			if(buf2){
				vbo->addVertexBuf(buf2);
			}
			if(buf3){
				vbo->addVertexBuf(buf3);
			}
			if(buf4){
				vbo->addVertexBuf(buf4);
			}
			vbo->initialEnd();

			return shared_ptr<IDrawVertexBufferOBject>(vbo);
		}

	}
}