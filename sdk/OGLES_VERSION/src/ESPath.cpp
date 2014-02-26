#include"ESPath.h"
#include"ColorPath.h"
namespace xc{
	namespace draw{
		void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
		{
			GLuint ShaderObj = glCreateShader(ShaderType);

			if (ShaderObj == 0) {
				throw std::exception();
			}

			const GLchar* p[1];
			p[0] = pShaderText;
			GLint Lengths[1];
			Lengths[0]= strlen(pShaderText);
			glShaderSource(ShaderObj, 1, p, Lengths);
			glCompileShader(ShaderObj);
			GLint success;
			glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
			if (!success) {
				GLchar InfoLog[1024];
				glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
				throw std::exception();
			}

			glAttachShader(ShaderProgram, ShaderObj);
		}
		void linkProgram(GLuint ShaderProgram){
			GLint Success = 0;
			glLinkProgram(ShaderProgram);
			glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
			if (Success == 0) {
				GLchar ErrorLog[1024] = { 0 };
				glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
				throw std::exception();
			}

			glValidateProgram(ShaderProgram);
			glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
			if (!Success) {
				GLchar ErrorLog[1024] = { 0 };
				glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
				throw std::exception();
			}

			glUseProgram(ShaderProgram);
		}

		ESPathContext::ESPathContext(){
			auto p = new colorPath;
			p->initialProgram();
			mColorPath = shared_ptr<IColoredPath>(p);
		}
	}
}