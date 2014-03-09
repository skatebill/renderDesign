#pragma once
#include <tools/MyTypes.h>
#include <phraser/IPhraseSerivce.h>
#include <service/file/IFileService.h>
namespace xc{
	namespace phraser{
		shared_ptr<IPhraserService> createPhraser(shared_ptr<xc::fileservice::IFileService> f);
	}
}