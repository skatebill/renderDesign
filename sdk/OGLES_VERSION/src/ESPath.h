#pragma once
#include<draw/IDrawPath.h>
#include<GLES2/gl2.h>
namespace xc{
	namespace draw{

		void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
		void linkProgram(GLuint ShaderProgram);

		template<typename T>
		class COGLESProgram:public T{
		private:
			GLuint m_Program;

		public:
			//! ��ʼ��shader
			virtual void initialProgram()=0;
			//! ��ʼ��handle
			virtual void initialHandles()=0;

			COGLESProgram():m_Program(0){
				m_Program = glCreateProgram();
				if(m_Program == 0){
					throw std::exception();
				}
				glUseProgram(m_Program);
			}
			~COGLESProgram(){
				glDeleteProgram(m_Program);
			}
			inline GLuint getProgram(){
				return m_Program;
			}
			//! ׼�����ƣ���һЩ׼��������
			virtual void activate(){
				glUseProgram(m_Program);
			}
			//! ��һЩ��β����
			virtual void deActivate(){
			}
		};

		class ESPathContext:public IPathContext{
		public:
			ESPathContext();

			shared_ptr<IColoredPath> mColorPath;
			shared_ptr<ITexturedPath> mTexturePath;

			//! ��ȡ��ɫ����path
			shared_ptr<IColoredPath> getColorPath(){
				return mColorPath;
			}
			//! ��ȡ�������path
			shared_ptr<ITexturedPath> getTexturePath(){
				return mTexturePath;
			}

		};
	}
}