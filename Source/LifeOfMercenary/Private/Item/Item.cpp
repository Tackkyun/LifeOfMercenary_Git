// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Item/Armor.h"
#include "Item/Weapon.h"
#include "Item/Equipment.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"

UItem::UItem() : m_name("NONE"), m_imageCode("NONE"), m_weight(0.f), m_meshCode("NONE")
{

}


/*
_path : 파일이 있는 폴더 경로.
*/
UTexture2D* UItem::GetItemTexture2D(FString _path)
{
	if (m_imageCode == "NONE")
		return nullptr;

	FString FullName = _path + m_imageCode + "." + m_imageCode;

	return LoadObject<UTexture2D>(nullptr, *FullName);
}

UArmor* UItem::ToArmor()
{
	return Cast<UArmor>(this);
}

UWeapon* UItem::ToWeapon()
{
	return Cast<UWeapon>(this);
}

UEquipment* UItem::ToEquipment()
{
	return Cast<UEquipment>(this);
}