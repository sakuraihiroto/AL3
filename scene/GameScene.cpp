﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

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
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	// 3Dモデルの生成
	model_ = Model::Create();
	//X,Y,Z方向のスケーリング設定
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	//X,Y,Z軸周りの回転角を設定
	worldTransform_.rotation_ = {XM_PI/4.0f, XM_PI/4.0f, 0.0f};
	//X,Y,Z軸周りの平行移動を設定
	worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	////サウンドデータの読み込み
	//soundDataHandle_ = audio_->LoadWave("se_sad03.wav");
	////音楽再生
	//audio_->PlayWave(soundDataHandle_);
	////音声再生
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
}

void GameScene::Update() {
	////スプライトの今の座標を取得
	//XMFLOAT2 position = sprite_->GetPosition();
	////座標を{2,0}移動
	//position.x += 2.0f;
	//position.y += 1.0f;
	////移動した座標をスプライトに反映
	//sprite_->SetPosition(position);
	////スペースキーを押した瞬間
	//if (input_->TriggerKey(DIK_SPACE)) {
	//	//音楽停止
	//	audio_->StopWave(voiceHandle_);
	//}
	//デバイステキストの表示
	//debugText_->Print("kaizokuou ni oreha naru.", 50, 50, 1.0f);
	////書式指定付き表示
	//debugText_->SetPos(50, 70);
	//debugText_->Printf("year:%d", 2001);
	////変数の値をインクリメント
	//value_++;
	//値を含めた文字列
	//translation
	std::string strDebug = std::string("translation:(") +
	                       std::to_string(worldTransform_.translation_.x) + std::string(",") +
	                       std::to_string(worldTransform_.translation_.y) + std::string(",") +
	                       std::to_string(worldTransform_.translation_.z) + std::string(",)");
	//デバッグテキストの表示
	debugText_->Print( strDebug, 50, 50, 1.0f);

	//rotation
	std::string strDebug2 = std::string("roration:(") +
	                       std::to_string(worldTransform_.rotation_.x) + std::string(",") +
	                       std::to_string(worldTransform_.rotation_.y) + std::string(",") +
	                       std::to_string(worldTransform_.rotation_.z) + std::string(",)");
	debugText_->Print(strDebug2, 50, 70, 1.0f);

	//scale
	std::string strDebug3 = std::string("scale:(") +
	                        std::to_string(worldTransform_.scale_.x) + std::string(",") +
	                        std::to_string(worldTransform_.scale_.y) + std::string(",") +
	                        std::to_string(worldTransform_.scale_.z) + std::string(",)");
	debugText_->Print(strDebug3, 50, 90, 1.0f);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	//// 背景スプライト描画前処理
	//Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
//	sprite_->Draw();
//	// スプライト描画後処理
//	Sprite::PostDraw();
//	// 深度バッファクリア
//	dxCommon_->ClearDepthBuffer();
//#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 3Dモデル描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
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