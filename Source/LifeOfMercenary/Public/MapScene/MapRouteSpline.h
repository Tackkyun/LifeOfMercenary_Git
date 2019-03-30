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
	//이 Spline이 연결된 Point. 양끝, 2개 연결되어 있음.
	AMapPoint* linkedPoint[2];

	//비용
	float cost;

	UFUNCTION(BlueprintCallable)
		//입력된 Point가 아닌 Point를 반환
		AMapPoint* GetOtherPoint(AMapPoint* _point);

	UFUNCTION(BlueprintCallable)
		//Spline에 연결된 Point를 반환. 0이면 0번째에 1이면 1번째에 들어있는 Point를 반환.
		AMapPoint* GetPoint(bool _num);

	UFUNCTION(BlueprintCallable)
		//정방향으로 시작하면 1, 역방향으로 시작하면 -1 반환
		int32 PointStartDirection(AMapPoint* _point, bool _reverse = false);

	bool PointStartDirectionBoolean(AMapPoint* _point, bool _reverse = false);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "RouteSpline")
		//Event구간을 위한 변수. 갯수만큼 Event구간이 늘어남.
		TArray<FSplinePartValue> splinePart;


	//Event
private:
	//0.0~1.0f 비율로 위치기록. SAVE
	TArray<float> eventPosArray;

public:
	//남은 이벤트 갯수 얻어오기
	int32 GetEventNumber();
	//위치 랜덤으로 지정.
	void SetSplineEvent();
	//이벤트 호출. 위치를 비율로 받아옴. 정방향이면 true 역방향이면 false입력
	void EventCall(float _pos, bool _direction = true);

	//Editor전용
//#if WITH_EDITOR
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMesh* splineMesh;
	UPROPERTY(EditDefaultsOnly)
		bool bVisibleEditorOnly;

	void SetPreviewText(FText _text, float _distance, FColor _color);
//#endif
	
};
