// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"

ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();	// Uclass 형태의 타입 반환. 리플렉션시스템 지원
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	
}
