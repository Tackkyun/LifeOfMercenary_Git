// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/Quest/QuestManager.h"
#include "LifeOfMercenary/Public/Functions/Calendar.h"
#include "UObject/ConstructorHelpers.h"
#include "Functions/LoMFunctions.h"
#include "LoMGameInstance.h"
#include "Character/MercenaryCharacter.h"
#include "UObject/Object.h"

UQuestManager::UQuestManager()
{
	ConstructorHelpers::FObjectFinder<UDataTable> ExcelTable_BP(TEXT("DataTable'/Game/DataTables/DT_RQ.DT_RQ'"));
	gameObjectLookupTable = ExcelTable_BP.Object;

	currentQuest = INDEX_NONE;

	SetQuestNum();
}

void UQuestManager::SetQuestNum()
{
	totalQuestNum = 0;

	for (int i = 0; true; i++)
	{
		FQuestData* tempQuestData = gameObjectLookupTable->FindRow<FQuestData>(FName(*(FString("RQ_") + FString::FromInt(i))), FString(""));

		if (tempQuestData->IsEnd)
		{
			totalQuestNum = i + 1;
			break;
		}
	}
}

TArray<int32> UQuestManager::GetQuestByDate(int32 _date, int32 _beforeDate, int32 _afterDate)
{
	TArray<int32> returnCurrentQuestArray;

	for (int32 i = 0; i < totalQuestNum; i++)
	{
		FString tempName = FName(*(FString("RQ_") + FString::FromInt(i))).ToString();
		FQuestData* tempQuestData = gameObjectLookupTable->FindRow<FQuestData>(FName(*(FString("RQ_") + FString::FromInt(i))), FString(""));

		//break조건
		//앞선 날짜
		if (UCalendar::ConvertFStoi(tempQuestData->StartDate) > _date + _afterDate) break;
		//countinue조건
		//지난 날짜
		if (UCalendar::ConvertFStoi(tempQuestData->StartDate) < _date - _beforeDate) continue;
		//완료/진행중 퀘스트
		if (GetComplateQuestArray().Find(i + 1) != INDEX_NONE || i + 1 == currentQuest) continue;

		//반환변수에 추가.
		returnCurrentQuestArray.Add(tempQuestData->Num);
	}

	return returnCurrentQuestArray;
}

bool UQuestManager::AcceptQuest(int32 _num)
{
	//옳지 못한 퀘스트번호라면
	if (_num > totalQuestNum || _num <= 0) return false;

	currentQuest = _num;

	changedQuestList.Broadcast();

	return true;
}

void UQuestManager::DeleteCurrentQuest()
{
	currentQuest = INDEX_NONE;

	changedQuestList.Broadcast();
}

FReward UQuestManager::ComlateQuest(bool _isSuccess)
{
	FReward returnReward;

	if (_isSuccess) {
		returnReward = SuccesQuest();
	}
	else {
		returnReward = FailQuest();
	}

	return returnReward;
}

//퀘스트 성공
FReward UQuestManager::SuccesQuest()
{
	FReward returnReward;

	FQuestData* tempQuestData = gameObjectLookupTable->FindRow<FQuestData>(FName(*(FString("RQ_") + FString::FromInt(currentQuest))), FString(""));

	returnReward.money = tempQuestData->Pay;
	returnReward.fame = tempQuestData->Fame;

	return returnReward;
}

//퀘스트 실패
FReward UQuestManager::FailQuest()
{
	FReward returnReward;

	returnReward.money = 0.0f;
	returnReward.fame = 0.0f;

	return returnReward;
}

bool UQuestManager::UnperformedToCurrent(int32 _num)
{
	//잘못된 번호, 예외처리.
	if (_num >= totalQuestNum || _num < 0 || ComplateQuestArrayHaveNum(_num)) return false;

	currentQuest = _num;

	return true;
}

bool UQuestManager::CurrentToComlate()
{
	complateQuestArray.Add(currentQuest);
	currentQuest = INDEX_NONE;

	return true;
}

bool UQuestManager::ComplateQuestArrayHaveNum(int32 _num)
{
	if (complateQuestArray.Find(_num) == INDEX_NONE) return false;

	return true;
}

FQuestData UQuestManager::GetQuestData(int32 _num)
{
	FQuestData returnQuestData;

	//잘못된 번호
	if (_num >= totalQuestNum || _num < 0) return returnQuestData;

	returnQuestData = *gameObjectLookupTable->FindRow<FQuestData>(FName(*(FString("RQ_") + FString::FromInt(_num))), FString(""));

	return returnQuestData;
}

int32 UQuestManager::GetCurrentQuest()
{
	return currentQuest;
}

TArray<int32> UQuestManager::GetComplateQuestArray()
{
	return complateQuestArray;
}

