// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LoMMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ALoMMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALoMMonsterAIController();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LoMMonsterAIController")
		FVector TwoCircleNodeVector(FVector _vOne, float _fOneRadius, FVector _vTwo, float _fTwoRadius, bool bElse = true);

	UFUNCTION(BlueprintCallable, Category = "LoMMonsterAIController")
		FVector MoveTarget(FVector _vTarget, float _fRotSpeed, float _fStopDist = 200.f);
protected:
	virtual void BeginPlay() override;

};
