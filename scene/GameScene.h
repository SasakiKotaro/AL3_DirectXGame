﻿#pragma once

#include "Audio.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//スプライト
	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;

	//モデル
	Model* model_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform worldTransform_[100];
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//カメラ上方向の角度
	float viewAngle = 0.0f;

	// soundデータバンドル
	uint32_t soundDataHandle_ = 0;

	//音声再生バンドル
	uint32_t voicehandle_ = 0;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
//
//class Xmfloat3Calc {
//  public:
//	Xmfloat3Calc();
//	~Xmfloat3Calc();
//	void add(XMFLOAT3 xmf3,);
//
//  private:
//};
//
//Xmfloat3Calc::Xmfloat3Calc() {}
//
//Xmfloat3Calc::~Xmfloat3Calc() {}