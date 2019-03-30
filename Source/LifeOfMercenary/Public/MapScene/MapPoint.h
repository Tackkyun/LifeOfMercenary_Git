// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "MapPoint.generated.h"

class AMapRouteSpline;

UCLASS()
class LIFEOFMERCENARY_API AMapPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapPoint();

	virtual void OnConstruction(const FTransform& Transform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitProperties() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapPoint", meta = (AllowPrivateAccess = "true"))
		//�� Point�� ����� Spline �迭.
		TArray<AMapRouteSpline*> splineArray;

	UFUNCTION(Blueprintcallable)
		//����� Spline�� �� Point�� ����.
		void SetArrayInSpline();

//#if WITH_EDITOR
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMesh* pointMesh;
	UPROPERTY(EditDefaultsOnly)
		bool bVisibleEditorOnly;
	UPROPERTY(EditDefaultsOnly)
		float pointMeshRadius;
//#endif
};
