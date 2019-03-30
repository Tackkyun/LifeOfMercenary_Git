// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/MainScene/Gamble/GambleBase.h"
#include "LifeOfMercenary/Public/Character/LoMCharacter.h"
#include "LifeOfMercenary/Public/Components/InventoryComponent.h"
#include "LifeOfMercenary/Public/Camera/MainSceneCamera.h"
#include "Kismet/KismetMathLibrary.h"
#include "LifeOfMercenary/Public/UI/DefaultUI.h"
#include "LifeOfMercenary/Public/MainScene/GameMode/HUDManager.h"


void AGambleBase::BeginPlay()
{
	Super::BeginPlay();

	m_playerGold = &Cast<ALoMCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->inventory->gold;
	m_betMultiplyingFactor = 1.0f;

	//위젯 생성 추가
	FStringClassReference myWidgetClassRef(TEXT("/Game/UI/UI_Gamble.UI_Gamble_C"));
	UUserWidget* myWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), myWidgetClassRef.TryLoadClass<UUserWidget>());
	myWidget->AddToViewport();

	Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->AddUI(myWidget, "UI_Gamble");
	Cast<UDefaultUI>(Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->FindUI("UI_Gamble"))->parentActor = this;
}

void AGambleBase::SetPlayerGold(int32 _variationGold)
{
	*m_playerGold += _variationGold;

	if (*m_playerGold < 0) {
		*m_playerGold = 0;
	}
}

void AGambleBase::InputTouchEnd(ETouchIndex::Type _type, UPrimitiveComponent* _primityive)
{
	//카메라 this액터로 이동
	Cast<AMainSceneCamera>(GetWorld()->GetFirstPlayerController()->GetViewTarget())->CameraMoveTo(
		UKismetMathLibrary::TransformLocation(GetActorTransform(), targetLocation),
		UKismetMathLibrary::TransformLocation(GetActorTransform(), targetView)
	);

	//Cast<AMainSceneCamera>(GetWorld()->GetFirstPlayerController()->GetViewTarget())->cameraMoveExit.AddDynamic(this, &AGambleBase::ActiveUI);
}

void AGambleBase::ActiveUI(bool _bBegin)
{
	//UI활성화
	Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->DrawUI("UI_Gamble");

	//뒤로가기 시 Delegate 호출을 위해 UI의 부모액터로 지정
	Cast<UDefaultUI>(Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->FindUI("UI_Gamble"))->parentActor = this;
}


void AGambleBase::BeforeActiveEvent()
{
	Super::BeforeActiveEvent();

	Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->DrawUI("UI_Gamble");
}

void AGambleBase::ActiveEvent()
{
	Super::ActiveEvent();
}

