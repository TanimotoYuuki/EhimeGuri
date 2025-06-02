#include "stdafx.h"
#include "Config.h"
#include <string>
using namespace std;

// 3Dモデル用。
string Config::GetFullPath_3DModel(const string& modelName)
{
    return string(MODEL_DATA_PATH) + modelName + FILE_EXTENSION;
}

// エネミー用。
string Config::GetFullPath_Enemy(const string& modelName)
{
    return string(ENEMY_DATA_PATH) + modelName + FILE_EXTENSION;
}

// アイテム用。
string Config::GetFullPath_Item(const string& modelName)
{
    return string(ITEM_DATA_PATH) + modelName + FILE_EXTENSION;
}



