#pragma once
#include "stdafx.h"
#include <string>

class FilePathConfig : public IGameObject
{
public:
    FilePathConfig() {};
    ~FilePathConfig() {};
    static constexpr const char* MODEL_DATA_PATH = "Assets/modelData/Stage/Assets/";
    static constexpr const char* FILE_EXTENSION = ".tkm";

    static string GetFullPath(const std::string& modelName);

};

