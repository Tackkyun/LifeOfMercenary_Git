#pragma once

#include "CoreMinimal.h"
#include "Item/Equipment.h"
#include "Engine/DataTable.h"
#include "Armor.generated.h"


USTRUCT(BlueprintType)
struct FArmorEquipmentData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FArmorEquipmentData() : Name("NONE"), Price(0), DefensivePower(0.f), Solidity(0.f), Durability(0.f),
		Weight(0.f), PartsType("NONE"), Material("NONE"), ImageCode("NONE"), MeshCode("NONE") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		int32 Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float DefensivePower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float Solidity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float Durability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString PartsType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString Material;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString ImageCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
		FString MeshCode;
};
/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UArmor : public UEquipment
{
	GENERATED_BODY()
public:
	UArmor();

	void SetArmorData(const FArmorEquipmentData& _amorData);
	FArmorEquipmentData GetArmorData();

	UFUNCTION(BlueprintCallable, Category = "Armor")
		float GetDefensivePower() { return m_defensivePower; }
	
protected:
	float m_defensivePower;
	
};
