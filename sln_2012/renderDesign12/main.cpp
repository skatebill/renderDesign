#include <phraser/CAssimpPhraser.h>
#include <service/file/IFileService.h>
#include"../sdk/FileService/FileService.h"
int main(){
	auto f = createFileService();
	auto pf = xc::phraser::createPhraser(f);
	auto b = pf->loadBoneFromFile("dwarf.x");

	return 0;
}