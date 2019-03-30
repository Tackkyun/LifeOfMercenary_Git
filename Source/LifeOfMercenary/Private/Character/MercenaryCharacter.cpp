// Fill out your copyright notice in the Description page of Project Settings.

#include "MercenaryCharacter.h"
#include "LifeOfMercenary/Public/Functions/Calendar.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "HUDManager.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


AMercenaryCharacter::AMercenaryCharacter() : equipment(nullptr), playerStatus(nullptr), playerSaveGame(nullptr)
{
	equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("equipment"));
	playerStatus = CreateDefaultSubobject<UPlayerStatusComponent>(TEXT("playerStatus"));
	playerStatus->equipment = equipment;

	body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("body"));
	hands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("hands"));
	bottoms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("bottoms"));
	feets = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("feets"));
	helmet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("helmet"));
	rightHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("righthand"));
	leftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("leftHand"));

	body->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	hands->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	feets->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	bottoms->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	helmet->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "helmet_socket");
	rightHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "rightHand_socket");
	leftHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "leftHand_socket");

	body->SetMasterPoseComponent(GetMesh());
	hands->SetMasterPoseComponent(GetMesh());
	feets->SetMasterPoseComponent(GetMesh());
	bottoms->SetMasterPoseComponent(GetMesh());
}

void AMercenaryCharacter::PostInitProperties()
{
	Super::PostInitProperties();
	//SaveGame Instance생성
	playerSaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));

	//데이터 불러오기.
	LoadData();
	
	//날짜 세팅
	date = UCalendar::ConvertFStoi("11015");

	questManager = NewObject<UQuestManager>(this);
	currentQuest = INDEX_NONE;
}

void AMercenaryCharacter::BeginPlay()
{
	Super::BeginPlay();

	//장비 아이템 장착 시 호출
	equipment->OnEquipItem.AddDynamic(this, &AMercenaryCharacter::OnEquipItem);
	//장비 아이템 해제 시 호출
	equipment->OnDisarmItem.AddDynamic(this, &AMercenaryCharacter::OnDisarmItem);

	for (int i = 0; i < (int)EEquipmentPartsType::MAX_PARTS; i++) {
		OnEquipItem_Implementation((EEquipmentPartsType)i);
	}
}

void AMercenaryCharacter::OnEquipItem_Implementation(EEquipmentPartsType _type)
{
	UItem* item = equipment->parts[(int32)_type];

	if (item != nullptr) {
		FString stringPath = "/Game/Resources/Item/Meshes/"
			+ item->GetMeshCode() + "." + item->GetMeshCode();

		switch (_type) {
		case EEquipmentPartsType::HEAD:
			helmet->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *stringPath));
			break;
		case EEquipmentPartsType::TOP:
			body->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *stringPath));
			break;
		case EEquipmentPartsType::BOTTOMS:
			bottoms->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *stringPath));
			break;
		case EEquipmentPartsType::HAND:
			hands->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *stringPath));
			break;
		case EEquipmentPartsType::FEET:
			feets->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *stringPath));
			break;
		case EEquipmentPartsType::ONE:
			rightHand->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *stringPath));
			break;
		case EEquipmentPartsType::TWO:
			rightHand->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *stringPath));
			break;
		case EEquipmentPartsType::ASSIST:
			if (item->ToWeapon()->GetWeaponType() == EWeaponType::SHIELD) {
				leftHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "shield_socket");
			}
			else {
				leftHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "leftHand_socket");
			}
			leftHand->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *stringPath));
			break;
		}
	}
}

void AMercenaryCharacter::OnDisarmItem_Implementation(EEquipmentPartsType _type)
{
	UItem* item = equipment->parts[(int32)_type];

	switch (_type) {
	case EEquipmentPartsType::HEAD:
		helmet->SetStaticMesh(nullptr);
		break;
	case EEquipmentPartsType::TOP:
		body->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr,
			TEXT("/Game/Characters/Mercenary/SkeletalMeshes/SK_Top.SK_Top")));
		break;
	case EEquipmentPartsType::BOTTOMS:
		bottoms->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr,
			TEXT("/Game/Characters/Mercenary/SkeletalMeshes/SK_Bottoms.SK_Bottoms")));
		break;
	case EEquipmentPartsType::HAND:
		hands->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr,
			TEXT("/Game/Characters/Mercenary/SkeletalMeshes/SK_Hands.SK_Hands")));
		break;
	case EEquipmentPartsType::FEET:
		feets->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr,
			TEXT("/Game/Characters/Mercenary/SkeletalMeshes/SK_Feet.SK_Feet")));
		break;
	case EEquipmentPartsType::ONE:
		rightHand->SetStaticMesh(nullptr);
		break;
	case EEquipmentPartsType::TWO:
		rightHand->SetStaticMesh(nullptr);
		break;
	case EEquipmentPartsType::ASSIST:
		leftHand->SetStaticMesh(nullptr);
		break;
	}
}

void AMercenaryCharacter::SaveData()
{
	playerSaveGame->ResetSaveData();
	playerSaveGame->gold = inventory->gold;
	playerSaveGame->SetSaveInventory(inventory->itemArray);
	playerSaveGame->SetSaveEquipment(equipment->parts);

	UGameplayStatics::SaveGameToSlot(playerSaveGame, playerSaveGame->saveSlotName, playerSaveGame->userIndex);
}

void AMercenaryCharacter::LoadData()
{
 	if (UGameplayStatics::DoesSaveGameExist(playerSaveGame->saveSlotName, playerSaveGame->userIndex)) {
		//Slot이 존재한다면 불러온다.
		inventory->startItemCode.Empty();

		playerSaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(playerSaveGame->saveSlotName, playerSaveGame->userIndex));
		inventory->gold = playerSaveGame->gold;
		inventory->itemArray = playerSaveGame->GetSaveInventory();
		equipment->parts = playerSaveGame->GetSaveEquipment();
	}
}
