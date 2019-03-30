#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Equipment.generated.h"

UENUM(BlueprintType)
enum class EEquipmentPartsType : uint8
{
	HEAD		UMETA(DisplayName = "HEAD"),
	TOP			UMETA(DisplayName = "TOP"),
	BOTTOMS		UMETA(DisplayName = "BOTTOMS"),
	HAND		UMETA(DisplayName = "HAND"),
	FEET		UMETA(DisplayName = "FEET"),
	ONE			UMETA(DisplayName = "ONE"),
	TWO			UMETA(DisplayName = "TWO"),
	ASSIST		UMETA(DisplayName = "ASSIST"),
	MAX_PARTS	UMETA(DisplayName = "MAX_PARTS")
};

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UEquipment : public UItem
{
	GENERATED_BODY()
public:
	UEquipment();

	UFUNCTION(BlueprintCallable, Category = "Equipment")
		float GetSolidity() { return m_solidity; }

	UFUNCTION(BlueprintCallable, Category = "Equipment")
		float GetDurabilty() { return m_durabilty; }

	UFUNCTION(BlueprintCallable, Category = "Equipment")
		EEquipmentPartsType GetPartsType() { return m_partsType; }
	

protected:
	float m_solidity;		//경도
	float m_durabilty;		//내구도
	EEquipmentPartsType m_partsType;	//장착 파츠 부위
};
