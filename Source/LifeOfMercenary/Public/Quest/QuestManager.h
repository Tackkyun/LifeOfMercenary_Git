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

	//퀘스트 목록이 담긴 데이터 테이블
	UPROPERTY()
		UDataTable* gameObjectLookupTable = nullptr;

private:

	//퀘스트 갯수
	int32 totalQuestNum = 0;
	//현재 퀘스트
	int32 currentQuest = INDEX_NONE;
	//완료 퀘스트 배열
	TArray<int32> complateQuestArray;

public:
	//현재날짜(일단위)로 부터 전후 일의 퀘스트들을 반환
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		TArray<int32> GetQuestByDate(int32 _date, int32 _beforeDate, int32 _afterDate);

	//퀘스트 수락
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		bool AcceptQuest(int32 _num);

	//퀘스트 완료
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		FReward ComlateQuest(bool _isSuccess);

	//해당 번호의 퀘스트 얻어오기. 0번부터 시작.
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		FQuestData GetQuestData(int32 _num);

	//현재 퀘스트 삭제
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		void DeleteCurrentQuest();

	//접근자
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		int32 GetCurrentQuest();

	//완료한 퀘스트 배열
	UFUNCTION(BlueprintCallable, Category = "QuestManager")
		TArray<int32> GetComplateQuestArray();

	//퀘스트 리스트 변화시 호출되는 Delegate
	UPROPERTY(BlueprintCallable, Category = "QuestManager")
		FChangeQuestList changedQuestList;

private:
	//퀘스트 갯수 세팅
	void SetQuestNum();

	//퀘스트 성공
	FReward SuccesQuest();
	//퀘스트 실패
	FReward FailQuest();
	//미수행퀘스트에서 현재퀘스트로
	bool UnperformedToCurrent(int32 _num);
	//현재퀘스트에서 완료퀘스트로
	bool CurrentToComlate();
	//완료 퀘스트 목록에 해당 퀘스트가 있는지 여부
	bool ComplateQuestArrayHaveNum(int32 _num);
	
	
};

