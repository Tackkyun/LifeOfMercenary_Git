// Fill out your copyright notice in the Description page of Project Settings.

#include "MapRouteSpline.h"
#include "MapPoint.h"
#include "Runtime/Engine/Classes/Engine/Engine.h" //PrintString
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"//Random
#include "Runtime/Engine/Classes/Components/SplineMeshComponent.h"//Use OnConstruction
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"//

// Sets default values
AMapRouteSpline::AMapRouteSpline()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	routeSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RouteSpline"));
	RootComponent = routeSpline;

	bVisibleEditorOnly = false;
}

void AMapRouteSpline::OnConstruction(const FTransform& _transform)
{
	Super::OnConstruction(_transform);

	//#if WITH_EDITOR
	//SetPreviewMesh
	for (int i = 0; i < routeSpline->GetNumberOfSplinePoints() - 1; i++) {
		USplineMeshComponent* tempSplineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		tempSplineMesh->SetHiddenInGame(bVisibleEditorOnly);
		tempSplineMesh->SetCastShadow(false);
		tempSplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		tempSplineMesh->SetMobility(EComponentMobility::Movable);
		tempSplineMesh->SetStaticMesh(splineMesh);
		tempSplineMesh->SetForwardAxis(ESplineMeshAxis::Z, true);
		tempSplineMesh->AttachToComponent(routeSpline, FAttachmentTransformRules::KeepRelativeTransform);
		//tempSplineMesh->AttachToComponent(routeSpline, FAttachmentTransformRules::KeepRelativeTransform);
		tempSplineMesh->SetStartAndEnd(
			routeSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local),
			routeSpline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local),
			routeSpline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local),
			routeSpline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Local), true);
		tempSplineMesh->AddLocalOffset(FVector(0.0f, 0.0f, 0.0f));
		tempSplineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//SetPreviewText
	if (splinePart.Num() <= 0) {
		SetPreviewText(FText::FromName(TEXT("None")), (routeSpline->GetSplineLength() / 2.0f) - 100.0f, FColor(105, 65, 0, 0));
	}
	else {
		//루프
		for (int i = 0; i < splinePart.Num(); i++) {
			SetPreviewText(FText::FromString(FString::FromInt(i)), i * routeSpline->GetSplineLength() / splinePart.Num(), FColor(105, 65, 0, 0));
		}
		//End
		SetPreviewText(FText::FromName(TEXT("END")), routeSpline->GetSplineLength() - 150.0f, FColor(0, 0, 0, 0));
	}

	RegisterAllComponents();

	//#endif
}

//#if WITH_EDITOR
void AMapRouteSpline::SetPreviewText(FText _text, float _distance, FColor _color)
{
	UTextRenderComponent* tempTextRender = NewObject<UTextRenderComponent>(this, UTextRenderComponent::StaticClass());
	tempTextRender->SetHiddenInGame(bVisibleEditorOnly);
	tempTextRender->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	tempTextRender->SetMobility(EComponentMobility::Movable);
	tempTextRender->SetText(_text);
	tempTextRender->AttachToComponent(routeSpline, FAttachmentTransformRules::KeepRelativeTransform);

	FVector textLocation = routeSpline->GetLocationAtDistanceAlongSpline(_distance, ESplineCoordinateSpace::World);
	textLocation.Z += 10.0f;

	FRotator textRot = routeSpline->GetRotationAtDistanceAlongSpline(_distance, ESplineCoordinateSpace::World);
	textRot.Pitch = 90.0f;
	textRot.Yaw += 90.0f;

	tempTextRender->SetWorldTransform(FTransform(textRot, textLocation, FVector(1.0f, 1.0f, 1.0f)));

	tempTextRender->SetWorldSize(100.0f);
	tempTextRender->SetTextRenderColor(_color);
}
//#endif

