// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIFEOFMERCENARY_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatusComponent();

	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetHealthPower() { return m_healthPower; };
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetDefensivePower() { return m_defensivePower; };
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetAttackPower() { return m_attackPower; };
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetStaminaPower() { return m_staminaPower; };
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetResistancePower() { return m_resistancePower; };
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetHealthRecuperation() { return m_healthRecuperation; };
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetAttackSpeed() { return m_attackSpeed; };
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetMoveSpeed() { return m_moveSpeed; };
	UFUNCTION(BlueprintCallable, Category = "StatusComponent")
		float GetStaminaRecuperation() { return m_staminaRecuperation; };

protected:
	virtual void BeginPlay() override;

protected:
	//����
	float m_healthPower; 		//ü��
	float m_defensivePower;		//����
	float m_attackPower;		//���ݷ�
	float m_staminaPower;		//���
	float m_resistancePower;	//���׷�
	float m_healthRecuperation;	//ȸ����
	float m_attackSpeed;		//���ݼӵ�
	float m_moveSpeed;			//�̵��ӵ�
	float m_staminaRecuperation;//��� ȸ���ӵ�
};
