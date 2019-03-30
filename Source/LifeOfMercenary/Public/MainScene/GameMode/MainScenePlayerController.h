// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MapCharacter.h"
#include "MainScenePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AMainScenePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<AMainSceneActor*> mainSceneActorArray;
};
