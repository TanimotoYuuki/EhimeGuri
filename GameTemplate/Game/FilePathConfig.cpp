#include "stdafx.h"
#include "FilePathConfig.h"
#include <string>
using namespace std;

// 関数の「実装」
string FilePathConfig::GetFullPath(const string& modelName)
{
    return string(MODEL_DATA_PATH) + modelName + FILE_EXTENSION;
}

