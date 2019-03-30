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
	//�ӽ�
	bool doOnce;

public:
	//A*ȣ��� ���ʼ��� �� StartMove�� ����. �̹� �̵����̰ų�, �������� �̵���Ʈ�� �ִٸ� return false.
	UFUNCTION(Blueprintcallable)
		bool SetMove(AMapPoint* _targetPoint);

	//Tick ����.
	void StopMove();
	//Tick ����. �̹� �̵����̰ų�, �������� ������ ���¶��, return false
	bool StartMove();

protected:
	//�̵�. Tick���� ȣ��.
	void Move();

protected:
	//1�ܰ� ��ã��. �ٷ� �ֺ��� �˻�. ã�� ���Ͽ��� ��� false��ȯ
	bool SingleFindRoute(AMapPoint* _targetPoint);
	//A* ��ã��
	bool FindRoute(AMapPoint* _targetPoint);

public:
	UPROPERTY(BlueprintReadOnly)
		//����(������ ��쿣 ����) Spline. save
		AMapRouteSpline* hasSpline;

	UPROPERTY(EditAnywhere, Blueprintable, BlueprintReadWrite, Category = "SplineActor")
		//���� Point. save
		AMapPoint* hasPoint;

	UPROPERTY(EditAnywhere, Blueprintable, BlueprintReadWrite, Category = "SplineActor")
		//���� Point. save
		AMapPoint* targetPoint;

	UPROPERTY(EditAnywhere, Blueprintable, BlueprintReadWrite, Category = "SplineActor")
		//�̵��ӵ�
		float MovementSpeed;

	//���� �̵� ��ġ�� ����(0.0~1.0f)�� ���. SAVE
	float distanceAlongSpline;

	//A* �ִܰŸ�. SAVE
	TArray<AMapRouteSpline*> SFT;
};
