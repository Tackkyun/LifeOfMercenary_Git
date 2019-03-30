// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MercenaryCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Curves/CurveVector.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "BattleMercenaryCharacter.generated.h"

UENUM(BlueprintType)
enum class EMercenaryStateType : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Roll		UMETA(DisplayName = "Roll"),
	Attack		UMETA(DisplayName = "Attack"),
	Block		UMETA(DisplayName = "Block"),
	Damage		UMETA(DisplayName = "Damage"),
};

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ABattleMercenaryCharacter : public AMercenaryCharacter
{
	GENERATED_BODY()
public:
	ABattleMercenaryCharacter();

	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void PlayRolling();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void PlayAttack();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void EndAttack();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void EndRolling();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void AttackAutoTarget();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void Rolling();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void Attack();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void Block();
	UFUNCTION(BlueprintCallable, Category = "BattleMercenaryCharacter")
		void UnBlock();

public:
	UPROPERTY(VisibleAnywhere, Category = "BattleMercenaryCharacter")
		USpringArmComponent* cameraSpringArm;
	UPROPERTY(VisibleAnywhere, Category = "BattleMercenaryCharacter")
		UBoxComponent* AttackCollisionBox;
	UPROPERTY(VisibleAnywhere, Category = "BattleMercenaryCharacter")
		UCameraComponent* camera;
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		EMercenaryStateType currentState;
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		FVector worldDir;
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		FVector damageDirection;  //�÷��̾ ���� ����.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		float OrgTouchXPoint;  //ó�� ��ġ�� ȭ����ǥX�� ��ġ.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		float cameraRotSpeed;  //ī�޶� ȸ�� �ӵ�.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bActiveRoll; //Ȱ��ȭ �ÿ��� ȸ�� ����
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bFreeAction; //���ݵ��߿� ������ Ʋ�� ���ֱ� ���ؼ�.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bSaveRoll;   //���� ���߿� �����ٸ� ������ ���� �� �������� ���ֱ� ���ؼ�.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bSaveBlock;  //�����̳� ȸ�� ���߿� ���и� ��ٸ� �ൿ�� ���� �Ŀ� ���и� ��� ���ֱ� ���ؼ�.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bNextAttack; //���� ������ �����ٸ� ���� ������ ���ؼ�.
	UPROPERTY(BlueprintReadWrite, Category = "BattleMercenaryCharacter")
		bool bCameraRotEnable; //ī�޶� ȸ�� Ȱ��ȭ ����.

private:
	float m_baseTurnRate;
	float m_baseLookUpRate;
};