// Called when the game starts or when spawned
void AMapRouteSpline::BeginPlay()
{
	Super::BeginPlay();

	//#if WITH_EDITOR
	//SetPreviewMesh
	for (int i = 0; i < routeSpline->GetNumberOfSplinePoints() - 1; i++) {
		USplineMeshComponent* tempSplineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		tempSplineMesh->SetHiddenInGame(bVisibleEditorOnly);
		tempSplineMesh->SetCastShadow(false);
		tempSplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		tempSplineMesh->SetMobility(EComponentMobility::Movable);
		tempSplineMesh->SetStaticMesh(splineMesh);
		tempSplineMesh->SetForwardAxis(ESplineMeshAxis::Z, true);
		tempSplineMesh->AttachToComponent(routeSpline, FAttachmentTransformRules::KeepRelativeTransform);
		//tempSplineMesh->AttachToComponent(routeSpline, FAttachmentTransformRules::KeepRelativeTransform);
		tempSplineMesh->SetStartAndEnd(
			routeSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local),
			routeSpline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local),
			routeSpline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local),
			routeSpline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Local), true);
		tempSplineMesh->AddLocalOffset(FVector(0.0f, 0.0f, 0.0f));
		tempSplineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//SetPreviewText
	if (splinePart.Num() <= 0) {
		SetPreviewText(FText::FromName(TEXT("None")), (routeSpline->GetSplineLength() / 2.0f) - 100.0f, FColor(105, 65, 0, 0));
	}
	else {
		//루프
		for (int i = 0; i < splinePart.Num(); i++) {
			SetPreviewText(FText::FromString(FString::FromInt(i)), i * routeSpline->GetSplineLength() / splinePart.Num(), FColor(105, 65, 0, 0));
		}
		//End
		SetPreviewText(FText::FromName(TEXT("END")), routeSpline->GetSplineLength() - 150.0f, FColor(0, 0, 0, 0));
	}

	RegisterAllComponents();

	//#endif

	//비용 == Spline길이
	cost = routeSpline->GetSplineLength();
	//비용 = 길이 + (위험도 - 내 전투력) + 목적지에서 얼마나 먼지.
}

// Called every frame
void AMapRouteSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


AMapPoint* AMapRouteSpline::GetOtherPoint(AMapPoint* _point)
{
	if (_point == linkedPoint[0]) return linkedPoint[1];
	else return linkedPoint[0];
}

AMapPoint* AMapRouteSpline::GetPoint(bool _num) {
	if (_num) return linkedPoint[1];
	else return linkedPoint[0];
}


int32 AMapRouteSpline::PointStartDirection(AMapPoint* _point, bool _reverse)
{
	//위치와 reverse상태에 따른 XOR연산
	if (((_point->GetActorLocation() - routeSpline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World)).Size() <
		(_point->GetActorLocation() - routeSpline->GetLocationAtSplinePoint(routeSpline->GetSplineLength(), ESplineCoordinateSpace::World)).Size()) ^ _reverse)
	{
		return 1;
	}
	else {
		return -1;
	}
}

bool AMapRouteSpline::PointStartDirectionBoolean(AMapPoint * _point, bool _reverse)
{
	//위치와 reverse상태에 따른 XOR연산
	if (((_point->GetActorLocation() - routeSpline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World)).Size() <
		(_point->GetActorLocation() - routeSpline->GetLocationAtSplinePoint(routeSpline->GetSplineLength(), ESplineCoordinateSpace::World)).Size()) ^ _reverse)
	{
		return true;
	}
	else {
		return false;
	}
}

int32 AMapRouteSpline::GetEventNumber()
{
	return eventPosArray.Num();
}

void AMapRouteSpline::SetSplineEvent()
{
	//if (splinePart != nullptr) {
	for (int32 i = 0; i < splinePart.Num(); i++) {
		eventPosArray.Add(UKismetMathLibrary::RandomFloatInRange((float(i) / (splinePart.Num())), (float(i + 1) / (splinePart.Num()))));
	}
	//}
}

void AMapRouteSpline::EventCall(float _pos, bool _direction)
{
	//이벤트 지점이 존재하면
	if (eventPosArray.Num() > 0) {
		if (_direction) {
			//정방향으로 위치 도달여부 확인.
			if (_pos >= eventPosArray[0]) {
				//이벤트

				eventPosArray.RemoveAt(0);

				//레벨오픈
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Event! %f"));
			}
		}
		else {
			//역방향으로 위치 도달여부 확인
			if (_pos <= eventPosArray[eventPosArray.Num() - 1]) {
				//이벤트

				eventPosArray.RemoveAt(eventPosArray.Num() - 1);

				//레벨오픈
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Event! %f"));
			}
		}
	}
}

