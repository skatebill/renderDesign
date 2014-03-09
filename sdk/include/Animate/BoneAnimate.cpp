#include "BoneAnimate.h"
namespace xc{
	namespace draw{
		using namespace std;

		mat4 Bone::getPreTranslateMatrix(f32 frame){
			if(curFrame == frame){
				return currentMatrix;
			}
			curFrame = frame;
			mat4 rotateMat,scaleMat,translateMat;
			if(scaleList.size() == 0 || translateList.size()==0||rotateList.size()==0){
				currentMatrix = nodeTranslatation;
			}else{
				//scale ²îÖµ
				if(scaleList.size() == 1){
					vector3df scale = scaleList[0].scaleInfo;
					scaleMat.setScale(scale);
				}else if(scaleList.size()>1){
					auto spos = std::find_if(scaleList.begin(),scaleList.end(),[frame](keyScale& s)->bool{
						return frame<s.keyPos;
					});
					if(spos == scaleList.end()){
						vector3df scale = scaleList[scaleList.size()-1].scaleInfo;
						scaleMat.setScale(scale);
					}else{

						auto pre = spos;
						pre--;
						auto t = (frame - pre->keyPos)/(spos->keyPos-pre->keyPos);
						vector3df t1=pre->scaleInfo,t2=spos->scaleInfo;
						auto t3 = (t2-t1)*t+t1;
						scaleMat.setScale(t3);
					}
				}
				// translate ²îÖµ
				if(translateList.size() == 1){
					vector3df trans = translateList[0].translateInfo;
					translateMat.setTranslation(trans);
				}else if(translateList.size()>1){
					auto spos = std::find_if(translateList.begin(),translateList.end(),[frame](keyTranslate& s)->bool{
						return frame<s.keyPos;
					});
					if(spos == translateList.end()){
						vector3df trans = translateList[translateList.size()-1].translateInfo;
						translateMat.setTranslation(trans);
					}else{
						auto pre = spos;
						pre--;
						auto t = (frame - pre->keyPos)/(spos->keyPos-pre->keyPos);
						vector3df t1=pre->translateInfo,t2=spos->translateInfo;
						auto t3 = (t2-t1)*t+t1;
						translateMat.setTranslation(t3);
					}
				}
				// rotate ²îÖµ
				if(rotateList.size() == 1){
					quaternion r = rotateList[0].rotateInfo;
					r.getMatrix(rotateMat,zero3df);
				}else if(rotateList.size()>1){
					auto spos = std::find_if(rotateList.begin(),rotateList.end(),[frame](keyRotate& s)->bool{
						return frame<s.keyPos;
					});
					if(spos == rotateList.end()){
						quaternion r = rotateList[rotateList.size()-1].rotateInfo;
						r.getMatrix(rotateMat,zero3df);
					}else{
						auto pre = spos;
						pre--;
						auto t = (frame - pre->keyPos)/(spos->keyPos-pre->keyPos);
						auto t1=pre->rotateInfo,t2=spos->rotateInfo;
						auto t3 = t1.lerp(t1,t2,t);
						t3.getMatrix(rotateMat,zero3df);
					}
				}
				currentMatrix = translateMat*rotateMat*scaleMat;
				if(mParent){
					currentMatrix = mParent->getPreTranslateMatrix(frame)*currentMatrix;
				}
			}
			return currentMatrix;
		}
		Bone::Bone(shared_ptr<Bone> parent):mParent(parent){
			curFrame = -1;
		}
		mat4 Bone::getTranslateMatrix(f32 frame){
			return getPreTranslateMatrix(frame) * boneOffset;
		}

		void BoneGroup::addBone(shared_ptr<Bone> bone){
			if( find(mBoneList.begin(),mBoneList.end(),bone) == mBoneList.end()){
				mBoneList.push_back(bone);
			}
		}
		u32 BoneGroup::getBoneIdx(shared_ptr<Bone> dstBone){
			return getBoneIdx(dstBone->boneName);
		}
		u32 BoneGroup::getBoneIdx(string boneName){
			auto ite = find_if(mBoneList.begin(),mBoneList.end(),[&boneName](shared_ptr<Bone>& b){
				return boneName == b->boneName;
			});
			if(ite == mBoneList.end()){
				return -1;
			}
			return ite-mBoneList.begin();
		}
		shared_ptr<Bone> BoneGroup::getBone(u32 idx){
			if(idx <0 || idx > mBoneList.size()-1){
				return nullptr;
			}
			return mBoneList[idx];
		}
		shared_ptr<Bone> BoneGroup::getBone(string boneName){
			return getBone(getBoneIdx(boneName));
		}

		void BoneAnimePlayer::update(f32 t,BoneAnimeCallback* callback){
			currentTime += t;
			auto delta = currentTime/lastTime;
			if(delta>=1.0f){
				if(!loopFlag){
					pauseAction();
				}else{
					currentTime = 0.0;
				}
				delta = 1.0f;
			}
			for(auto ite = actionPartList.begin();ite != actionPartList.end();++ite){
				if(ite->actionLevel > callback->boneLevel[ite->boneIdx]){
					callback->boneLevel[ite->boneIdx] = ite->actionLevel;
				}
				if(ite->actionLevel == callback->boneLevel[ite->boneIdx]){
					auto cf = ite->startFrame + (ite->endFrame-ite->startFrame)*ite->interper->interp(delta);
					callback->boneFrames[ite->boneIdx] = cf;
				}
			}

		}

		BoneAnimeController::BoneAnimeController(){
			updateFlag = false;
			mUnifomUpdateFunc = [this](){
				mUniformBuffers.resize(mDstBones->mBoneList.size());
				mUnifomUpdateFunc = [this](){
					auto num = mUniformBuffers.size();
					for(u32 i=0;i<num;++i){
						mUniformBuffers[i]=mDstBones->mBoneList[i]->getTranslateMatrix(this->BoneAnimeCallback::boneFrames[i]);
					}
				};
			};
		}
		void BoneAnimeController::update(f32 t){
			for(auto ite = mActionList.begin();ite != mActionList.end();++ite){
				if(ite->second->playing){
					ite->second->update(t,this);
				}
			}
			updateFlag=true;
		}
		void BoneAnimeController::playAction(string actionName){
			auto ite = mActionList.find(actionName);
			if(ite != mActionList.end()){
				ite->second->playAction();
			}
		}
		void BoneAnimeController::getBoneUnifomBuff(void*& bufPtr,u32& size){
			if(updateFlag){
				updateFlag=false;
				mUnifomUpdateFunc();
				bufPtr = &mUniformBuffers[0];
				size = mUniformBuffers.size();
			}else{
				bufPtr = nullptr;
				size = 0;
			}
		}

	}
}