// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"
#include "Item/Armor.h"
#include "Item/Weapon.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIFEOFMERCENARY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void AddArmorFromItemCode(const FString& _itemCode);
	void AddWeaponFromItemCode(const FString& _itemCode);
	void AddStartItem();
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "InventoryComponent")
		TArray<UItem*> itemArray;

	//개수 추가예정(구조체로 만들 예정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryComponent")
		TArray<FString> startItemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryComponent")
		int32 gold;
};
