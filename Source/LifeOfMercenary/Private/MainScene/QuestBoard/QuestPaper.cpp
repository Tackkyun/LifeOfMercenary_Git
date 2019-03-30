// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOfMercenary/Public/MainScene/QuestBoard/QuestPaper.h"


// Sets default values
AQuestPaper::AQuestPaper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	paperRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	paperRootComponent->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));
	RootComponent = paperRootComponent;

	paperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaperMesh"));
	paperMesh->AttachToComponent(paperRootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	boxCollision->AttachToComponent(paperRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	boxCollision->SetCollisionProfileName("UI");

	paperWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaperWidget"));
	paperWidget->AttachToComponent(paperRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	paperWidget->SetCollisionProfileName("UI");
}

// Called when the game starts or when spawned
void AQuestPaper::BeginPlay()
{
	Super::BeginPlay();
	
	//위젯 생성
	FStringClassReference myWidgetClassRef(TEXT("/Game/UI/UI_3D_Paper.UI_3D_Paper_C"));
	UDefaultUI* myWidget = CreateWidget<UDefaultUI>(GetWorld()->GetFirstPlayerController(), myWidgetClassRef.TryLoadClass<UDefaultUI>());
	myWidget->parentActor = this;

	paperWidget->SetWidget(myWidget);

	boxCollision->OnInputTouchEnd.AddDynamic(this, &AQuestPaper::TouchEnd);
}

// Called every frame
void AQuestPaper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestPaper::TouchEnd(ETouchIndex::Type _fingerIndex, UPrimitiveComponent* _touchedComponent)
{
	//위젯 생성
	FStringClassReference myWidgetClassRef(TEXT("/Game/UI/UI_QuestPaper.UI_QuestPaper_C"));
	UDefaultUI* myWidget = CreateWidget<UDefaultUI>(GetWorld()->GetFirstPlayerController(), myWidgetClassRef.TryLoadClass<UDefaultUI>());
	myWidget->parentActor = this;
	myWidget->AddToViewport();
}

