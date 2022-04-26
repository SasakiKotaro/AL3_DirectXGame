#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

using namespace std;
using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();

	////乱数シード生成期
	// random_device seed_gen;
	////メルセンヌ・ツイスタ
	// mt19937_64 engine(seed_gen());
	////乱数範囲（回転角用）
	// uniform_real_distribution<float> rotDist(0.0f, XM_2PI);
	////乱数範囲（座標用）
	// uniform_real_distribution<float> posDist(-10.0f, 10.0f);

	for (int i = 0; i < _countof(worldTransform_); i++) {

		// X,Y,Z方向のスケーリングを設定
		worldTransform_[i].scale_ = {10.0f, 10.0f, 1.0f};
		//// X,Y,Z軸周りの回転角を設定
		// worldTransform_[i].rotation_ = {0, 0, 0};
		//  X,Y,Z軸周りの平行移動を設定

		if (i % 2 == 0) // odd
		{
			worldTransform_[i].translation_ = {
			  i / 2 * worldTransform_[i].scale_.x * 2 - 100,
			  -30,
			  0,
			};
		} else {
			worldTransform_[i].translation_ = {
			  i / 2 * worldTransform_[i].scale_.x * 2 - 100, worldTransform_[i].scale_.x * 6 - 30,
			  0};
		}

		worldTransform_[i].Initialize();
	}
	// viewProjection_.eye = {0, 0, -50};
	//////カメラ注視点座標の設定
	// viewProjection_.target = {10, 0, 0};
	//////カメラ上方向ベクトルの設定（右上45度設定）
	// viewProjection_.up = {cosf(XM_PI / 4.0f), sinf(XM_PI / 4.0f), 0.0f};
	////カメラ垂直方向視野角を設定
	viewProjection_.fovAngleY = XMConvertToRadians(75.0f);
	//アスペクト比を設定
	//  viewProjection_.aspectRatio = 1.0f;
	//ニアクリップ距離を設定
	viewProjection_.nearZ = 32.0f;
	//ファークリップ距離を設定
	viewProjection_.farZ = 53.0f;
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameScene::Update() {
	//今の座標取得
	XMFLOAT2 position = sprite_->GetPosition();
	//視点移動処理=====================
	// XMFLOAT3 move = {0, 0, 0};
	////視点移動の速さ
	// const float kEyeSpeed = 0.2f;
	////押した方向で移動ベクトルを変更
	// if (input_->PushKey(DIK_W)) {
	//	move = {0, 0, kEyeSpeed};
	// } else if (input_->PushKey(DIK_S)) {
	//	move = {0, 0, -kEyeSpeed};
	// }
	////視点移動
	// viewProjection_.eye.x += move.x;
	// viewProjection_.eye.y += move.y;
	// viewProjection_.eye.z += move.z;
	////行列の再計算
	// viewProjection_.UpdateMatrix();
	//デバッグ用
	debugText_->SetPos(50, 50);
	debugText_->Printf(
	  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	//注視移動処理=====================
	////注視点の移動ベクトル
	// XMFLOAT3 move = {0, 0, 0};
	//注視点の速さ
	// const float kTargetSpeed = 0.2f;
	////押した方向で移動ベクトルを変更
	// if (input_->PushKey(DIK_LEFT)) {
	//	move = {-kTargetSpeed, 0, 0};
	// } else if (input_->PushKey(DIK_RIGHT)) {
	//	move = {kTargetSpeed, 0, 0};
	// }
	////注視点移動（ベクトルの加算）
	// viewProjection_.target.x += move.x;
	// viewProjection_.target.y += move.y;
	// viewProjection_.target.z += move.z;
	////行列の再計算
	// viewProjection_.UpdateMatrix();
	////デバッグ用
	debugText_->SetPos(50, 70);
	debugText_->Printf(
	  "tgt:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
	  viewProjection_.target.z);
	//上方向の回転処理
	//上方向の回転の速さ[ラジアン/flame]
	// const float kUpRotSpeed = 0.05f;
	////押した方向で移動ベクトルを変更
	// if (input_->PushKey(DIK_SPACE)) {
	//	viewAngle += kUpRotSpeed;
	//	// 2πを超えたら0に戻す
	//	viewAngle = fmodf(viewAngle, XM_2PI);
	// }
	////上方向のベクトルを計算（半径１の円周上の座標）
	// viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};
	////行列の再計算
	// viewProjection_.UpdateMatrix();
	//デバッグ用
	debugText_->SetPos(50, 90);
	debugText_->Printf(
	  "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
	// FoV変更処理
	//上キーで視野角が広がる
	if (input_->PushKey(DIK_W)) {
		viewProjection_.fovAngleY += 0.01f;
		viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, XM_PI);
	} else if (input_->PushKey(DIK_S)) {
		viewProjection_.fovAngleY -= 0.01f;
		viewProjection_.fovAngleY = max(viewProjection_.fovAngleY, 0.01f);
	}
	viewProjection_.UpdateMatrix();
	//クリップ距離変更処理
	//上下キーでニアクリップ距離を増減
	if (input_->PushKey(DIK_UP)) {
		viewProjection_.nearZ += 0.05f;
	} else if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.nearZ -= 0.05f;
	}
	viewProjection_.UpdateMatrix();

	debugText_->SetPos(50, 130);
	debugText_->Printf("nearZ:%f", viewProjection_.nearZ);

	//デバッグ用表示
	debugText_->SetPos(50, 110);
	debugText_->Printf("fovAngleY(Degree) :%f", XMConvertToDegrees(viewProjection_.fovAngleY));

	//移動した座標をスプライトに反映
	sprite_->SetPosition(position);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	for (int i = 0; i < _countof(worldTransform_); i++) {
		model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
