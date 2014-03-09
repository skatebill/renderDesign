#include"CAssimpPhraser.h"
#include <phraser/IPhraseSerivce.h>
#include <service/file/IFileService.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <draw/IDraw3DBase.h>
#include <Animate/BoneAnimate.h>
#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif
namespace xc{
	namespace phraser{
		using namespace fileservice;
		using namespace draw;
		class assimpPhraser{
		public:
			shared_ptr<BoneAnimeController> loadBone(shared_ptr<IFile> fi){
				using namespace Assimp;
				Importer Imp;
				u32 size = fi->getFileSize();
				void* buf = malloc(size);
				fi->read((char*)buf,size);
				const aiScene* pScene = Imp.ReadFile(fi->getAbsolutePath().c_str(),aiProcess_Triangulate | aiProcess_GenSmoothNormals);
				free(buf);

				const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
			//	auto model = new drawBasement::CModel;
			//	model->modelPath = fi->getAbsolutePath();
				//骨骼动画初始化
				auto boneg = shared_ptr<BoneGroup>(new BoneGroup);
				if(pScene->HasAnimations()){
					buildBoneAnimations(pScene->mAnimations[0],pScene->mRootNode,boneg,nullptr);
					boneg->maxFrames = f32(pScene->mAnimations[0]->mDuration);
					boneg->framesPersecond = f32(pScene->mAnimations[0]->mTicksPerSecond);
				}
				auto bonec = shared_ptr<BoneAnimeController>(new BoneAnimeController);
				bonec->mDstBones = boneg;
				return bonec;
			}


			const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
			{
				for (u32 i = 0 ; i < pAnimation->mNumChannels ; i++) {
					const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

					if (string(pNodeAnim->mNodeName.data) == NodeName) {
						return pNodeAnim;
					}
				}

				return NULL;
			}

			void buildBoneAnimations(aiAnimation* animation, aiNode* node, shared_ptr<BoneGroup> boneg,shared_ptr<Bone> parent = nullptr )
			{
				auto bone =shared_ptr<Bone>(new Bone(parent));
				bone->boneName = node->mName.C_Str();
				memcpy(&bone->nodeTranslatation,&node->mTransformation,sizeof(f32)*16);
				bone->nodeTranslatation = bone->nodeTranslatation.getTransposed();
				boneg->addBone(bone);
				const aiNodeAnim* pNodeAnim = FindNodeAnim(animation, bone->boneName);
				if(pNodeAnim){
					for(u32 i=0;i<pNodeAnim->mNumPositionKeys;++i){
						keyTranslate tt;
						tt.keyPos=f32(pNodeAnim->mPositionKeys[i].mTime);
						auto& r = pNodeAnim->mPositionKeys[i].mValue;
						tt.translateInfo.X = r.x;
						tt.translateInfo.Y = r.y;
						tt.translateInfo.Z = r.z;
						bone->translateList.push_back(tt);
					}
					for(u32 i=0;i<pNodeAnim->mNumRotationKeys;++i){
						keyRotate tr;
						tr.keyPos=f32(pNodeAnim->mRotationKeys[i].mTime);
						auto& r = pNodeAnim->mRotationKeys[i].mValue;
						tr.rotateInfo.X = r.x;
						tr.rotateInfo.Y = r.y;
						tr.rotateInfo.Z = r.z;
						tr.rotateInfo.W = r.w;
						bone->rotateList.push_back(tr);
					}

					for(u32 i=0;i<pNodeAnim->mNumScalingKeys;++i){
						keyScale ts;
						ts.keyPos=f32(pNodeAnim->mScalingKeys[i].mTime);
						auto& r = pNodeAnim->mScalingKeys[i].mValue;
						ts.scaleInfo.X = r.x;
						ts.scaleInfo.Y = r.y;
						ts.scaleInfo.Z = r.z;
						bone->scaleList.push_back(ts);
					}
					/*bone->mMaxFrame = max(pNodeAnim->mNumPositionKeys,pNodeAnim->mNumRotationKeys);
					bone->mMaxFrame = max(bone->mMaxFrame,pNodeAnim->mNumScalingKeys);*/
				}

				for(u32 i=0;i<node->mNumChildren;++i){
					buildBoneAnimations(animation,node->mChildren[i],boneg,bone);
				}
			}


		};
		class CPhraserService:public IPhraserService{
		private:
			shared_ptr<IFileService> mFileService;
			shared_ptr<IContext3D> mDrawFactory;
			assimpPhraser mAssImp;
		public:
			CPhraserService(shared_ptr<IFileService> f,shared_ptr<IContext3D> d):mFileService(f),mDrawFactory(d){

			}
			//! 读取模型
			virtual shared_ptr<BoneAnimeController> loadBoneFromFile(const char* filename){
				auto file = mFileService->createReadableFile(filename);
				//file->open();
				auto r =mAssImp.loadBone(file);
				//file->close();
				return r;
			}
		};
		shared_ptr<IPhraserService> createPhraser(shared_ptr<IFileService> f){
			return shared_ptr<IPhraserService>(new CPhraserService(f,nullptr));
		}
	}
}