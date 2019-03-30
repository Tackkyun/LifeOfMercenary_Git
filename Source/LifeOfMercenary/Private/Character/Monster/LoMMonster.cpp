// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Monster/LoMMonster.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ALoMMonster::ALoMMonster() : attackRange(0.f), targetActor(nullptr), currentState(EMonsterStateType::Idle),
bGoBack(false)
{

}

void ALoMMonster::BeginPlay()
{
	Super::BeginPlay();
	//this->GetCapsuleComponent()->GetScaledCapsuleRadius()
	attackRange = this->GetCapsuleComponent()->GetScaledCapsuleRadius()+120.f;
	targetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ALoMMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

