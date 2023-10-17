// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"
#include "InputActionValue.h"
#include "Chaos/ChaosDebugDraw.h"
#include "Killcode_character.generated.h"
class UInputAction;
class UInputMappingContext;

UCLASS()
class KILLCODE_API AKillcode_character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKillcode_character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// calling the input for the shooting then game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ShootAction;

	void Shoot(const FInputActionValue& Value);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Sets jump flag when key is pressed.
	
	UFUNCTION()
	void MoveX(float valinput);
	
	UFUNCTION()
	void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
	void StopJump();
	
	
	// SCS camera.
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* SCSCameraComponent;

protected:

	UPROPERTY(EditDefaultsOnly,Category = "spawn objects")
	TSubclassOf<AActor> BulletToSpawn;
	
	float Timer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "shooting")
	float ShootDelay;
	//creating the different axe's for where to spawn the bullet
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "shooting")
	float BulletSpawnLocationX = 0.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "shooting")
	float BulletSpawnLocationY = 0.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "shooting")
	float BulletSpawnLocationZ = 0.f;
};