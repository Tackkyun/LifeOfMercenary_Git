// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MapSceneSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UMapSceneSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UMapSceneSaveGame();
	
public:
	UPROPERTY(BlueprintReadWrite, Category = PlayerSaveGame)
		FString saveSlotName;

	UPROPERTY(BlueprintReadWrite, Category = PlayerSaveGame)
		int32 userIndex;
	
};
