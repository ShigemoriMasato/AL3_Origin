#include "GameScene.h"
#include "../Engine/Input/Input.h"
#include "../externals/imgui/imgui.h"
#include "../Engine/Math/MyMath.h"

using namespace Matrix;

GameScene::GameScene(CommonData* commonData) : Scene(commonData) {
	camera_ = new Camera();
	debugCamera = new DebugCamera();
	player_ = new Player();
	logger_ = new Logger("scene");
	cameraController_ = new CameraController();
	mapChip_ = new MapChip();
	fadeInOut_ = new FadeInOut();
}

GameScene::~GameScene() {
	delete camera_;
	delete player_;
	delete mapChip_;
	delete debugCamera;
	delete logger_;
	delete cameraController_;
	delete fadeInOut_;
}

void GameScene::Initialize() {
	skydome_ = commonData_->modelHandle_[int(ModelType::skydome)];
	player_->Initialize(camera_, commonData_->modelHandle_[int(ModelType::player)]);

	enemies_.clear();
	Enemy enemy;
	enemy.Initialize(camera_, commonData_->modelHandle_[int(ModelType::skull)], 0);
	enemies_.push_back(enemy);

	enemy.SetPosition({ 15.0f, 4.5f, 0.0f });
	enemy.SetNumber(1);
	enemies_.push_back(enemy);

	enemy.SetPosition({ 20.0f, 1.5f, 0.0f });
	enemy.SetNumber(2);
	enemies_.push_back(enemy);

	cameraController_->Initialize({ 12.0f, 88.0f, 88.0f, 7.2f });
	cameraController_->SetTarget(player_);

	mapChip_->Initialize("resources/blocks.csv", commonData_->textureHandle_[int(TextureType::block)], camera_);

	player_->SetMapChip(mapChip_);

	debugCamera->Initialize();

	fadeInOut_->Initialize(60, camera_);
	fadeInOut_->SwitchFadeInOut(true); // フェードインを開始
}

Scene* GameScene::Update() {

	cameraController_->Update();

	if (isDebugCamera) {
		debugCamera->Update();
		*camera_ = debugCamera->GetCamera();
	} else {
		*camera_ = *cameraController_->GetCamera();

		camera_->SetProjectionMatrix(PerspectiveFovDesc());
	}

	camera_->MakeMatrix();

	logger_->Log("Camera Complete");

	fadeInOut_->Update();


	if (Input::GetKeyState(DIK_SPACE) && !Input::GetPreKeyState(DIK_SPACE)) {
		isDebugCamera = !isDebugCamera; // Toggle camera mode
	}

	player_->Update();

	logger_->Log("Player Update Complete");

	for(auto& enemy : enemies_) {
		enemy.Update();
	}

	logger_->Log("Enemy Update Complete");

	CheeckAllCollisions();

	logger_->Log("Collision Check Complete");

	return nullptr;
}

void GameScene::Draw() const {
	Render::DrawModel(skydome_, MakeIdentity4x4(), camera_, { 1.0f, 1.0f, 1.0f, 1.0f, true }, {});

	player_->Draw();

	logger_->Log("Player Draw Complete");

	for (const auto& enemy : enemies_) {
		enemy.Draw();
	}

	logger_->Log("Enemy Draw Complete");

	mapChip_->Draw();

	logger_->Log("MapChip Draw Complete");

	logger_->Log("Draw Complete\n");

	fadeInOut_->Draw();
}

void GameScene::CheeckAllCollisions() {
#pragma region Player to Enemy Collision Check

	AABB player, enemy;

	player = player_->GetAABB();

	//生きてたら
	if (player_->GetState() == PlayerState::Alive) {
		for (const auto& e : enemies_) {
			enemy = e.GetAABB();
			if (Collision::AABBtoAABB(player, enemy)) {
				player_->OnCollition(e);
				break;
			}
		}
	}

#pragma endregion
}
