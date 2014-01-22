#pragma once
#include <tools/MyTypes.h>
/************************************************************************/
/* 用来输入日志的地方
	authored by 肖驰
	@2013年12月7日23:10:34*/
/************************************************************************/
namespace xc{
	namespace logservice{
		class ILogService{
		public:
			//! 输入普通日志
			virtual void log(const char* infos)=0;
			void log(string infos){
				log(infos.c_str());
			}
			void log(stringw infos){
				log((const char*)infos.c_str());
			}
			//! 输入警告日志
			virtual void warning(const char* infos)=0;
			void warning(string infos){
				warning(infos.c_str());
			}
			void warning(stringw infos){
				warning((const char*)infos.c_str());
			}
			//! 输入错误日志
			virtual void error(const char* infos)=0;
			void error(string infos){
				error(infos.c_str());
			}
			void error(stringw infos){
				error((const char*)infos.c_str());
			}
		};
		//! 获取服务实例
		inline static ILogService* getService();
	}
}