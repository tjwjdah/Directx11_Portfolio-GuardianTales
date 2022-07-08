#pragma once
#include <Engine\CScript.h>

#include <Engine/CMaterial.h>
class CStructuredBuffer;
class CTexture;

class CMapScript :
    public CScript
{
private:
    vector<tTile>           m_tile2D;
    tTileShared             m_TileShared;
    CStructuredBuffer*      m_TileBuffer;
    CStructuredBuffer*      m_TSharedBuffer;

   
    int                   m_tile_x;
    int                   m_tile_y;
    float                 m_tileUv_x;
    float                 m_tileUv_y;

    int                  m_tileSize;



public:
    void SetTileNum(int _x, int _y);
    void SetTile(int _x, int _y, Vec2 index);
    //void SetTileTexture(CTexture* _Tex) { m_TileTexture = _Tex; }
    int GetTileX() { return m_tile_x; }
    int GetTileY() { return m_tile_y; }
    int GetTileSIze() { return m_tileSize; }
    float GetTileUvX() { return m_tileUv_x; }
    float GetTileUvY() { return m_tileUv_y; }

public:
    virtual void awake();
    virtual void update();
    virtual void render();

public:
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);

public:
    CLONE(CMapScript);
    CMapScript();
    ~CMapScript();
};

