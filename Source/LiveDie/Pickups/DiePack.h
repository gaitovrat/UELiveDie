// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "DiePack.generated.h"

UCLASS()
class LIVEDIE_API ADiePack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADiePack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent *OverlapSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent *OverlapMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUp")
	float DamageAmount = 25.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent *OverlappedComponent,
		AActor *OtherActor,
		UPrimitiveComponent *OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);
};
