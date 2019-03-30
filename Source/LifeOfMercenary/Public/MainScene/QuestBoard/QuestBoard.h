// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LifeOfMercenary/Public/MainScene/MainSceneActor.h"
#include "LifeOfMercenary/Public/Quest/QuestManager.h"
#include "LifeOfMercenary/Public/MainScene/QuestBoard/QuestPaper.h"
#include "QuestBoard.generated.h"

#define MaxPaperSlot 6

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActiveQuestBoardDelegate);

/**
*
*/
UCLASS()
class LIFEOFMERCENARY_API AQuestBoard : public AMainSceneActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
public:
	//���� Board�� �����ִ� Quest�迭
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board", Meta = (MakeEditWidget = true))
		TArray<FQuestData> requestDataArray;

	//������ Paper�� ��ġ �迭
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board", Meta = (MakeEditWidget = true))
		TArray<FTransform> paperPos;

	//���� Ȱ��ȭ Delegate
	UPROPERTY(BlueprintCallable, BlueprintReadWrite, Category = "Board")
		FActiveQuestBoardDelegate ActiveQuestBoard;

public:
	UFUNCTION(BlueprintCallable, Category = "Board")
		bool SetPaperObjectonBoard(FString _PaperClassPath, bool _paperActive);

	UFUNCTION(BlueprintCallable, Category = "Board")
		void ActiveBoard();

	UFUNCTION(BlueprintCallable, Category = "Board")
		void ActiveUI(bool _bBegin);

	UFUNCTION(BlueprintCallable, Category = "Board")
		void RefreshPaper();

private:
	//RequestManager�κ��� ���� ����Ʈ�� ����.
	UFUNCTION(BlueprintCallable, Category = "Board")
		TArray<FQuestData> GetQuest();

	TArray<AQuestPaper*> papers;

protected:
	UFUNCTION(BlueprintCallable, Category = "Board")
		void TouchEnd(ETouchIndex::Type _fingerIndex, UPrimitiveComponent* _touchedComponent);

	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void BeforeActiveEvent();
	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void ActiveEvent();

public:
	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void UnActiveEvent();
};

