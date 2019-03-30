// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSaveGame.h"
#include "Functions/LoMFunctions.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

UPlayerSaveGame::UPlayerSaveGame() : saveSlotName("PlayerSaveSlot"), userIndex(0)
{

}

void UPlayerSaveGame::ResetSaveData()
{
	armor.Empty();
	weapon.Empty();
	gold = 0;
	m_invenotryCount = 0;
}

void UPlayerSaveGame::SetSaveInventory(TArray<UItem*> _inventoryArray)
{
	m_invenotryCount = _inventoryArray.Num();
	for(int i = 0; i < m_invenotryCount ; ++i) {
		if (_inventoryArray[i] != nullptr) {
			if (EItemType::ARMOR == _inventoryArray[i]->GetItemType()) {
				FArmorEquipmentData armorData;
				armorData = Cast<UArmor>(_inventoryArray[i])->GetArmorData();
				armor.Add(i, armorData);
			}
			else if (EItemType::WEAPON == _inventoryArray[i]->GetItemType()) {
				FWeaponEquipmentData weaponData;
				weaponData = Cast<UWeapon>(_inventoryArray[i])->GetWeaponData();
				weapon.Add(i, weaponData);
			}
		}
	}
}

TArray<UItem*> UPlayerSaveGame::GetSaveInventory()
{
	TArray<UItem*> itemArray;

	for (int i = 0; i < m_invenotryCount; ++i) {
		if (armor.Find(i) != nullptr) {
			UArmor* armorData = NewObject<UArmor>();
			armorData->SetArmorData(*armor.Find(i));
			itemArray.Add(Cast<UItem>(armorData));
		}
		else if (weapon.Find(i) != nullptr) {
			UWeapon* weaponData = NewObject<UWeapon>();
			weaponData->SetWeaponData(*weapon.Find(i));
			itemArray.Add(Cast<UItem>(weaponData));
		}
	}

	return itemArray;
}

void UPlayerSaveGame::SetSaveEquipment(TArray<UItem*> _equipmentArray)
{
	for (int i = 0; i < _equipmentArray.Num(); ++i) {
		if (_equipmentArray[i] != nullptr) {
			if (EItemType::ARMOR == _equipmentArray[i]->GetItemType()) {
				FArmorEquipmentData armorData;
				armorData = Cast<UArmor>(_equipmentArray[i])->GetArmorData();
				armor.Add(armor.Num() + weapon.Num(), armorData);
				//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("%s"), *armorData.Name));
			}
			else if (EItemType::WEAPON == _equipmentArray[i]->GetItemType()) {
				FWeaponEquipmentData weaponData;
				weaponData = Cast<UWeapon>(_equipmentArray[i])->GetWeaponData();
				weapon.Add(armor.Num() + weapon.Num(), weaponData);
				//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("%s"), *weaponData.Name));
			}
		}
	}
}

TArray<UItem*> UPlayerSaveGame::GetSaveEquipment()
{
	TArray<UItem*> itemArray;

	for (int i = 0; i < (int)EEquipmentPartsType::MAX_PARTS; ++i) {
		itemArray.Add(nullptr);
	}

	for (int i = m_invenotryCount; i < armor.Num() + weapon.Num(); ++i) {
		if (armor.Find(i) != nullptr) {
			UArmor* armorData = NewObject<UArmor>();
			armorData->SetArmorData(*armor.Find(i));
			itemArray[(int)armorData->GetPartsType()] = armorData;
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("%s"), *armorData->GetName()));
		}
		else if (weapon.Find(i) != nullptr) {
			UWeapon* weaponData = NewObject<UWeapon>();
			weaponData->SetWeaponData(*weapon.Find(i));
			itemArray[(int)weaponData->GetPartsType()] = weaponData;
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("%s"), *weaponData->GetName()));
		}
	}

	return itemArray;
}