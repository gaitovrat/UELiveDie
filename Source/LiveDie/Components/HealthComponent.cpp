// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::ApplyDamage(float Amount)
{
	if (bIsDead)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't apply damage to a dead actor"));
		return;
	}

	CurrentHealth -= Amount;
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0.f)
	{
		Kill();
	}
}

void UHealthComponent::Heal(float Amount)
{
	if (bIsDead)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't heal a dead actor"));
		return;
	}

	CurrentHealth += Amount;
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void UHealthComponent::Kill()
{
	if (bIsDead)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor is already dead"));
		return;
	}

	CurrentHealth = 0.f;
	bIsDead = true;
	OnDeath.Broadcast();
}

float UHealthComponent::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

bool UHealthComponent::IsDead() const
{
	return bIsDead;
}
