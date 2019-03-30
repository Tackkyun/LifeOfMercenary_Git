// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MapScenePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AMapScenePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintReadWrite)
	AMapCharacter* mapCharacter;
	
};
