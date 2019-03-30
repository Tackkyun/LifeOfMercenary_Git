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
	//스텟
	float m_healthPower; 		//체력
	float m_defensivePower;		//방어력
	float m_attackPower;		//공격력
	float m_staminaPower;		//기력
	float m_resistancePower;	//저항력
	float m_healthRecuperation;	//회복력
	float m_attackSpeed;		//공격속도
	float m_moveSpeed;			//이동속도
	float m_staminaRecuperation;//기력 회복속도
};
