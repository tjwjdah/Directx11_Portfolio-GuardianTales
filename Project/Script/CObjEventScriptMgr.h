#pragma once
#include <Engine\CSingleton.h>

class CObjEventScript;
class CScene;
class CObjEventScriptMgr :
    public CSingleton<CObjEventScriptMgr>
{
    SINGLE(CObjEventScriptMgr);
private:
    vector<CObjEventScript*> SaveEvent;


public:
    void EvnetPush(CObjEventScript* _Event) { SaveEvent.push_back(_Event); }
    void DeleteEvent(CObjEventScript* _Event);
    vector<CObjEventScript*>& GetEvent() { return SaveEvent; }
    
public:
    void SaveToScene(FILE* _pFile);
    void LoadFromScene(CScene* _Scene, FILE* _pFile);
};

