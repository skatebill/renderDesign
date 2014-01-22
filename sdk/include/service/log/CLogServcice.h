#pragma once
#include"ILogService.h"
#include<functional>
namespace xc{
	namespace logservice{
		class CLogService:public ILogService{
		public:
			std::function<void(const char*)> _logF;
			std::function<void(const char*)> _warnF;
			std::function<void(const char*)> _errorF;
			std::function<void()> onClose;
			~CLogService(){
				if(onClose) onClose();
			}
			//! ������ͨ��־
			virtual void log(const char* infos){
				if(check(infos)){
					return;
				}
				if(_logF)
				{
					_logF(infos);
					_logF("\n");
				}
			}
			//! ���뾯����־
			virtual void warning(const char* infos){
				if(check(infos)){
					return;
				}
				if(_warnF){
					_warnF(infos);
					_warnF("\n");
				}

			}
			//! ���������־
			virtual void error(const char* infos){
				if(check(infos)){
					return;
				}
				if(_errorF){
					_errorF(infos);
					_errorF("\n");
				}

			}

			bool check( const char* infos ) 
			{
				//�������ȳ���512һ�е���־
				if(strlen(infos)>512){
					if(_errorF){
						_errorF("error log ���ȳ�����512���ַ�.�����ַ���.\n");
					}
					return true;
				}
				return false;
			}


		};
	}
}