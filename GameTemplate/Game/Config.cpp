#include "stdafx.h"
#include "Config.h"
#include <string>
using namespace std;


// 3Dモデル用。
string Config::GetFullPath_3DModel(const string& modelName)
{
    return string(MODEL_DATA_PATH) + modelName + FILE_EXTENSION;
}

// アイテム用。
string Config::GetFullPath_Item(const string& modelName)
{
    return string(ITEM_DATA_PATH) + modelName + FILE_EXTENSION;
}

// 愛媛県の場所。
string Config::GetFullPath_EHIMEPLACE(const string& modelName)
{
    return string(EHIME_PLACE) + modelName + SPRITE_EXTENSION;
}

// スプライトレンダー用のファイルパス。
string Config::GetFullPath_Sprite(const string& spriteName, const float w, const float h)
{
    return string(SPRITE_PATH) + spriteName + SPRITE_EXTENSION;
}

// DDS用のファイルパス。
string Config::GetFullPaht_DDS(const string& ddsName, const float w, const float h)
{
    return string(DDS_PATH) + ddsName + DDS_EXTENSION;
}

