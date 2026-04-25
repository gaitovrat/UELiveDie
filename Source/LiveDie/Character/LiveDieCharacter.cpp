// Fill out your copyright notice in the Description page of Project Settings.

#include "LiveDieCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
ALiveDieCharacter::ALiveDieCharacter(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 300.0f;

	StaticMesh->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	UCharacterMovementComponent *CharacterMovementComponent = GetCharacterMovement();
	check(CharacterMovementComponent != nullptr);
	CharacterMovementComponent->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ALiveDieCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddDynamic(this, &ThisClass::HandleDeath);
}

// Called every frame
void ALiveDieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALiveDieCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent *EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
}

void ALiveDieCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	APlayerController *PC = Cast<APlayerController>(GetController());
	if (!PC)
		return;

	UEnhancedInputLocalPlayerSubsystem *Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	if (!Subsystem || !DefaultMappingContext)
		return;

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void ALiveDieCharacter::Move(const FInputActionValue &Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (!Controller || Axis.IsNearlyZero())
		return;

	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, Axis.Y);
	AddMovementInput(Right, Axis.X);
}

void ALiveDieCharacter::Look(const FInputActionValue &Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void ALiveDieCharacter::HandleDeath()
{
}
