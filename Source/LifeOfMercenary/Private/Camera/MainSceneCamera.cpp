// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/Camera/MainSceneCamera.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Kismet/KismetMathLibrary.h"

AMainSceneCamera::AMainSceneCamera() : moveTime(1.f), m_tick(0.f), m_bBegin(true)
{
	m_beginPos = FVector::ZeroVector;
	m_beginLookPos = FVector::ZeroVector;
	m_pastPos = FVector::ZeroVector;
	m_pastLookPos = FVector::ZeroVector;
	m_targetPos = FVector::ZeroVector;
	m_targetLookPos = FVector::ZeroVector;
}

void AMainSceneCamera::BeginPlay()
{
	Super::BeginPlay();

	m_beginTransform = GetActorTransform();

	m_beginPos = GetActorLocation();
	m_beginLookPos = GetActorLocation() + (GetActorForwardVector() * 10);
	SetActorTickEnabled(false);//InActive Tick
}

void AMainSceneCamera::Tick(float _deltaSeconds)
{
	Super::Tick(_deltaSeconds);

	MoveFunc(_deltaSeconds);
}

bool AMainSceneCamera::CameraMoveTo(FVector _gotoPos, FVector _lookPos)
{
	if (IsActorTickEnabled()) return false;

	m_pastPos = GetActorLocation();
	m_pastLookPos = GetActorLocation() + (GetActorForwardVector() * 10);
	m_targetPos = _gotoPos;
	m_targetLookPos = _lookPos;

	m_tick = 0.0f;

	SetActorTickEnabled(true); //Active Tick
	m_bBegin = false;

	cameraMoveEnter.Broadcast();

	return true;
}

bool AMainSceneCamera::CameraMoveBegin()
{
	if (IsActorTickEnabled()) return false;

	m_pastPos = GetActorLocation();
	m_pastLookPos = GetActorLocation() + (GetActorForwardVector() * 10);
	m_targetPos = m_beginPos;
	m_targetLookPos = m_beginLookPos;

	m_tick = 0.0f;

	SetActorTickEnabled(true); //Active Tick
	m_bBegin = true;

	cameraMoveEnter.Broadcast();

	return true;
}

void AMainSceneCamera::MoveFunc(float _deltaSeconds)
{
	m_tick += (_deltaSeconds / moveTime);

	//그래프 형태로 이동/회전
	SetActorLocation(UKismetMathLibrary::VEase(m_pastPos, m_targetPos, m_tick, EEasingFunc::EaseOut));
	SetActorRotation(UKismetMathLibrary::REase(
		FRotationMatrix::MakeFromX((m_pastLookPos - m_pastPos)).Rotator(),
		FRotationMatrix::MakeFromX((m_targetLookPos - m_targetPos)).Rotator(),
		m_tick, true, EEasingFunc::EaseOut));

	if (m_tick >= 1.0f) {
		SetActorTickEnabled(false);//Active Tick
		cameraMoveExit.Broadcast(m_bBegin);
		if (m_bBegin) {
			cameraMoveExit.Clear(); //delegate에 연결된 함수를 모두 끊음.
		}
	}
}

void AMainSceneCamera::TransformBegin()
{
	SetActorTransform(m_beginTransform);
}