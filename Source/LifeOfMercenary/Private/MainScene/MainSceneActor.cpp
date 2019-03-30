// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/MainScene/MainSceneActor.h"
#include "MainScenePlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Core/Public/Math/RotationMatrix.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMainSceneActor::AMainSceneActor() : targetLocation(0,0,0), targetView(0,0,0)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	boxCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	boxCollision->SetCollisionProfileName("UI");
}

// Called when the game starts or when spawned
void AMainSceneActor::BeginPlay()
{
	Super::BeginPlay();
	boxCollision->OnInputTouchEnd.AddDynamic(this, &AMainSceneActor::InputTouchEnd);

	boxCollision->SetVisibility(false, true);
	boxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (!Cast<AMainScenePlayerController>(GetWorld()->GetFirstPlayerController())->mainSceneActorArray.Contains(this))
		Cast<AMainScenePlayerController>(GetWorld()->GetFirstPlayerController())->mainSceneActorArray.Add(this);
}

// Called every frame
void AMainSceneActor::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void AMainSceneActor::InputTouchEnd(ETouchIndex::Type _type, UPrimitiveComponent* _primityive)
{
	
}

void AMainSceneActor::BeforeActiveEvent()
{
	//카메라 이동.
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget() == nullptr) return;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget()->SetActorLocation(UKismetMathLibrary::TransformLocation(GetActorTransform(), targetLocation));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(
		UKismetMathLibrary::TransformLocation(GetActorTransform(), targetLocation),
		UKismetMathLibrary::TransformLocation(GetActorTransform(), targetView)));

	//랜더링
	boxCollision->SetVisibility(true, true);
}

void AMainSceneActor::ActiveEvent()
{

}


void AMainSceneActor::UnActiveEvent()
{
	//랜더링
	boxCollision->SetVisibility(false, true);
}