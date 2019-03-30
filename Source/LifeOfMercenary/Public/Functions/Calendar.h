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
		//���� �⵵�� �޾ƿ�.
		static int32 GetYear(int32 _Date);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//���� ���� �޾ƿ�.
		static int32 GetMonth(int32 _Date);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//���� ���� �޾ƿ�.
		static int32 GetDay(int32 _Date);

	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//"-yymmdd"������ FString��¥�� �ϴ����� ��ȯ
		static int32 ConvertFStoi(FString _Date);

	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//��¥�� �ϴ����� ����.
		static bool SetDate(int32& _Date, int32 _Day);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//��¥�� FString���·� ����. "-yymmdd" ����. �ּ� ���� 10101(1�� 1�� 1��). �� �� �� �ִ���� ����.
		static bool SetDateFromFString(int32& _Date, FString _SDate);

	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//���� ��¥���� �ϴ��� �߰�
		static bool AddDay(int32& _Date, int32 _Day);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//���� ��¥���� ������ �߰�
		static bool AddMonth(int32& _Date, int32 _Month);
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//���� ��¥���� ����� �߰�
		static bool AddYear(int32& _Date, int32 _Year);

	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//�Ѵ� �� ������ ��
		static int32 GetMaxDay() { return MaxDay; };
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//�ϳ� �� ������ ��
		static int32 GetMaxMonth() { return MaxMonth; };
	UFUNCTION(BlueprintCallable, Category = "Calendar")
		//������ �⵵
		static int32 GetMaxYear() { return MaxYear; };
	
	
};
