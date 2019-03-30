// Fill out your copyright notice in the Description page of Project Settings.

#include "Armor.h"
#include "Functions/LoMFunctions.h"

UArmor::UArmor() : m_defensivePower(0.f)
{

}

void UArmor::SetArmorData(const FArmorEquipmentData& _amorData)
{
	m_name = _amorData.Name;
	m_defensivePower = _amorData.DefensivePower;
	m_solidity = _amorData.Solidity;
	m_durabilty = _amorData.Durability;
	m_weight = _amorData.Weight;
	m_partsType = ULoMFunctions::GetEnumValueFromString<EEquipmentPartsType>("EEquipmentPartsType", _amorData.PartsType);
	m_imageCode = _amorData.ImageCode;
	m_price = _amorData.Price;
	m_meshCode = _amorData.MeshCode;
	//UItem Á¤º¸
	m_itemType = EItemType::ARMOR;
}

FArmorEquipmentData UArmor::GetArmorData()
{
	FArmorEquipmentData armorData;

	armorData.Name = m_name;
	armorData.DefensivePower = m_defensivePower;
	armorData.Solidity = m_solidity;
	armorData.Durability = m_durabilty;
	armorData.Weight = m_weight;
	armorData.PartsType = ULoMFunctions::GetStringFromEnumValue<EEquipmentPartsType>("EEquipmentPartsType", m_partsType);
	armorData.ImageCode = m_imageCode;
	armorData.Price = m_price;
	armorData.MeshCode = m_meshCode;

	return armorData;
}