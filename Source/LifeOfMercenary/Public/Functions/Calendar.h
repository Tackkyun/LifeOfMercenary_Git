// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Calendar.generated.h"

#define MaxDay 30
#define MaxMonth 12
#define MaxYear 214747

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UCalendar : public UObject
{
	GENERATED_BODY()
	
public:
	UCalendar() {};
	~UCalendar() {};

public:

	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//현재 년도를 받아옴.
		static int32 GetYear(int32 _Date);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//현재 월을 받아옴.
		static int32 GetMonth(int32 _Date);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//현재 일을 받아옴.
		static int32 GetDay(int32 _Date);

	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//"-yymmdd"형식의 FString날짜를 일단위로 변환
		static int32 ConvertFStoi(FString _Date);

	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//날짜를 일단위로 세팅.
		static bool SetDate(int32& _Date, int32 _Day);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//날짜를 FString형태로 세팅. "-yymmdd" 순서. 최소 단위 10101(1년 1월 1일). 년 월 일 최대단위 존재.
		static bool SetDateFromFString(int32& _Date, FString _SDate);

	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//현재 날짜에서 일단위 추가
		static bool AddDay(int32& _Date, int32 _Day);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//현재 날짜에서 월단위 추가
		static bool AddMonth(int32& _Date, int32 _Month);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//현재 날짜에서 년단위 추가
		static bool AddYear(int32& _Date, int32 _Year);

	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//한달 중 마지막 일
		static int32 GetMaxDay() { return MaxDay; };
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//일년 중 마지막 달
		static int32 GetMaxMonth() { return MaxMonth; };
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//최후의 년도
		static int32 GetMaxYear() { return MaxYear; };
};
