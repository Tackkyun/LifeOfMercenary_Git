// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LoMCharacter.h"
#include "LoMMonster.generated.h"

UENUM(BlueprintType)
enum class EMonsterStateType : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	AttackReady	UMETA(DisplayName = "AttackReady"),
	Attack		UMETA(DisplayName = "Attack"),
	Damage		UMETA(DisplayName = "Damage"),
};

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ALoMMonster : public ALoMCharacter
{
	GENERATED_BODY()
public:
	ALoMMonster();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "LoMMonster")
		float attackRange;
	UPROPERTY(BlueprintReadWrite, Category = "LoMMonster")
		AActor* targetActor;
	UPROPERTY(BlueprintReadWrite, Category = "LoMMonster")
		EMonsterStateType currentState;
	UPROPERTY(BlueprintReadWrite, Category = "LoMMonster")
		bool bGoBack;
};
