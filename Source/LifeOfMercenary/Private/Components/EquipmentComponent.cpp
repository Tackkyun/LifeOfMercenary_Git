// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipmentComponent.h"
//#include "Functions/LoMFunctions.h"

UEquipmentComponent::UEquipmentComponent() : m_totalAttackPower(0.f), m_totalDefensivePower(0.f)
{
	for (int32 i = 0; i < (int32)EEquipmentPartsType::MAX_PARTS; i++) {
		parts.Add(nullptr);
	}
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UEquipmentComponent::SetEquipItem(UItem* _item, EEquipmentPartsType _partsType)
{
	parts[(int32)_partsType] = _item;
	UpdateEquipmentPower();
	OnEquipItem.Broadcast(_partsType);
}

void UEquipmentComponent::Disarm(EEquipmentPartsType _partsType)
{
	parts[(int32)_partsType] = nullptr;
	UpdateEquipmentPower();
	OnDisarmItem.Broadcast(_partsType);
}

void UEquipmentComponent::UpdateEquipmentPower()
{
	m_totalDefensivePower = 0;
	m_totalAttackPower = 0;
	for (int32 i = 0; i < (int32)EEquipmentPartsType::MAX_PARTS; i++) {
		if (parts[i] != nullptr) {
			switch (parts[i]->GetItemType()) {
			case EItemType::ARMOR:
				m_totalDefensivePower += Cast<UArmor>(parts[i])->GetDefensivePower();
				break;
			case EItemType::WEAPON:
				m_totalAttackPower += Cast<UWeapon>(parts[i])->GetAttackPower();
				break;
			}
		}
	}
}