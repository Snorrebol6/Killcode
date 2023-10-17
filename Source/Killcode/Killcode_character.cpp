// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "AI/NavigationSystemBase.h"
#include "Misc/TypeContainer.h"
#include "SCSProjectile.h"
#include "Killcode_character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AKillcode_character::AKillcode_character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a side scroller camera component.
	SCSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideScrollerShooterCamera"));
	check(SCSCameraComponent != nullptr);

	Timer = ShootDelay;
	
	bUseControllerRotationYaw = false;
	// Attach the camera component to our capsule component.
	SCSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AKillcode_character::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

// Called every frame
void AKillcode_character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;
}

// Called to bind functionality to input
void AKillcode_character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AKillcode_character::Shoot);
	}
	// Setting up the "look" bindings.
	PlayerInputComponent->BindAxis("MoveX", this, &AKillcode_character::MoveX);

	// Setting up the "Jump" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKillcode_character::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AKillcode_character::StopJump);
}
//checking if the ShootPressed value is true when input is used
void AKillcode_character::Shoot(const FInputActionValue& Value)
{
	bool ShootPressed = Value.Get<bool>();

	UE_LOG(LogTemp, Warning, TEXT("Bool value is: %hs"), &ShootPressed? "true" : "false" );
	FVector location = GetActorLocation();
	location = FVector (location.X + BulletSpawnLocationX, location.Y + BulletSpawnLocationY, location.Z + BulletSpawnLocationZ);

	if(ShootPressed == true)
	{
		if (Timer >= ShootDelay)
		{
			Timer = 0;

			FActorSpawnParameters SpawnParams;
			AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(BulletToSpawn, location,GetActorRotation(),SpawnParams);
		}
	}
}

void AKillcode_character::MoveX(float valinput)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, valinput);
	if (((MoveX != 0)))
	{
		
	}
}
void AKillcode_character::StartJump()
{
	bPressedJump = true;
}

void AKillcode_character::StopJump()
{
	bPressedJump = false;
}