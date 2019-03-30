// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "DefaultUI.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UDefaultUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UDefaultUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), parentActor(nullptr) {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefaultUI")
		AActor* parentActor;
};
