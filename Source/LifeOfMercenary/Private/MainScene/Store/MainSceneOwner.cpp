// Fill out your copyright notice in the Description page of Project Settings.

#include "MainSceneOwner.h"
#include "Camera/MainSceneCamera.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Functions/LoMFunctions.h"
#include "HUDManager.h"


AMainSceneOwner::AMainSceneOwner() : Inventory(nullptr)
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	Mesh->AttachToComponent(boxCollision, FAttachmentTransformRules::KeepRelativeTransform);
}

void AMainSceneOwner::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetVisibility(false, true);
}


void AMainSceneOwner::InputTouchEnd(ETouchIndex::Type _type, UPrimitiveComponent* _primityive)
{
	AMainSceneCamera* camera = Cast<AMainSceneCamera>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget());

	if (camera->GetIsBegin()) {
		if (ULoMFunctions::GetHUDManager(GetWorld())->bEnable) {
			camera->CameraMoveTo(UKismetMathLibrary::TransformLocation(this->GetActorTransform(), targetLocation),
				UKismetMathLibrary::TransformLocation(this->GetActorTransform(), targetView));
		}
	}
}

void AMainSceneOwner::BeforeActiveEvent()
{
	Super::BeforeActiveEvent();

	Mesh->SetVisibility(true, true);

	Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->DrawUI("Store");
}

void AMainSceneOwner::ActiveEvent()
{
	Super::ActiveEvent();
}
