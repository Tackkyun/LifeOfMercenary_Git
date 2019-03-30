#include "LoMGameInstance.h"

ULoMGameInstance::ULoMGameInstance() : m_dataTableManager(nullptr)
{
	m_dataTableManager = UDataTableManager::StaticClass()->GetDefaultObject<UDataTableManager>();
}

UDataTableManager* ULoMGameInstance::GetDataTableManager()
{
	return m_dataTableManager;
}