// Fill out your copyright notice in the Description page of Project Settings.

#include "UIInventory.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UUIInventory::UUIInventory(const FObjectInitializer& _objectInitializer) : Super(_objectInitializer), choiceSlot(nullptr),
beforeSlot(nullptr), inventoryWidthSize(4), inventoryComponent(nullptr)
{

}

void UUIInventory::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UUIInventory::AddEmptyInventorySlot(UUniformGridPanel* _panel, int32 _index/* = 1*/)
{
	//가로크기가 정해져 있지 않다면 리턴.
	if (inventoryWidthSize == 0) {
		UE_LOG(LogClass, Warning, TEXT("UUMGInventory::AddEmptyInventorySlot - None 'InventoryWidthSize'"));
		return false;
	}

	for (int i = 0; i < _index; ++i) {
		//아이템 공간(Sizebox) 생성 및 추가.
		USizeBox* pTempSizeBox = NewObject<USizeBox>(USizeBox::StaticClass());
		_panel->AddChild(pTempSizeBox);

		//추가된 아이템 공간의 위치 구하기.
		int32 row = (_panel->GetChildrenCount() - 1) / inventoryWidthSize;
		int32 column = (_panel->GetChildrenCount() - 1) % inventoryWidthSize;

		//아이템 공간의 위치 설정.
		UUniformGridSlot* pSizeboxGridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(pTempSizeBox);
		pSizeboxGridSlot->SetRow(row);
		pSizeboxGridSlot->SetColumn(column);
	}

	return true;
}

void UUIInventory::InventorySortNotEmpty(UUniformGridPanel* _pPanel)
{
	for (int i = 0; i < _pPanel->GetChildrenCount(); ++i) {
		//추가된 아이템 공간의 위치 구하기.
		int32 row = i / inventoryWidthSize;
		int32 column = i % inventoryWidthSize;

		UUniformGridSlot* pSizeboxGridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(_pPanel->GetChildAt(i));
		pSizeboxGridSlot->SetRow(row);
		pSizeboxGridSlot->SetColumn(column);
	}
}