// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character_SpartaHomeWork_7.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class PR_SPARTAPROJECT_API ACharacter_SpartaHomeWork_7 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACharacter_SpartaHomeWork_7();
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComponent;
	
	

	
	UFUNCTION()
	void Move(const FInputActionValue& value);	// 구조체는 크기가 커서 복사대신 참조를 통해서 가져온다
	UFUNCTION()
	void Look(const FInputActionValue& value);


private:
	// 현재 마우스 회전 값들
	float CurrentYaw = 0.0f;
	float CurrentPitch = 0.0f;
};
