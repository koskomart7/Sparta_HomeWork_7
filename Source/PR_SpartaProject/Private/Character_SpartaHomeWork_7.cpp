// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_SpartaHomeWork_7.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


class ASpartaPlayerController;
// Sets default values
ACharacter_SpartaHomeWork_7::ACharacter_SpartaHomeWork_7()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	CapsuleComponent->SetCapsuleHalfHeight(90.0f);
	CapsuleComponent->SetCapsuleRadius(40.0f);
	CapsuleComponent->SetCollisionProfileName("Pawn");

	CapsuleComponent->SetSimulatePhysics(false);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	SkeletalMeshComponent->SetSimulatePhysics(false);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void ACharacter_SpartaHomeWork_7::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacter_SpartaHomeWork_7::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ACharacter_SpartaHomeWork_7::Move(const FInputActionValue& value)
{
	if (!Controller) return;
	const FVector2D MoveInput = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Get forward and right vectors based on actor's current rotation
		FVector ForwardDirection = GetActorForwardVector();
		FVector RightDirection = GetActorRightVector();

		// Move the pawn
		FVector Movement = (ForwardDirection * MoveInput.X) + (RightDirection * MoveInput.Y);
		AddActorLocalOffset(Movement * 300.0f * GetWorld()->GetDeltaSeconds(), true);
	}
}

void ACharacter_SpartaHomeWork_7::Look(const FInputActionValue& value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Calculate rotation based on mouse input
		float MouseSensitivity = 2.0f;
        
		// Update current rotation values
		CurrentYaw += LookAxisVector.X * MouseSensitivity;
		CurrentPitch += LookAxisVector.Y * MouseSensitivity;
        
		// Clamp pitch to prevent over-rotation
		CurrentPitch = FMath::Clamp(CurrentPitch, -89.0f, 89.0f);
        
		// Apply rotation to the actor
		FRotator NewRotation = FRotator(CurrentPitch, CurrentYaw, 0.0f);
		AddActorLocalRotation(FRotator(0.0f, LookAxisVector.X * MouseSensitivity, 0.0f));
        
		// For camera pitch, we can directly manipulate the spring arm
		FRotator SpringArmRotation = SpringArmComponent->GetRelativeRotation();
		SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch + LookAxisVector.Y * MouseSensitivity, -89.0f, 89.0f);
		SpringArmComponent->SetRelativeRotation(SpringArmRotation);
	}
}
	

// Called to bind functionality to input
void ACharacter_SpartaHomeWork_7::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// IA를 가져오기 위해 현재 소유 중인 Controller를 ASpartaPlayerController로 캐스팅
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				// IA_Move 액션 키를 "키를 누르고 있는 동안" Move() 호출
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ACharacter_SpartaHomeWork_7::Move
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ACharacter_SpartaHomeWork_7::Look
					);
			}
		}
	}
	
}



