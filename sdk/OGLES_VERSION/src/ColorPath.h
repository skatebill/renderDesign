#include"ESPath.h"
namespace xc{
	namespace draw{
		namespace colorP{
			static const char* vs = "                                                    \n\
																\n\
																attribute vec3 Position;                                       \n\
																\n\
																void main()                                                                   \n\
																{                                                                             \n\
																gl_Position = vec4( Position.x, Position.y, Position.z, 1.0);   \n\
																}";

			static const char* ps = "precision mediump float;                                                   \n\
									uniform vec4 Color;										\n\
									void main()                                                                   \n\
									{                                                                             \n\
									gl_FragColor = Color;													     \n\
									}";
		}
		class colorPath:public COGLESProgram<IColoredPath>{
		public:
			GLuint mColorHandle;
			GLuint mPosHandle;
			//! 初始化shader
			virtual void initialProgram(){
				AddShader(getProgram(),colorP::vs,GL_VERTEX_SHADER);
				AddShader(getProgram(),colorP::ps,GL_FRAGMENT_SHADER);
				linkProgram(getProgram());
				initialHandles();

			}
			//! 初始化handle
			virtual void initialHandles(){
				mColorHandle = glGetUniformLocation(getProgram(),"Color");
				mPosHandle = glGetAttribLocation(getProgram(),"Position");

			}
			//! 设置颜色
			virtual void setColor(colorf color){
				glUniform4f(mColorHandle,color.r,color.g,color.b,color.a);
			}
		};
	}
}