// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainScene/MainSceneActor.h"
#include "Components/InventoryComponent.h"
#include "MainSceneOwner.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AMainSceneOwner : public AMainSceneActor
{
	GENERATED_BODY()

public:
	AMainSceneOwner();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MainSceneOwner")
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MainSceneOwner")
		UInventoryComponent* Inventory;

	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void InputTouchEnd(ETouchIndex::Type _type, UPrimitiveComponent* _primityive);

	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void BeforeActiveEvent();
	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void ActiveEvent();
};
