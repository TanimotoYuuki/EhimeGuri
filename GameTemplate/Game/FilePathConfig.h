#pragma once
#include "stdafx.h"
#include <string>
using namespace std;

class FilePathConfig : public IGameObject
{
public:
    FilePathConfig() {};
    ~FilePathConfig() {};
    static constexpr const char* MODEL_DATA_PATH = "Assets/modelData/Stage/Assets/";
    static constexpr const char* FILE_EXTENSION = ".tkm";

    static string GetFullPath(const string& modelName);

};

