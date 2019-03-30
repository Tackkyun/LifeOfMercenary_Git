// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "LoMCamera.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCameraMoveEnter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCameraMoveExit, bool, _begin);

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ALoMCamera : public ACameraActor
{
	GENERATED_BODY()
public:
	ALoMCamera();

	virtual void Tick(float _deltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "LoMCamera")
		FCameraMoveEnter cameraMoveEnter;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "LoMCamera")
		FCameraMoveExit cameraMoveExit;
	
};
