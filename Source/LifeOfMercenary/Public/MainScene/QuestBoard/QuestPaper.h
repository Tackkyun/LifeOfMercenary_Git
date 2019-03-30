// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LifeOfMercenary/Public/Quest/QuestManager.h"
#include "Components/StaticMeshComponent.h" //boxmesh
#include "Components/BoxComponent.h" //boxcollision
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "LifeOfMercenary/Public/UI/DefaultUI.h"
#include "QuestPaper.generated.h"

UCLASS()
class LIFEOFMERCENARY_API AQuestPaper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestPaper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//소지하고 있는 Quest Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paper")
		FQuestData questData;

	//Components
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USceneComponent* paperRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* paperMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* paperWidget;
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Board")
		void TouchEnd(ETouchIndex::Type _fingerIndex, UPrimitiveComponent* _touchedComponent);

};
