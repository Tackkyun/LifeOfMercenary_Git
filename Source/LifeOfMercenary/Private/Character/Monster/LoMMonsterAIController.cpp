// Fill out your copyright notice in the Description page of Project Settings.

#include "LoMMonsterAIController.h"


ALoMMonsterAIController::ALoMMonsterAIController()
{

}

void ALoMMonsterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALoMMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

}

FVector ALoMMonsterAIController::MoveTarget(FVector _vTarget, float _fRotSpeed, float _fStopDist/*= 200.f*/)
{
	//타겟 위치로 회전하며 이동.
	
	FVector vResult = GetPawn()->GetActorForwardVector() * 250 + GetPawn()->GetActorLocation();
	FVector vDir = _vTarget - GetPawn()->GetActorLocation();

	float fDist = 0.f;
	vDir.ToDirectionAndLength(vDir, fDist);

	vResult += vDir * _fRotSpeed;

	if (fDist <= _fStopDist) {
		return GetPawn()->GetActorLocation();
	}

	return vResult;
}

FVector ALoMMonsterAIController::TwoCircleNodeVector(FVector _vOne, float _fOneRadius, FVector _vTwo, float _fTwoRadius, bool bElse /*= true*/)
{

	FVector vResult(0, 0, _vOne.Z);
	float fXDist = _vTwo.X - _vOne.X;
	float fYDist = _vTwo.Y - _vOne.Y;
	float fCircleDist = sqrt(fXDist*fXDist + fYDist*fYDist);
	float k = (fCircleDist*fCircleDist + _fOneRadius*_fOneRadius - _fTwoRadius*_fTwoRadius) / (2 * fCircleDist);
	float a = sqrt(_fOneRadius*_fOneRadius - k*k);

	//bElse의 여부에 따라 반환해주는 점을 변경.
	if (bElse) {
		vResult.X = _vOne.X + (fXDist*k) / fCircleDist + (fYDist / fCircleDist) * a;
		vResult.Y = _vOne.Y + (fYDist*k) / fCircleDist - (fXDist / fCircleDist) * a;
	}
	else {
		vResult.X = _vOne.X + (fXDist*k) / fCircleDist - (fYDist / fCircleDist) * a;
		vResult.Y = _vOne.Y + (fYDist*k) / fCircleDist + (fXDist / fCircleDist) * a;
	}

	return vResult;
}