// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleMercenaryCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Runtime/Engine/Classes/Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ABattleMercenaryCharacter::ABattleMercenaryCharacter() : m_baseTurnRate(45.f), m_baseLookUpRate(45.f),
currentState(EMercenaryStateType::Idle), bActiveRoll(true), bFreeAction(true), bSaveRoll(false), bNextAttack(false),
bSaveBlock(false), bCameraRotEnable(true), damageDirection(0.f, 0.f, 0.f), cameraRotSpeed(10.f)
{
	cameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("cameraSpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	AttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionBox"));

	cameraSpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	camera->AttachToComponent(cameraSpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	AttackCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("rightHand_socket"));

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1000.0f, 0.0f); // ...at this rotation rate

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	cameraSpringArm->bUsePawnControlRotation = true;
	camera->bUsePawnControlRotation = false;
}

void ABattleMercenaryCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABattleMercenaryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (currentState) {
	case EMercenaryStateType::Idle:
		this->GetCharacterMovement()->MaxWalkSpeed = 600;
		//this->GetCharacterMovement()->bOrientRotationToMovement = true;
		break;
	case EMercenaryStateType::Attack:
		PlayAttack();
		break;
	case EMercenaryStateType::Block:
		this->GetCharacterMovement()->MaxWalkSpeed = 150;
		//this->GetCharacterMovement()->bOrientRotationToMovement = false;
		break;
	}
}

void ABattleMercenaryCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ABattleMercenaryCharacter::Rolling);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABattleMercenaryCharacter::Attack); 
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &ABattleMercenaryCharacter::Block);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &ABattleMercenaryCharacter::UnBlock);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABattleMercenaryCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABattleMercenaryCharacter::MoveRight);

	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &ABattleMercenaryCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &ABattleMercenaryCharacter::LookUpAtRate);
}


void ABattleMercenaryCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f)){
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		Value = Value > 0 ? 1 : -1; //중간 속도들을 없애기 위해사용

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

		worldDir = worldDir + Direction * Value;
		worldDir.Normalize();
	}
}

void ABattleMercenaryCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f)){
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		Value = Value > 0 ? 1 : -1; //중간 속도들을 없애기 위해사용

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);

		worldDir = worldDir + Direction * Value;
		worldDir.Normalize();
	}
}

void ABattleMercenaryCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * m_baseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABattleMercenaryCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * m_baseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABattleMercenaryCharacter::Rolling()
{
	if(bActiveRoll){
		PlayRolling();
	}
	else {
		if (currentState == EMercenaryStateType::Attack) {
			bSaveRoll = true;
		}
	}
}

void ABattleMercenaryCharacter::Attack()
{
	if (currentState != EMercenaryStateType::Roll) {
		if (currentState == EMercenaryStateType::Attack) {
			if (bActiveRoll == false) {
				bNextAttack = true;
			}
		}
		currentState = EMercenaryStateType::Attack;
	}
}

void ABattleMercenaryCharacter::Block()
{
	if (currentState != EMercenaryStateType::Roll &&
		currentState != EMercenaryStateType::Attack) {
		SetActorRotation(worldDir.Rotation());
		currentState = EMercenaryStateType::Block;
	}
	else {
		bSaveBlock = true;
	}
}

void ABattleMercenaryCharacter::UnBlock()
{
	if (currentState != EMercenaryStateType::Roll &&
		currentState != EMercenaryStateType::Attack) {
		currentState = EMercenaryStateType::Idle;
	}
	bSaveBlock = false;
}

void ABattleMercenaryCharacter::PlayRolling()
{
	currentState = EMercenaryStateType::Roll;
	SetActorRotation(worldDir.Rotation());
	PlayAnimMontage(LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Characters/Mercenary/Animation/AM_Rolling.AM_Rolling")));
	bActiveRoll = false;
	bFreeAction = true;
}

void ABattleMercenaryCharacter::PlayAttack()
{
	if (bFreeAction) {
		bFreeAction = false;
		UAnimMontage* ableMontage = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Characters/Mercenary/Animation/AM_RAttackEnd.AM_RAttackEnd"));
		if (this->GetCurrentMontage() == ableMontage) {
			PlayAnimMontage(LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Characters/Mercenary/Animation/AM_LAttackStart.AM_LAttackStart")));
		}
		else {
			PlayAnimMontage(LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Characters/Mercenary/Animation/AM_RAttackStart.AM_RAttackStart")));
		}
	}
}

void ABattleMercenaryCharacter::EndAttack()
{
	if(bNextAttack == false){
		currentState = EMercenaryStateType::Idle;
	}

	bFreeAction = true;
	bActiveRoll = true;
	bNextAttack = false;

	if (bSaveBlock) {
		currentState = EMercenaryStateType::Block;
	}
	else {
		if (bSaveRoll) {
			PlayRolling();
			bSaveRoll = false;
		}
	}
}

void ABattleMercenaryCharacter::EndRolling()
{
	bActiveRoll = true;
	currentState = EMercenaryStateType::Idle;

	if (bSaveBlock) {
		currentState = EMercenaryStateType::Block;
	}
}

void ABattleMercenaryCharacter::AttackAutoTarget()
{
	FHitResult hitResult;
	bool bObjectCheck = false;
	FVector targetLocation;

	bObjectCheck = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), this->GetActorLocation(), this->GetActorLocation(), 300,
	{ EObjectTypeQuery::ObjectTypeQuery7 }, false, {}, EDrawDebugTrace::None, hitResult, true);

	//자동 타겟 될 목표의 위치를 구한다.
	if (true == bObjectCheck) {
		targetLocation = hitResult.Actor->GetActorLocation();
	}
	else {
		targetLocation = GetActorForwardVector() + GetActorLocation();
	}

	//플레이어를 타겟의 방향으로 회전시킨다.
	if (true == this->bFreeAction && currentState== EMercenaryStateType::Idle) {
		FVector rotDir = targetLocation - this->GetActorLocation();
		rotDir.Normalize();
		SetActorRotation(FRotator(0.f, rotDir.Rotation().Yaw,0.f));
		
		worldDir = rotDir;
	}
}