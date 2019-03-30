// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/Item.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "UIInventorySlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTouchSlot, UUIInventorySlot*, _slot);
/**
 * 
*/
UCLASS()
class LIFEOFMERCENARY_API UUIInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UUIInventorySlot(const FObjectInitializer& _objectInitializer);

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& _inGeometry, const FPointerEvent& _inMouseEvent);

	UFUNCTION(BlueprintCallable, Category = "UIInventorySlot")
		void SetItem(UItem* _item);

	UFUNCTION(BlueprintCallable, Category = "UIInventorySlot")
		void UnableSlot();

public:
	UPROPERTY(BlueprintReadWrite, Category = "UIInventorySlot")
		UTexture2D* textureBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIInventorySlot")
		UTexture2D* textureBeforeBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIInventorySlot")
		UTexture2D* textureAfterTouchBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIInventorySlot")
		UTexture2D* textureItem;

	UPROPERTY(BlueprintReadWrite, Category = "UIInventorySlot")
		bool bChoice;

	UPROPERTY(BlueprintReadWrite, Category = "UIInventorySlot", meta = (ExposeOnSpawn = "true"))
		UItem* item;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "UIInventorySlot")
		FOnTouchSlot OnTouchSlot;
};