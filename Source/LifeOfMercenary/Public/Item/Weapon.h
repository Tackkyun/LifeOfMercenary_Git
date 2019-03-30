#pragma once

#include "CoreMinimal.h"
#include "Item/Equipment.h"
#include "Engine/DataTable.h"
#include "Weapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponEquipmentData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FWeaponEquipmentData() : Name("NONE"), Price(0), AttackPower(0.f), Solidity(0.f), Durability(0.f),
		Weight(0.f), PartsType("NONE"), WeaponType("NONE"), ImageCode("NONE") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		int32 Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float AttackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float Solidity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float Durability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString PartsType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString ImageCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString MeshCode;
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	SWORD		UMETA(DisplayName = "SWORD"),
	SHIELD		UMETA(DisplayName = "SHIELD"),
	SPEAR		UMETA(DisplayName = "SPEAR"),
	AX			UMETA(DisplayName = "AX")
};

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UWeapon : public UEquipment
{
	GENERATED_BODY()

public:
	UWeapon();

	void SetWeaponData(const FWeaponEquipmentData& _weaponData);
	FWeaponEquipmentData GetWeaponData();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetAttackPower() { return m_attackPower; }
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		EWeaponType GetWeaponType() { return m_weaponType; }

private:
	float m_attackPower;
	EWeaponType m_weaponType;
};
