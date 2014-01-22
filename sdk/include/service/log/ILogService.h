#pragma once
#include <tools/MyTypes.h>
/************************************************************************/
/* ����������־�ĵط�
	authored by Ф��
	@2013��12��7��23:10:34*/
/************************************************************************/
namespace xc{
	namespace logservice{
		class ILogService{
		public:
			//! ������ͨ��־
			virtual void log(const char* infos)=0;
			void log(string infos){
				log(infos.c_str());
			}
			void log(stringw infos){
				log((const char*)infos.c_str());
			}
			//! ���뾯����־
			virtual void warning(const char* infos)=0;
			void warning(string infos){
				warning(infos.c_str());
			}
			void warning(stringw infos){
				warning((const char*)infos.c_str());
			}
			//! ���������־
			virtual void error(const char* infos)=0;
			void error(string infos){
				error(infos.c_str());
			}
			void error(stringw infos){
				error((const char*)infos.c_str());
			}
		};
		//! ��ȡ����ʵ��
		inline static ILogService* getService();
	}
}