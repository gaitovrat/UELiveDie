// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPack.h"

#include "../Components/HealthComponent.h"

// Sets default values
AHealthPack::AHealthPack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(FName("OverlapSphere"));
	OverlapMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("OverlapMesh"));

	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);

	RootComponent = OverlapSphere;
	OverlapMesh->SetupAttachment(OverlapSphere);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// ReSharper disable once CppMemberFunctionMayBeConst
// Required by signature of USphereComponent
void AHealthPack::OnOverlap(
	UPrimitiveComponent *OverlappedComponent,
	// ReSharper disable once CppParameterMayBeConstPtrOrRef
	// Required by signature of USphereComponent
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	UHealthComponent *HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health component is null"));
		return;
	}

	HealthComponent->Heal(HealAmount);
}
