// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainScene/Gamble/GambleBase.h"
#include "GambleExample.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AGambleExample : public AGambleBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "GambleExample")
		int32 SetNumber();

	UFUNCTION(BlueprintCallable, Category = "GambleExample")
		void GameFinish(int32 _num);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GambleExample")
		int32 randNumber;
};
