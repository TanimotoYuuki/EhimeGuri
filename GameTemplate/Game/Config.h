#pragma once
#include "stdafx.h"
#include <string>
using namespace std;

class Lever;
class Config : public IGameObject
{
public:
    /// <summary>
    /// ファイパスの定数化クラス。
    /// </summary>
    Config() {};
    ~Config() {};

    /// <summary>
    /// static … クラス内で共有される変数。 インスタンスには依存しない。
    /// constexpr … コンパイル時に値が決まる定数。 実行前に定まる値。
    /// const char* … 文字列リテラルのポインタを指す型。 文字列データへのポインタ。
    /// </summary>

    static constexpr const char* MODEL_DATA_PATH = "Assets/modelData/Stage/Assets/"; // ファイルパス。
    static constexpr const char* FILE_EXTENSION = ".tkm"; // 拡張子。

    static string GetFullPath(const std::string& modelName);

private:
    Lever* m_levelRender; // レベルレンダー。
};

