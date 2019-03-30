// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "LoMGameInstance.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() : gold(2000)
{

}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	AddStartItem();
}

void UInventoryComponent::AddStartItem()
{
	for (int i = 0; i < startItemCode.Num(); ++i) {
		FString strType = startItemCode[i].Left(2);

		if ("AE" == strType) {
			AddArmorFromItemCode(startItemCode[i]);
		}
		else if ("WE" == strType) {
			AddWeaponFromItemCode(startItemCode[i]);
		}
	}
}

void UInventoryComponent::AddArmorFromItemCode(const FString& _itemCode)
{

	FArmorEquipmentData* AED = Cast<ULoMGameInstance>(GetWorld()->GetGameInstance())->
		GetDataTableManager()->GetArmorDataTable()->FindRow<FArmorEquipmentData>(*_itemCode, FString(""));

	if (AED != nullptr) {
		UArmor* armor = NewObject<UArmor>(this);
		armor->SetArmorData(*AED);
		itemArray.Add(armor);
	}
	else {
		UE_LOG(LogClass, Log, TEXT("UInventoryComponent::AddArmorFromItemCode - None Item Code!! - %s"), *_itemCode);
	}
}

void UInventoryComponent::AddWeaponFromItemCode(const FString& _itemCode)
{
	FWeaponEquipmentData* WED = Cast<ULoMGameInstance>(GetWorld()->GetGameInstance())->
		GetDataTableManager()->GetWeaponDataTable()->FindRow<FWeaponEquipmentData>(*_itemCode, FString(""));

	if (WED != nullptr) {
		UWeapon* weapon = NewObject<UWeapon>(this);
		weapon->SetWeaponData(*WED);
		itemArray.Add(weapon);
	}
	else {
		UE_LOG(LogClass, Log, TEXT("UInventoryComponent::AddWeaponFromItemCode - None Item Code!! - %s"), *_itemCode);
	}
}