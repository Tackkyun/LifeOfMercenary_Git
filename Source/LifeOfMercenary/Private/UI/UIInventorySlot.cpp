// Fill out your copyright notice in the Description page of Project Settings.

#include "UIInventorySlot.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

UUIInventorySlot::UUIInventorySlot(const FObjectInitializer& _objectInitializer)
	: Super(_objectInitializer), textureBackground(nullptr), textureItem(nullptr), bChoice(false), item(nullptr)
{

}

void UUIInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	textureBackground = textureBeforeBackground;

	SetItem(item);
}

FReply UUIInventorySlot::NativeOnMouseButtonUp(const FGeometry& _inGeometry, const FPointerEvent& _inMouseEvent)
{
	bChoice = true;

	textureBackground = textureAfterTouchBackground;

	OnTouchSlot.Broadcast(this);
	return FReply::Handled();
}

void UUIInventorySlot::SetItem(UItem* _item)
{
	item = _item;
	if (nullptr != item) {
		textureItem = item->GetItemTexture2D("/Game/Resources/Item/Textures/");
	}
	else {
		textureItem = textureBeforeBackground;
	}
}

void UUIInventorySlot::UnableSlot()
{
	bChoice = false;
	textureBackground = textureBeforeBackground;
		/*LoadObject<UTexture2D>
		(nullptr, TEXT("Texture2D'/Game/Resources/UI/Textures/T_NotSlotChoice.T_NotSlotChoice'"));*/
}