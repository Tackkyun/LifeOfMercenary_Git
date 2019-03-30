// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"
#include "MapRouteSpline.generated.h"

class AMapPoint;

USTRUCT(BlueprintType)
struct FSplinePartValue {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int32> spawnMonster;
};

UCLASS()
class LIFEOFMERCENARY_API AMapRouteSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapRouteSpline();

	virtual void OnConstruction(const FTransform& _transform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadWrite)
		USplineComponent* routeSpline;

public:
	//�� Spline�� ����� Point. �糡, 2�� ����Ǿ� ����.
	AMapPoint* linkedPoint[2];

	//���
	float cost;

	UFUNCTION(BlueprintCallable)
		//�Էµ� Point�� �ƴ� Point�� ��ȯ
		AMapPoint* GetOtherPoint(AMapPoint* _point);

	UFUNCTION(BlueprintCallable)
		//Spline�� ����� Point�� ��ȯ. 0�̸� 0��°�� 1�̸� 1��°�� ����ִ� Point�� ��ȯ.
		AMapPoint* GetPoint(bool _num);

	UFUNCTION(BlueprintCallable)
		//���������� �����ϸ� 1, ���������� �����ϸ� -1 ��ȯ
		int32 PointStartDirection(AMapPoint* _point, bool _reverse = false);

	bool PointStartDirectionBoolean(AMapPoint* _point, bool _reverse = false);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "RouteSpline")
		//Event������ ���� ����. ������ŭ Event������ �þ.
		TArray<FSplinePartValue> splinePart;


	//Event
private:
	//0.0~1.0f ������ ��ġ���. SAVE
	TArray<float> eventPosArray;

public:
	//���� �̺�Ʈ ���� ������
	int32 GetEventNumber();
	//��ġ �������� ����.
	void SetSplineEvent();
	//�̺�Ʈ ȣ��. ��ġ�� ������ �޾ƿ�. �������̸� true �������̸� false�Է�
	void EventCall(float _pos, bool _direction = true);

	//Editor����
//#if WITH_EDITOR
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMesh* splineMesh;
	UPROPERTY(EditDefaultsOnly)
		bool bVisibleEditorOnly;

	void SetPreviewText(FText _text, float _distance, FColor _color);
//#endif
	
};
