// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "HUDManager.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API AHUDManager : public AHUD
{
	GENERATED_BODY()

public:
	AHUDManager();

	//UI 추가.
	UFUNCTION(BlueprintCallable, Category = "MainSceneHUD")
		bool AddUI(UUserWidget* _widget, FString _uiName);

	//UI 활성화.
	UFUNCTION(BlueprintCallable, Category = "MainSceneHUD")
		bool DrawUI(FString _uiName);

	//UI 비활성.
	UFUNCTION(BlueprintCallable, Category = "MainSceneHUD")
		bool EraseUI(FString _uiName);

	//UI 검색.
	UFUNCTION(BlueprintCallable, Category = "MainSceneHUD")
		UUserWidget* FindUI(FString _uiName);

public:
	UPROPERTY(BlueprintReadWrite, Category = "MainSceneHUD")
		bool bEnable;

private:
	//UI모음 창고. 이곳에 있는 UI만 사용 가능.
	TMap<FString, UUserWidget*> uiAssortment;

	//UI순서
	//TArray<UUserWidget*> uiRecord;
	
};
