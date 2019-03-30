// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "Camera/MainSceneCamera.h"
#include "MainScene/GameMode/HUDManager.h"
#include "LoMFunctions.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ULoMFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//Enum�̸��� ���� ��ġ�ϴ� ���� ��ȯ���ش�.
	template <typename EnumType>
	static FORCEINLINE EnumType GetEnumValueFromString(const FString& _enumName, const FString& _string)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *_enumName, true);
		if (!enumPtr)
		{
			return EnumType(-1);
		}
		return (EnumType)enumPtr->GetIndexByName(FName(*_string));
	}

	template <typename EnumType>
	static FORCEINLINE FString GetStringFromEnumValue(FString _typeName, EnumType _enumValue)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *_typeName, true);
		if (!enumPtr) {
			return FString("Invalid");
		}
		return enumPtr->GetNameByValue((int64)_enumValue).ToString();
	}


	//���ڿ��� �ش��ϴ� ���������̺��� �ҷ����ش�.
	UFUNCTION(BlueprintCallable, Category = "LoMFunctions")
		static UDataTable* GetDataTableFromString(const FString& _dataTablePath);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "_world"), Category = "LoMFunctions")
		static AMainSceneCamera* GetMainSceneCamera(const UObject* _world);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "_world"), Category = "LoMFunctions")
		static AHUDManager* GetHUDManager(const UObject* _world);
};
