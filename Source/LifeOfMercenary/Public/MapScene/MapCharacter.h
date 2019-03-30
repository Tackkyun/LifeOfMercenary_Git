// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MapCharacter.generated.h"

class AMapRouteSpline;
class AMapPoint;

struct AStarSplineFastRoute {
	float fastCost;
	AMapRouteSpline* fastSpline;
};

UCLASS()
class LIFEOFMERCENARY_API AMapCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMapCharacter();

	virtual void OnConstruction(const FTransform& _transform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//임시
	bool doOnce;

public:
	//A*호출과 최초세팅 및 StartMove가 포함. 이미 이동중이거나, 진행중인 이동루트가 있다면 return false.
	UFUNCTION(Blueprintcallable)
		bool SetMove(AMapPoint* _targetPoint);

	//Tick 중지.
	void StopMove();
	//Tick 시작. 이미 이동중이거나, 목적지에 도착한 상태라면, return false
	bool StartMove();

protected:
	//이동. Tick에서 호출.
	void Move();

protected:
	//1단계 길찾기. 바로 주변만 검색. 찾지 못하였을 경우 false반환
	bool SingleFindRoute(AMapPoint* _targetPoint);
	//A* 길찾기
	bool FindRoute(AMapPoint* _targetPoint);

public:
	UPROPERTY(BlueprintReadOnly)
		//현재(도착한 경우엔 직전) Spline. save
		AMapRouteSpline* hasSpline;

	UPROPERTY(EditAnywhere, Blueprintable, BlueprintReadWrite, Category = "SplineActor")
		//현재 Point. save
		AMapPoint* hasPoint;

	UPROPERTY(EditAnywhere, Blueprintable, BlueprintReadWrite, Category = "SplineActor")
		//목적 Point. save
		AMapPoint* targetPoint;

	UPROPERTY(EditAnywhere, Blueprintable, BlueprintReadWrite, Category = "SplineActor")
		//이동속도
		float MovementSpeed;

	//다음 이동 위치를 비율(0.0~1.0f)로 기록. SAVE
	float distanceAlongSpline;

	//A* 최단거리. SAVE
	TArray<AMapRouteSpline*> SFT;
};
