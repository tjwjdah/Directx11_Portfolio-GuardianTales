#include "pch.h"
#include "CObjEventScriptMgr.h"

#include <Script\CObjEventScript.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CGameObject.h>
CObjEventScriptMgr::CObjEventScriptMgr()
{


}
CObjEventScriptMgr::~CObjEventScriptMgr() {

}

void CObjEventScriptMgr::DeleteEvent(CObjEventScript* _Event)
{

	vector<CObjEventScript*>::const_iterator iter = SaveEvent.begin();
	for (; iter != SaveEvent.end(); iter++)
	{
		if (_Event == (*iter))
		{
			SaveEvent.erase(iter);
			break;
		}
	}

}

void CObjEventScriptMgr::SaveToScene(FILE* _pFile)
{
	UINT iCount = SaveEvent.size();
	fwrite(&iCount, sizeof(UINT), 1, _pFile);
	for (size_t i = 0; i < SaveEvent.size(); i++)
	{
		SaveWString(SaveEvent[i]->GetGameObject()->GetName(), _pFile);
		iCount = SaveEvent[i]->GetChildeTrigger().size();
		fwrite(&iCount, sizeof(UINT), 1, _pFile);
		for (size_t l = 0; l < SaveEvent[i]->GetChildeTrigger().size(); l++)
		{
			SaveWString(SaveEvent[i]->GetChildeTrigger()[l]->GetGameObject()->GetName(), _pFile);
		}
	}
}

void CObjEventScriptMgr::LoadFromScene(CScene* _Scene, FILE* _pFile)
{
	if(SaveEvent.size()>0)
		SaveEvent.clear();
	UINT iCount = 0;
	fread(&iCount, sizeof(UINT), 1, _pFile);
	for (UINT i = 0; i < iCount; i++)
	{
		wstring _str;
		LoadWString(_str, _pFile);
		const wstring& st = _str;
		CGameObject* Obj = _Scene->FindParentObjectByName(st);
		CObjEventScript* Event = (CObjEventScript*)Obj->GetScript(L"CObjEventScript");
		SaveEvent.push_back(Event);
		UINT iCount2 = 0;
		fread(&iCount2, sizeof(UINT), 1, _pFile);
		for (size_t l = 0; l < iCount2; l++)
		{

			LoadWString(_str, _pFile);
			const wstring& st2 = _str;
			Obj = _Scene->FindParentObjectByName(st2);
			CObjEventScript* child = (CObjEventScript*)Obj->GetScript(L"CObjEventScript");
			Event->PushEvnetChild(child);
		}
	}
}
