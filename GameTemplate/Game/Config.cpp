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



