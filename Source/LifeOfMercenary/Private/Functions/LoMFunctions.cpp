// Fill out your copyright notice in the Description page of Project Settings.

#include "LoMFunctions.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UDataTable* ULoMFunctions::GetDataTableFromString(const FString& _dataTablePath)
{
	ConstructorHelpers::FObjectFinder<UDataTable> ExcelTable_BP(*_dataTablePath);
	return ExcelTable_BP.Object;
}

AMainSceneCamera* ULoMFunctions::GetMainSceneCamera(const UObject* _world)
{
	return Cast<AMainSceneCamera>(UGameplayStatics::GetPlayerController(_world, 0)->GetViewTarget());
}

AHUDManager* ULoMFunctions::GetHUDManager(const UObject* _world)
{
	return Cast<AHUDManager>(UGameplayStatics::GetPlayerController(_world, 0)->GetHUD());
}