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

	//UI �߰�.
	UFUNCTION(BlueprintCallable, Category = "MainSceneHUD")
		bool AddUI(UUserWidget* _widget, FString _uiName);

	//UI Ȱ��ȭ.
	UFUNCTION(BlueprintCallable, Category = "MainSceneHUD")
		bool DrawUI(FString _uiName);

	//UI ��Ȱ��.
	UFUNCTION(BlueprintCallable, Category = "MainSceneHUD")
		bool EraseUI(FString _uiName);

	//UI �˻�.
	UFUNCTION(BlueprintCallable, Category = "MainSceneHUD")
		UUserWidget* FindUI(FString _uiName);

public:
	UPROPERTY(BlueprintReadWrite, Category = "MainSceneHUD")
		bool bEnable;

private:
	//UI���� â��. �̰��� �ִ� UI�� ��� ����.
	TMap<FString, UUserWidget*> uiAssortment;

	//UI����
	//TArray<UUserWidget*> uiRecord;
	
};
