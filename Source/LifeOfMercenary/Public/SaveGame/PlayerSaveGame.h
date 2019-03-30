// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Item/Item.h"
#include "Item/Armor.h"
#include "Item/Weapon.h"
#include "PlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPlayerSaveGame();

	/*
	####저장 순서 주의####
	Inventory저장 후
	Equipment를 저장해야 한다.
	*/
	void SetSaveEquipment(TArray<UItem*> _equipmentArray);
	TArray<UItem*> GetSaveEquipment();
	void SetSaveInventory(TArray<UItem*> _inventoryArray);
	TArray<UItem*> GetSaveInventory();
	void ResetSaveData();

public:
	UPROPERTY(BlueprintReadWrite, Category = Equipment)
		TMap<int32, FArmorEquipmentData> armor; 

	UPROPERTY(BlueprintReadWrite, Category = Equipment)
		TMap<int32, FWeaponEquipmentData> weapon;

	UPROPERTY(BlueprintReadWrite, Category = Equipment)
		int32 gold;

	UPROPERTY(BlueprintReadWrite, Category = Equipment)
		int32 m_invenotryCount; //인벤토리 아이템 개수

	UPROPERTY(BlueprintReadWrite, Category = PlayerSaveGame)
		FString saveSlotName;

	UPROPERTY(BlueprintReadWrite, Category = PlayerSaveGame)
		int32 userIndex;


};
