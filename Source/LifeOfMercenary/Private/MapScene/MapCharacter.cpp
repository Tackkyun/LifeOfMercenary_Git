// Fill out your copyright notice in the Description page of Project Settings.

#include "MapCharacter.h"
#include "MapRouteSpline.h"
#include "MapPoint.h"


// Sets default values
AMapCharacter::AMapCharacter() : MovementSpeed(1000.0f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMapCharacter::OnConstruction(const FTransform& _transform)
{
	Super::OnConstruction(_transform);
}

// Called when the game starts or when spawned
void AMapCharacter::BeginPlay()
{
	Super::BeginPlay();

	doOnce = true;

	//적용 시 주석 풀것
	StopMove();
}

// Called every frame
void AMapCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	if (doOnce) {
	StopMove();
	if (SetMove(targetPoint)) {
	//최초 이벤트세팅
	hasSpline->SetSplineEvent();
	}
	doOnce = false;
	}*/

	Move();
}

// Called to bind functionality to input
void AMapCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AMapCharacter::FindRoute(AMapPoint* _targetPoint) {
	SFT.Empty();

	//방문된 RouteSpline 기록
	TArray<AMapRouteSpline*> visitedSpline;
	//각 포인트의 가장 빠른 이전 RouteSpline과 비용 기록
	TMap<AMapPoint*, AStarSplineFastRoute> fastRoute;

	//다음 검색할 Point들을 기록
	TArray<AMapPoint*> q;

	//현재 위치를 검색목록에 추가.
	q.Add(hasPoint);
	fastRoute.Add(hasPoint);

	//현재 검색위치.
	AMapPoint* currentPoint = nullptr;

	while (q.Num() > 0) {
		//가장 비용이 낮은 Point POP. Cost + 목적지까지 거리
		currentPoint = q[0];

		for (int i = 0; i < q.Num(); i++) {
			currentPoint = (fastRoute.Find(q[i])->fastCost + (q[i]->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) <
				(fastRoute.Find(currentPoint)->fastCost + (currentPoint->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) ? q[i] : currentPoint;
		}
		q.RemoveAt(q.Find(currentPoint));

		//목적지에 도달했다면, 변경?
		if (currentPoint == _targetPoint)
			break;

		//현재 Point와 연결된 모든 Spline과 반대편 Point를 확인.
		for (int i = 0; i < currentPoint->splineArray.Num(); i++) {
			//방문 흔적이 있다면 다음으로.
			if (visitedSpline.Find(currentPoint->splineArray[i]) != INDEX_NONE) continue;

			//Spline 반대쪽에 있는 Point. 다음 Point
			AMapPoint* tempPoint = currentPoint->splineArray[i]->GetOtherPoint(currentPoint);

			//다음 Point가 최단거리 목록이 없다면, 추가
			if (!fastRoute.Contains(tempPoint))
				fastRoute.Add(tempPoint);

			//다음 Point에 최단거리 기록이 안돼있다면,
			if (fastRoute.Find(tempPoint)->fastSpline == nullptr) {
				//현재 Point로 오는 길과 비용을 최단거리로 기록
				fastRoute.Find(tempPoint)->fastSpline = currentPoint->splineArray[i];
				fastRoute.Find(tempPoint)->fastCost = fastRoute.Find(currentPoint)->fastCost + currentPoint->splineArray[i]->cost;

				//검색목록에 다음 Point를 추가.
				q.Push(tempPoint);

				//방문된 RouteSpline에 추가
				visitedSpline.Push(currentPoint->splineArray[i]);
			}
			//다음 Point에 최단거리 기록이 있으나, 새로운 최단거리가 더 빠르다면,
			else if (fastRoute.Find(tempPoint)->fastCost > fastRoute.Find(currentPoint)->fastCost + currentPoint->splineArray[i]->cost) {
				//현재 Point로 오는 길과 비용을 최단거리로 기록
				fastRoute.Find(tempPoint)->fastSpline = currentPoint->splineArray[i];
				fastRoute.Find(tempPoint)->fastCost = fastRoute.Find(currentPoint)->fastCost + currentPoint->splineArray[i]->cost;

				//방문된 RouteSpline에 추가
				visitedSpline.Push(currentPoint->splineArray[i]);
			}
		}

		//길을 못찾았으면,
		if (q.Num() <= 0) return false;
	}

	//처음 위치로 부터 목적지까지의 최단거리 Spline을 모아 기록.
	while (currentPoint != hasPoint)
	{
		SFT.Push(fastRoute.Find(currentPoint)->fastSpline);
		currentPoint = fastRoute.Find(currentPoint)->fastSpline->GetOtherPoint(currentPoint);
	}

	return true;
}

bool AMapCharacter::SingleFindRoute(AMapPoint* _targetPoint)
{
	//현재 Point와 연결된 RouteSpline만 검색
	for (int i = 0; i < hasPoint->splineArray.Num(); i++) {
		if (hasPoint->splineArray[i]->GetOtherPoint(hasPoint) == _targetPoint) {
			SFT.Push(hasPoint->splineArray[i]);
			return true;
		}
	}

	return false;
}

bool AMapCharacter::SetMove(AMapPoint* _targetPoint)
{
	//예외처리
	if (_targetPoint == nullptr) return false;
	if (hasPoint == nullptr) return false;
	if (hasPoint == _targetPoint) return false;

	//이동중이 아니고, 저장된 최단거리 기록이 없을경우.
	if (StartMove() && SFT.Num() <= 0) {
		targetPoint = _targetPoint;
		//1단계 검색에서 목적지가 나오지 않는다면,
		if (!SingleFindRoute(_targetPoint)) {
			//A*검색
			if (!FindRoute(_targetPoint)) {
				//검색결과가 없으면 false return
				return false;
			}
		}

		//다음 이동해야 할 RouteSpline
		hasSpline = SFT.Pop();
		//RouteSpline이 정방향인지 역방향인지 세팅
		if (hasSpline->PointStartDirectionBoolean(hasPoint))
			distanceAlongSpline = 0.0f;
		else
			distanceAlongSpline = 1.0f;

		hasSpline->SetSplineEvent();
		return true;
	}
	else {
		return false;
	}
}

void AMapCharacter::StopMove()
{
	SetActorTickEnabled(false);//InActive Tick
}

bool AMapCharacter::StartMove()
{
	if (!IsActorTickEnabled()) {
		SetActorTickEnabled(true);//Active Tick
		return true;
	}
	else {
		return false;
	}
}

void AMapCharacter::Move()
{
	if (hasSpline == nullptr || targetPoint == hasPoint) {
		StopMove();
		return;
	}

	//다음 이동포인트 좌표
	const FVector destination = hasSpline->routeSpline->GetLocationAtDistanceAlongSpline(distanceAlongSpline * hasSpline->routeSpline->GetSplineLength(), ESplineCoordinateSpace::World);

	//LineTrace를 이용하여 다음 이동 z위치를 얻어옴. 지점 기준은 LandScape
	TArray<AActor*> tempActorArray;
	TArray<FHitResult> landScape;
	UKismetSystemLibrary::LineTraceMulti(GetWorld(),
		FVector(destination.X, destination.Y, GetActorLocation().Z + 1000.0f),
		FVector(destination.X, destination.Y, GetActorLocation().Z - 1000.0f),
		ETraceTypeQuery::TraceTypeQuery1,
		false, tempActorArray, EDrawDebugTrace::None, landScape, true);

	//===================== 이동 ==========================
	//Spline의 해당(비율) 위치 좌표 불러옴.
	FVector movePos = destination;
	//목적지의 XY위치와 캐릭터 Z위치 합성 및 방향벡터 확인.
	movePos = (FVector(movePos.X, movePos.Y, landScape[0].Location.Z) - GetActorLocation());
	movePos = movePos / movePos.Size();

	AddMovementInput(movePos, MovementSpeed / 1000.0f);
	//=====================================================

	//===================== 이벤트 발생 ===========================
	if (hasSpline->GetEventNumber() > 0)
		hasSpline->EventCall(distanceAlongSpline, hasSpline->PointStartDirectionBoolean(hasPoint));
	//=============================================================

	//다음위치 얻어오기. distanceAlongSpline에 비율(0~1.0f)로 기록
	//다음 이동포인트까지 도착했는지 확인.
	if ((destination - FVector(GetActorLocation().X, GetActorLocation().Y, destination.Z)).Size() < 50.0f) {
		//중간 목적지에 도착했다면
		if (distanceAlongSpline < 0.0f || distanceAlongSpline > 1.0f) {
			//최종목적지가 아니라면
			if (SFT.Num() > 0) {
				//도착한 곳을 현재위치로
				hasPoint = hasSpline->GetOtherPoint(hasPoint);
				//최단거리 배열에서 다음 Spline을 얻어옴.
				hasSpline = SFT.Pop();
				//시작지점이 정방향인지 역방향인지 확인하여 세팅(0.0f 정방향, 1.0f 역방향)
				if (hasSpline->PointStartDirectionBoolean(hasPoint)) {
					distanceAlongSpline = 0.0f;
				}
				else {
					distanceAlongSpline = 1.0f;
				}

				//이벤트 세팅
				hasSpline->SetSplineEvent();
			}
			//최종목적지라면
			else {
				//도착한 곳을 현재위치로
				hasPoint = hasSpline->GetOtherPoint(hasPoint);
				//이동 종료.
				StopMove();
			}
		}
		//아직 진행중이라면,
		else {
			//다음 지점 받아옴. PointStartLengthZero()는 정방향인지 역방향인지 양음수 역할.
			distanceAlongSpline += GetWorld()->DeltaTimeSeconds * MovementSpeed * hasSpline->PointStartDirection(hasPoint) / hasSpline->routeSpline->GetSplineLength();
			//비율 = 경과시간 * (속도 / 총 길이)
		}
	}
}
