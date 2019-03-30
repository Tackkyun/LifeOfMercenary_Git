// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InventoryComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "LoMCharacter.generated.h"


UCLASS()
class LIFEOFMERCENARY_API ALoMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALoMCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LoMCharacter")
		UInventoryComponent* inventory;
	UPROPERTY(BlueprintReadWrite, Category = "LoMCharacter")
		bool bAttackEnable; //공격중인 상태라면 true
};
