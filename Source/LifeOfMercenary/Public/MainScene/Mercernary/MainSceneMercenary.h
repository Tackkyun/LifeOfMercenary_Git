// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainScene/MainSceneActor.h"
#include "MainSceneMercenary.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AMainSceneMercenary : public AMainSceneActor
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
	virtual void BeginPlay();

public:
	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void BeforeActiveEvent();
	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void ActiveEvent();
	
};
