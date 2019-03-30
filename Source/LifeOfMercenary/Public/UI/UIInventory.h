// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/UIInventorySlot.h"
#include "Components/InventoryComponent.h"
#include "Runtime/UMG/Public/Components/UniformGridPanel.h"
#include "Runtime/UMG/Public/Components/UniformGridSlot.h"
#include "Runtime/UMG/Public/Components/SizeBox.h"
#include "UIInventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChoiceSlot, const UItem*, _item);

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UUIInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	UUIInventory(const FObjectInitializer& _objectInitializer);

	virtual void NativeConstruct() override;

protected:
	//인벤토리에 아이템이 들어갈 공간을 만들어준다.
	UFUNCTION(BlueprintCallable, Category = "UIInventory")
		bool AddEmptyInventorySlot(UUniformGridPanel* _panel, int32 _index = 1);

	//인벤토리의 아이템들을 빈 공간이 없도록 정렬시켜준다
	UFUNCTION(BlueprintCallable, Category = "UIInventory")
		void InventorySortNotEmpty(UUniformGridPanel* _pPanel);

public:
	UPROPERTY(BlueprintReadWrite, Category = "UIInventory")
		UUIInventorySlot* choiceSlot;
	UPROPERTY(BlueprintReadWrite, Category = "UIInventory")
		UUIInventorySlot* beforeSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIInventory")
		int32 inventoryWidthSize;
	UPROPERTY(BlueprintReadWrite, Category = "UIInventory", meta = (ExposeOnSpawn = "true"))
		UInventoryComponent* inventoryComponent;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "UIInventory")
		FOnChoiceSlot OnChoiceSlot;
};
