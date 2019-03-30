#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DataTableManager.h"
#include "LoMGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ULoMGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	ULoMGameInstance();
	UDataTableManager* GetDataTableManager();

private:
	UDataTableManager* m_dataTableManager;
};
