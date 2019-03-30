// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatusComponent.h"
#include "Components/EquipmentComponent.h"
#include "PlayerStatusComponent.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UPlayerStatusComponent : public UStatusComponent
{
	GENERATED_BODY()

public:
	UPlayerStatusComponent();

	UFUNCTION(BlueprintCallable, Category = "PlayerStatusComponent")
		void UpdateStatus();

	UFUNCTION(BlueprintCallable, Category = "PlayerStatusComponent")
		float GetStrength() { return m_strength; };
	UFUNCTION(BlueprintCallable, Category = "PlayerStatusComponent")
		float GetEndurance() { return m_endurance; };
	UFUNCTION(BlueprintCallable, Category = "PlayerStatusComponent")
		float GetMentalStrength() { return m_mentalStrength; };
	UFUNCTION(BlueprintCallable, Category = "PlayerStatusComponent")
		float GetStress() { return m_stress; };
	UFUNCTION(BlueprintCallable, Category = "PlayerStatusComponent")
		float GetFame() { return m_fame; };
	UFUNCTION(BlueprintCallable, Category = "PlayerStatusComponent")
		float GetMaxWeight() { return m_maxWeight; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UMGInventory)
		UEquipmentComponent* equipment;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//메인 스텟
	float m_strength;		//근력
	float m_endurance;		//지구력
	float m_mentalStrength;	//정신력

	float m_stress;			//스트레스
	float m_fame;			//명성
	float m_maxWeight;		//무게
};
