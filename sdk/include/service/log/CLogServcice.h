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
			//! 输入普通日志
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
			//! 输入警告日志
			virtual void warning(const char* infos){
				if(check(infos)){
					return;
				}
				if(_warnF){
					_warnF(infos);
					_warnF("\n");
				}

			}
			//! 输入错误日志
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
				//不允许长度超过512一行的日志
				if(strlen(infos)>512){
					if(_errorF){
						_errorF("error log 长度超过了512个字符.请检查字符串.\n");
					}
					return true;
				}
				return false;
			}


		};
	}
}