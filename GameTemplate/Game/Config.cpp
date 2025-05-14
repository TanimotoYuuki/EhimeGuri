#include "stdafx.h"
#include "Config.h"
#include <string>
using namespace std;

// 関数の「実装」
string Config::GetFullPath(const string& modelName)
{
    return string(MODEL_DATA_PATH) + modelName + FILE_EXTENSION;
}

