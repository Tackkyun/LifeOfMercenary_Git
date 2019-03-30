#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MainSceneActor.generated.h"

UCLASS()
class LIFEOFMERCENARY_API AMainSceneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMainSceneActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float _deltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MainSceneActor")
		UBoxComponent* boxCollision;

	//Camera Position
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainSceneActor", Meta = (MakeEditWidget = true))
		FVector targetLocation;

	//Camera LookTarget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainSceneActor", Meta = (MakeEditWidget = true))
		FVector targetView;

	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void InputTouchEnd(ETouchIndex::Type _type, UPrimitiveComponent* _primityive);

	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void BeforeActiveEvent();
	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void ActiveEvent();

	UFUNCTION(BlueprintCallable, Category = "MainSceneActor")
		virtual void UnActiveEvent();
};
