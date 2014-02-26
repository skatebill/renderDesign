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
			//! 初始化shader
			virtual void initialProgram()=0;
			//! 初始化handle
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
			//! 准备绘制（做一些准备工作）
			virtual void activate(){
				glUseProgram(m_Program);
			}
			//! 做一些收尾工作
			virtual void deActivate(){
			}
		};

		class ESPathContext:public IPathContext{
		public:
			ESPathContext();

			shared_ptr<IColoredPath> mColorPath;
			shared_ptr<ITexturedPath> mTexturePath;

			//! 获取颜色绘制path
			shared_ptr<IColoredPath> getColorPath(){
				return mColorPath;
			}
			//! 获取纹理绘制path
			shared_ptr<ITexturedPath> getTexturePath(){
				return mTexturePath;
			}

		};
	}
}