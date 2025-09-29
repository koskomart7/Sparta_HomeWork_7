// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "inputmappingcontext.h"
#include "InputAction.h"
#include "UObject/ConstructorHelpers.h"
#include "Character_SpartaHomeWork_7.h"

ASpartaPlayerController::ASpartaPlayerController()
{
	PlayerPawn = nullptr;
	InputMappingContext = nullptr;
	MoveAction = nullptr;
	JumpAction = nullptr;
	LookAction = nullptr;
	SprintAction = nullptr;
	ElevateAction = nullptr;
	RollAction = nullptr;
}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext != nullptr)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}