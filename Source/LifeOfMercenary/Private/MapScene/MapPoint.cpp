// Fill out your copyright notice in the Description page of Project Settings.

#include "MapPoint.h"


// Sets default values
AMapPoint::AMapPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bVisibleEditorOnly = false;
	pointMeshRadius = 3.0f;
}


void AMapPoint::PostInitProperties()
{
	Super::PostInitProperties();

}

void AMapPoint::OnConstruction(const FTransform& _transform)
{
	Super::OnConstruction(_transform);

	//액터 갱신 시, 연결된 Spline의 끝 위치를 액터 한가운데로.
	for (int i = 0; i < splineArray.Num(); i++) {
		if (splineArray[i] != nullptr) {
			if ((GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World)).Size() >
				(GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(splineArray[i]->routeSpline->GetSplineLength(), ESplineCoordinateSpace::World)).Size()) {
				splineArray[i]->routeSpline->SetLocationAtSplinePoint(splineArray[i]->routeSpline->GetNumberOfSplinePoints() - 1, GetActorLocation(), ESplineCoordinateSpace::World, true);
			}
			else {
				splineArray[i]->routeSpline->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::World, true);
			}
		}
	}

	UStaticMeshComponent* tempMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	tempMesh->SetHiddenInGame(bVisibleEditorOnly);
	tempMesh->SetCastShadow(false);
	tempMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	tempMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	tempMesh->SetMobility(EComponentMobility::Movable);
	tempMesh->SetStaticMesh(pointMesh);
	tempMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	tempMesh->SetRelativeScale3D(tempMesh->RelativeScale3D * pointMeshRadius);

	RegisterAllComponents();
}

// Called when the game starts or when spawned
void AMapPoint::BeginPlay()
{
	Super::BeginPlay();

	//#if WITH_EDITOR
	//액터 갱신 시, 연결된 Spline의 끝 위치를 액터 한가운데로.
	for (int i = 0; i < splineArray.Num(); i++) {
		if (splineArray[i] != nullptr) {
			if ((GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World)).Size() >
				(GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(splineArray[i]->routeSpline->GetSplineLength(), ESplineCoordinateSpace::World)).Size()) {
				splineArray[i]->routeSpline->SetLocationAtSplinePoint(splineArray[i]->routeSpline->GetNumberOfSplinePoints() - 1, GetActorLocation(), ESplineCoordinateSpace::World, true);
			}
			else {
				splineArray[i]->routeSpline->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::World, true);
			}
		}
	}


	UStaticMeshComponent* tempMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	tempMesh->SetHiddenInGame(bVisibleEditorOnly);
	tempMesh->SetCastShadow(false);
	tempMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	tempMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	tempMesh->SetMobility(EComponentMobility::Movable);
	tempMesh->SetStaticMesh(pointMesh);
	tempMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	tempMesh->SetRelativeScale3D(tempMesh->RelativeScale3D * pointMeshRadius);

	RegisterAllComponents();
	//#endif

	SetArrayInSpline();
}

// Called every frame
void AMapPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapPoint::SetArrayInSpline()
{
	//Spline 세팅
	for (int i = 0; i < splineArray.Num(); i++) {
		float dist0 = (GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World)).Size();
		float dist1 = (GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(splineArray[i]->routeSpline->GetSplineLength(), ESplineCoordinateSpace::World)).Size();

		if (dist1 > dist0) {
			splineArray[i]->linkedPoint[0] = this;
		}
		else {
			splineArray[i]->linkedPoint[1] = this;
		}
	}
}

