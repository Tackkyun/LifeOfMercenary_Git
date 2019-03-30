// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDManager.h"

AHUDManager::AHUDManager() : bEnable(true)
{

}

bool AHUDManager::AddUI(UUserWidget* _widget, FString _uiName)
{
	if (_widget == nullptr) return false;
	_widget->SetVisibility(ESlateVisibility::Hidden);
	uiAssortment.Add(_uiName, _widget);

	return true;
}

bool AHUDManager::DrawUI(FString _uiName)
{
	if (uiAssortment.Find(_uiName) == nullptr) return false;

	//if (false == bEnable)	return false;

	bEnable = false;

	(*uiAssortment.Find(_uiName))->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	return true;
}

bool AHUDManager::EraseUI(FString _uiName)
{
	if (uiAssortment.Find(_uiName) == nullptr) return false;

	bEnable = true;

	(*uiAssortment.Find(_uiName))->SetVisibility(ESlateVisibility::Hidden);
	return true;
}

UUserWidget* AHUDManager::FindUI(FString _uiName)
{
	return *uiAssortment.Find(_uiName);
}