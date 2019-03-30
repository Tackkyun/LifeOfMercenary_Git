#include "DataTableManager.h"

UDataTableManager::UDataTableManager() : m_armorDataTable(nullptr), m_weaponDataTable(nullptr), m_questDataTable(nullptr)
{
	m_armorDataTable = ULoMFunctions::GetDataTableFromString(TEXT("DataTable'/Game/DataTables/DT_ArmorEquipment.DT_ArmorEquipment'"));
	m_weaponDataTable = ULoMFunctions::GetDataTableFromString(TEXT("DataTable'/Game/DataTables/DT_WeaponEquipment.DT_WeaponEquipment'"));
	m_questDataTable = ULoMFunctions::GetDataTableFromString(TEXT("DataTable'/Game/DataTables/DT_RQ.DT_RQ'"));
}