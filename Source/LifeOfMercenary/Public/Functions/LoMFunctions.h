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
	//Enum이름을 얻어와 일치하는 값를 반환해준다.
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


	//문자열에 해당하는 데이터테이블을 불러와준다.
	UFUNCTION(BlueprintCallable, Category = "LoMFunctions")
		static UDataTable* GetDataTableFromString(const FString& _dataTablePath);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "_world"), Category = "LoMFunctions")
		static AMainSceneCamera* GetMainSceneCamera(const UObject* _world);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "_world"), Category = "LoMFunctions")
		static AHUDManager* GetHUDManager(const UObject* _world);
};
