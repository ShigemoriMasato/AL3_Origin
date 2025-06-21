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
	while (enemies_.size() > 0) {
		DestroyEnemy(0); // 既存の敵を削除
	}
}

void GameScene::Initialize() {
	skydome_ = commonData_->modelHandle_[int(ModelType::skydome)];
	player_->Initialize(camera_, commonData_->modelHandle_[int(ModelType::player)], commonData_->textureHandle_[int(TextureType::AttackEffect)]);

	while(enemies_.size() > 0) {
		DestroyEnemy(0); // 既存の敵を削除
	}

	Enemy* enemy = new Enemy();
	enemy->Initialize(camera_, commonData_->modelHandle_[int(ModelType::skull)], 0);
	enemies_.push_back(enemy);

	enemy = new Enemy();
	enemy->Initialize(camera_, commonData_->modelHandle_[int(ModelType::skull)], 0);
	enemy->SetPosition({ 15.0f, 4.5f, 0.0f });
	enemies_.push_back(enemy);

	enemy = new Enemy();
	enemy->Initialize(camera_, commonData_->modelHandle_[int(ModelType::skull)], 0);
	enemy->SetPosition({ 20.0f, 1.5f, 0.0f });
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

	if(Input::GetKeyState(DIK_R) && !Input::GetPreKeyState(DIK_R)) {
		Initialize(); // Rキーで再初期化
	}

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


	if (Input::GetKeyState(DIK_RETURN) && !Input::GetPreKeyState(DIK_RETURN)) {
		isDebugCamera = !isDebugCamera; // Toggle camera mode
	}

	player_->Update();

	logger_->Log("Player Update Complete");

	for (int i = 0; i < enemies_.size(); ++i) {
		enemies_[i]->Update();
		if (enemies_[i]->GetIsDeath()) {
			DestroyEnemy(i--);
		}
	}

	//GetIsDeath()がtrueの敵を削除(エラーが出るため使用不可)
	//std::erase_if(enemies_, [](const Enemy& enemy) { return enemy.GetIsDeath(); } );

	logger_->Log("Enemy Update Complete");

	CheeckAllCollisions();

	logger_->Log("Collision Check Complete");

	return nullptr;
}

void GameScene::Draw() const {
	Render::DrawModel(skydome_, MakeIdentity4x4(), camera_, { 1.0f, 1.0f, 1.0f, 1.0f, true }, {});

	player_->Draw();

	logger_->Log("Player Draw Complete");

	for (const auto* enemy : enemies_) {
		enemy->Draw();
	}

	logger_->Log("Enemy Draw Complete");

	mapChip_->Draw();

	logger_->Log("MapChip Draw Complete");

	logger_->Log("Draw Complete\n");

	fadeInOut_->Draw();
}

void GameScene::DestroyEnemy(int index) {
	if(index < 0 || index >= enemies_.size()) {
		return; // インデックスが範囲外の場合は何もしない
	}

	delete enemies_[index];
	enemies_.erase(enemies_.begin() + index);
}

void GameScene::CheeckAllCollisions() {
#pragma region Player to Enemy Collision Check

	AABB player, enemy;

	player = player_->GetAABB();

	//生きてたら
	if (player_->GetState() == PlayerState::Alive) {
		for (Enemy* e : enemies_) {
			
			if (e->GetIsInvisible()) {
				continue; //当たり判定をとらない敵は処理を飛ばす
			}

			enemy = e->GetAABB();
			if (Collision::AABBtoAABB(player, enemy)) {

				if (player_->GetIsAttack()) {
					e->OnCollition(player_);
				} else {
					player_->OnCollition(*e);
				}

				break;
			}
		}
	}

#pragma endregion
}
