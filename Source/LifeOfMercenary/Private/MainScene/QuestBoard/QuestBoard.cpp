// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/MainScene/QuestBoard/QuestBoard.h"
#include "LifeOfMercenary/Public/Character/MercenaryCharacter.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "LifeOfMercenary/Public/Quest/QuestManager.h"
#include "LifeOfMercenary/Public/Camera/MainSceneCamera.h"
#include "LifeOfMercenary/Public/UI/DefaultUI.h"
#include "LifeOfMercenary/Public/MainScene/GameMode/HUDManager.h"
#include "LifeOfMercenary/Public/Quest/QuestManager.h"

// Sets default values
AQuestBoard::AQuestBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	paperPos.Add(FTransform(FRotator(0, 0, 0), FVector(1.0f, 50.0f, 28.0f), FVector(0.3f, 0.3f, 0.3f)));
	paperPos.Add(FTransform(FRotator(0, 0, 0), FVector(1.0f, 0.0f, 28.0f), FVector(0.3f, 0.3f, 0.3f)));
	paperPos.Add(FTransform(FRotator(0, 0, 0), FVector(1.0f, -50.0f, 28.0f), FVector(0.3f, 0.3f, 0.3f)));
	paperPos.Add(FTransform(FRotator(0, 0, 0), FVector(0.1f, 50.0f, -28.0f), FVector(0.3f, 0.3f, 0.3f)));
	paperPos.Add(FTransform(FRotator(0, 0, 0), FVector(0.1f, 0.0f, -28.0f), FVector(0.3f, 0.3f, 0.3f)));
	paperPos.Add(FTransform(FRotator(0, 0, 0), FVector(0.1f, -50.0f, -28.0f), FVector(0.3f, 0.3f, 0.3f)));

}

// Called when the game starts or when spawned
void AQuestBoard::BeginPlay()
{
	Super::BeginPlay();

	//위젯 생성 추가
	FStringClassReference myWidgetClassRef(TEXT("/Game/UI/UI_Board.UI_Board_C"));
	UUserWidget* myWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), myWidgetClassRef.TryLoadClass<UUserWidget>());
	myWidget->AddToViewport();

	Cast<UDefaultUI>(myWidget)->parentActor = this;

	Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->AddUI(myWidget, "UI_Board");

	//Delegate 할당
	ActiveQuestBoard.AddDynamic(this, &AQuestBoard::ActiveBoard);

	requestDataArray = GetQuest();

	boxCollision->OnInputTouchEnd.AddDynamic(this, &AQuestBoard::TouchEnd);

	//
	SetPaperObjectonBoard("/Game/Blueprints/MainScene/BP_QuestPaper.BP_QuestPaper_C", false);

	AMercenaryCharacter* tempPlayerCharacter = Cast<AMercenaryCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	tempPlayerCharacter->questManager->changedQuestList.AddDynamic(this, &AQuestBoard::RefreshPaper);
}

void AQuestBoard::RefreshPaper()
{
	for (int i = papers.Num(); i >= 1; --i) {
		AActor* temp = papers.Pop();
		temp->Destroy();
	}

	SetPaperObjectonBoard("/Game/Blueprints/MainScene/BP_QuestPaper.BP_QuestPaper_C", true);
}

// Called every frame
void AQuestBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FQuestData> AQuestBoard::GetQuest()
{
	TArray<FQuestData> returnQuestArray;

	//캐릭터 얻어오기
	AMercenaryCharacter* tempPlayerCharacter = Cast<AMercenaryCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	UQuestManager* questManager = tempPlayerCharacter->questManager;

	TArray<int32> questArrayInt32 = questManager->GetQuestByDate(tempPlayerCharacter->date, 0, 7);

	for (int32 i = 0; i < questArrayInt32.Num(); i++)
	{
		returnQuestArray.Add((questManager->GetQuestData(questArrayInt32[i] - 1)));
	}

	return returnQuestArray;
}

bool AQuestBoard::SetPaperObjectonBoard(FString _PaperClassPath, bool _paperActive)
{
	//Blueprint Class Load.
	UClass* paperBlueprint = LoadObject<UClass>(nullptr, *_PaperClassPath);

	//예외처리. 퀘스트 페이지가 없을 경우.
	if (paperBlueprint == nullptr) return false;

	//Get Current Quest.
	requestDataArray = GetQuest();

	for (int i = 0; i < requestDataArray.Num(); i++) {
		//Set SpawnPaperTransform
		FTransform _SpawnPaperTransform(
			UKismetMathLibrary::Conv_VectorToRotator(UKismetMathLibrary::TransformDirection(GetActorTransform(), paperPos[i].GetRotation().Vector())),
			UKismetMathLibrary::TransformLocation(GetActorTransform(), paperPos[i].GetLocation()),
			paperPos[i].GetScale3D()
		);

		//Spawn Paper Object
		AQuestPaper* tempPaper = GetWorld()->SpawnActor<AQuestPaper>(paperBlueprint, _SpawnPaperTransform);

		tempPaper->questData = requestDataArray[i];
		papers.Add(tempPaper);
	}

	//Paper비활성화
	if (!_paperActive) {
		for (int i = 0; i < papers.Num(); i++) {
			papers[i]->SetActorHiddenInGame(true);
			papers[i]->boxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	return true;
}

void AQuestBoard::TouchEnd(ETouchIndex::Type _fingerIndex, UPrimitiveComponent* _touchedComponent)
{
	//카메라 this액터로 이동
	Cast<AMainSceneCamera>(GetWorld()->GetFirstPlayerController()->GetViewTarget())->CameraMoveTo(
		UKismetMathLibrary::TransformLocation(GetActorTransform(), targetLocation),
		UKismetMathLibrary::TransformLocation(GetActorTransform(), targetView)
	);

	//클릭 안되도록
	boxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Cast<AMainSceneCamera>(GetWorld()->GetFirstPlayerController()->GetViewTarget())->cameraMoveExit.AddDynamic(this, &AQuestBoard::ActiveUI);
	Cast<UDefaultUI>(Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->FindUI("UI_Board"))->parentActor = this;
}

void AQuestBoard::ActiveBoard()
{
	boxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	//Cast<AMainSceneCamera>(GetWorld()->GetFirstPlayerController()->GetViewTarget())->CameraMoveBegin();
}

void AQuestBoard::ActiveUI(bool _bBegin)
{
	//UI활성화
	Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->DrawUI("UI_Board");

	//뒤로가기 시 Delegate 호출을 위해 UI의 부모액터로 지정
	Cast<UDefaultUI>(Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->FindUI("UI_Board"))->parentActor = this;
}

void AQuestBoard::BeforeActiveEvent()
{
	Super::BeforeActiveEvent();

	//Paper활성화
	for (int i = 0; i < papers.Num(); i++) {
		papers[i]->SetActorHiddenInGame(false);
		papers[i]->boxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->DrawUI("UI_Board");
}

void AQuestBoard::ActiveEvent()
{

}

void AQuestBoard::UnActiveEvent()
{
	Super::UnActiveEvent();

	for (int i = 0; i < papers.Num(); i++) {
		papers[i]->SetActorHiddenInGame(true);
		papers[i]->boxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}