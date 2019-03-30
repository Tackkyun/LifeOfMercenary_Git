// Fill out your copyright notice in the Description page of Project Settings.

#include "Wolf.h"
#include "Runtime/AIModule/Classes/AIController.h"
AWolf::AWolf()
{
	AttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionBox"));
	BodyCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyCollisionBox"));

	AttackCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket_Teeth"));
	BodyCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
}

void AWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWolf::BeginPlay()
{
	Super::BeginPlay();

}