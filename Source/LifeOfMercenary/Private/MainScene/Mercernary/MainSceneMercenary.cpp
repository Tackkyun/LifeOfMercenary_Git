// Fill out your copyright notice in the Description page of Project Settings.

#include "MainSceneMercenary.h"

void AMainSceneMercenary::BeginPlay()
{
	Super::BeginPlay();


}

void AMainSceneMercenary::BeforeActiveEvent()
{
	Super::BeforeActiveEvent();

	Cast<AHUDManager>(GetWorld()->GetFirstPlayerController()->GetHUD())->DrawUI("PlayerInformation");
}

void AMainSceneMercenary::ActiveEvent()
{
	Super::ActiveEvent();


}
