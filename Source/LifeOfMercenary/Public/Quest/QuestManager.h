// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h" // FTableRowBase
#include "QuestManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeQuestList);

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FQuestData() : Num(0), Title("NONE"), Client("NONE"), StartDate("NONE"), EndDate("NONE"),
		Pay(0), Fame(0), Deposit(0), IsEnd(true), DetailStory("NONE") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		int32 Num;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		FString Client;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		FString StartDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		FString EndDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		int32 Pay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		int32 Fame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		int32 Deposit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		bool IsEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_RQ")
		FString DetailStory;
};

USTRUCT(BlueprintType)
struct FReward
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Reword")
		float money;
	UPROPERTY(BlueprintReadWrite, Category = "Reword")
		float fame;
};

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UQuestManager : public UObject
{
	GENERATED_BODY()
	
public:
	UQuestManager();
	~UQuestManager() {};

	//����Ʈ ����� ��� ������ ���̺�
	UPROPERTY()
		UDataTable* gameObjectLookupTable = nullptr;

private:

	//����Ʈ ����
	int32 totalQuestNum = 0;
	//���� ����Ʈ
	int32 currentQuest = INDEX_NONE;
	//�Ϸ� ����Ʈ �迭
	TArray<int32> complateQuestArray;

public:
	//���糯¥(�ϴ���)�� ���� ���� ���� ����Ʈ���� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		TArray<int32> GetQuestByDate(int32 _date, int32 _beforeDate, int32 _afterDate);

	//����Ʈ ����
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		bool AcceptQuest(int32 _num);

	//����Ʈ �Ϸ�
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		FReward ComlateQuest(bool _isSuccess);

	//�ش� ��ȣ�� ����Ʈ ������. 0������ ����.
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		FQuestData GetQuestData(int32 _num);

	//���� ����Ʈ ����
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		void DeleteCurrentQuest();

	//������
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		int32 GetCurrentQuest();

	//�Ϸ��� ����Ʈ �迭
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		TArray<int32> GetComplateQuestArray();

	//����Ʈ ����Ʈ ��ȭ�� ȣ��Ǵ� Delegate
	UPROPERTY(BlueprintCallable, Category = "QuestManager")
		FChangeQuestList changedQuestList;

private:
	//����Ʈ ���� ����
	void SetQuestNum();

	//����Ʈ ����
	FReward SuccesQuest();
	//����Ʈ ����
	FReward FailQuest();
	//�̼�������Ʈ���� ��������Ʈ��
	bool UnperformedToCurrent(int32 _num);
	//��������Ʈ���� �Ϸ�����Ʈ��
	bool CurrentToComlate();
	//�Ϸ� ����Ʈ ��Ͽ� �ش� ����Ʈ�� �ִ��� ����
	bool ComplateQuestArrayHaveNum(int32 _num);
	
	
};

