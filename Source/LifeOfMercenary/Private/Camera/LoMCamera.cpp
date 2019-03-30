// Fill out your copyright notice in the Description page of Project Settings.

#include "LoMCamera.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ALoMCamera::ALoMCamera()
{

}

void ALoMCamera::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(this);
}

void ALoMCamera::Tick(float _deltaSeconds)
{
	Super::Tick(_deltaSeconds);

}