// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Functions/LoMFunctions.h"

UWeapon::UWeapon() :m_attackPower(0.f)
{

}

void UWeapon::SetWeaponData(const FWeaponEquipmentData& _weaponData)
{
	m_name = _weaponData.Name;
	m_attackPower = _weaponData.AttackPower;
	m_solidity = _weaponData.Solidity;
	m_durabilty = _weaponData.Durability;
	m_weight = _weaponData.Weight;
	m_partsType = ULoMFunctions::GetEnumValueFromString<EEquipmentPartsType>("EEquipmentPartsType", _weaponData.PartsType);
	m_imageCode = _weaponData.ImageCode;
	m_price = _weaponData.Price;
	m_meshCode = _weaponData.MeshCode;
	m_weaponType = ULoMFunctions::GetEnumValueFromString<EWeaponType>("EWeaponType", _weaponData.WeaponType);
	//UItem Á¤º¸.
	m_itemType = EItemType::WEAPON;
}

FWeaponEquipmentData UWeapon::GetWeaponData()
{
	FWeaponEquipmentData weaponData;

	weaponData.Name = m_name;
	weaponData.AttackPower = m_attackPower;
	weaponData.Solidity = m_solidity;
	weaponData.Durability = m_durabilty;
	weaponData.Weight = m_weight;
	weaponData.PartsType = ULoMFunctions::GetStringFromEnumValue<EEquipmentPartsType>("EEquipmentPartsType", m_partsType);
	weaponData.ImageCode = m_imageCode;
	weaponData.Price = m_price;
	weaponData.MeshCode = m_meshCode;
	weaponData.WeaponType = ULoMFunctions::GetStringFromEnumValue<EWeaponType>("EWeaponType", m_weaponType);

	return weaponData;
}