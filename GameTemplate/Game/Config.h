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

    /// <summary>
    /// ファイルパス。
    /// </summary>
    static constexpr const char* MODEL_DATA_PATH = "Assets/modelData/Stage/Assets/"; // 3Dモデル。
    static constexpr const char* ENEMY_DATA_PATH = "Assets/modelData/YoshinagaAssets/";// 敵キャラ。
    static constexpr const char* ENEMY_ANIMATION_PATH = "Assets/modelData/YoshinagaAssets/SkeletonAnim/";// 敵キャラ用のアニメーション。
    static constexpr const char* PLAYER_ANIMATION_PATH = "Assets/animData/";// Playerのアニメーション。
    static constexpr const char* ITEM_DATA_PATH = "Assets/modelData/tokusannhinn/";// アイテム。
    
    /// <summary>
    /// 拡張子。
    /// </summary>
    static constexpr const char* FILE_EXTENSION = ".tkm"; // 3Dモデル用の拡張子。
    static constexpr const char* ENEMY_ANIMATION_FILE_EXTENSION = ".tka"; // アニメーション用の拡張子。

    /// <summary>
    /// それぞれの関数。
    /// </summary>
    static string GetFullPath_3DModel(const std::string& modelName);// 3Dモデル用のファイルパス。
    static string GetFullPath_Enemy(const std::string& modelName);// 敵キャラ用のファイルパス。
    static string GetFullPath_Item(const std::string& modelName);// アイテムのファイルパス。
private:
};

