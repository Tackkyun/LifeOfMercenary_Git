// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/LoMMonster.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Wolf.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AWolf : public ALoMMonster
{
	GENERATED_BODY()
	
public:
	AWolf();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	
public:
	UPROPERTY(VisibleAnywhere, Category = "Wolf")
		UBoxComponent* BodyCollisionBox;
	UPROPERTY(VisibleAnywhere, Category = "Wolf")
		UBoxComponent* AttackCollisionBox;
};
