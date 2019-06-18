// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LifeOfMercenary/Public/MapScene/MapCharacter.h"
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
	UPROPERTY(BlueprintReadWrite, Category = Equipment)
	FString m_hasPoint;
	UPROPERTY(BlueprintReadWrite, Category = Equipment)
	FString m_hasSpline;
	UPROPERTY(BlueprintReadWrite, Category = Equipment)
	FString m_targetPoint;
	
	UPROPERTY(BlueprintReadWrite, Category = Equipment)
	FTransform m_characterTransform;
	
	UPROPERTY(BlueprintReadWrite, Category = Equipment)
	TArray<int32> m_SFT;

public:
	UFUNCTION(BlueprintCallable, Category = PlayerSaveGame)
		void SaveCharacter(const AMapCharacter* const _mapChar);

	UFUNCTION(BlueprintCallable, Category = PlayerSaveGame)
		void LoadCharacter(const UObject* _world, AMapCharacter* const _mapChar);

	//SplineStatus

public:
	UPROPERTY(BlueprintReadWrite, Category = PlayerSaveGame)
		FString saveSlotName;

	UPROPERTY(BlueprintReadWrite, Category = PlayerSaveGame)
		int32 userIndex;
	
};
