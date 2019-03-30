// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainScene/MainSceneActor.h"
#include "GambleBase.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AGambleBase : public AMainSceneActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	//차감될 금액
	void SetPlayerGold(int32 _variationGold);

	UFUNCTION(BlueprintCallable, Category = "GambleBase")
		virtual void InputTouchEnd(ETouchIndex::Type _type, UPrimitiveComponent* _primityive);

	UFUNCTION(BlueprintCallable, Category = "GambleBase")
		void ActiveUI(bool _bBegin);

private:
	//플레이어 소지금
	int32* m_playerGold;

	//판돈 배율
	float m_betMultiplyingFactor;

	UFUNCTION(BlueprintCallable, Category = "GambleBase")
		virtual void BeforeActiveEvent();
	UFUNCTION(BlueprintCallable, Category = "GambleBase")
		virtual void ActiveEvent();
};
