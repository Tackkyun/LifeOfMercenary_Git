// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStatusComponent.h"

UPlayerStatusComponent::UPlayerStatusComponent() : m_strength(20.f), m_endurance(20.f), m_mentalStrength(20.f),
m_stress(0.f), m_fame(0.f), m_maxWeight(0.f)
{

}

void UPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateStatus();
}

void UPlayerStatusComponent::UpdateStatus()
{
	m_healthPower = m_endurance * 100.f;
	m_defensivePower = equipment->GetTotalDefensivePower();	//방어력
	m_attackPower = m_strength + equipment->GetTotalWeaponPower();	//공격력
	m_staminaPower = m_endurance * 9.f;	//기력
	m_resistancePower = (m_endurance*0.01f) + (m_mentalStrength*0.01f);//저항력
	m_healthRecuperation = m_healthPower*0.01f;	//회복력
	m_attackSpeed = 1.f;	//공격속도
	m_moveSpeed = 1.f;		//이동속도
	m_staminaRecuperation = m_endurance + (m_mentalStrength*0.1f);//기력 회복속도
}