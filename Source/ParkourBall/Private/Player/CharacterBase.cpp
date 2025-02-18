// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/ThrowableProjectile.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BoomArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SocketOffset = FVector(0.0f, 40.0f, 80.0f); // setup default boom arm offset
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraComponent->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void ACharacterBase::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//get direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0.0f, Rotation.Yaw, 0.0f);

		const FVector ForwardDirection = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACharacterBase::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACharacterBase::Throw(const FInputActionValue& Value)
{
	if (!AnimComplete) return;

	TObjectPtr<UWorld> const World = GetWorld();
	if (Controller != nullptr) {
		if (World != nullptr) {
			APlayerController* PlayerController = Cast <APlayerController>(GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AThrowableProjectile* SpawnedProjectile = World->SpawnActor<AThrowableProjectile>(ThrowableClass, GetMesh()->GetSocketLocation("ThrowableSocket"), SpawnRotation, ActorSpawnParams);
			SpawnedProjectile->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "ThrowableSocket");

			FTimerHandle ThrowableTimer;
			FTimerDelegate TimerDel;
			TimerDel.BindUFunction(this, FName("Release"), SpawnedProjectile);
			GetWorldTimerManager().SetTimer(ThrowableTimer, TimerDel, 0.25f, false);
		}

		if (ThrowAnim != nullptr) {
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance != nullptr) {
				AnimComplete = false;
				float MontageLength = AnimInstance->Montage_Play(ThrowAnim, 1.0f);

				FTimerHandle AnimTimer;
				FTimerDelegate AnimTimerDel;
				AnimTimerDel.BindUFunction(this, FName("SetAnimComplete"), true);
				GetWorldTimerManager().SetTimer(AnimTimer, AnimTimerDel, MontageLength, false);
			}
		}
	}
}

void ACharacterBase::Release(AThrowableProjectile* SpawnedProjectile)
{
	SpawnedProjectile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SpawnedProjectile->OnRelease(CameraComponent->GetForwardVector());
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterBase::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterBase::Look);

		//Throwing
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &ACharacterBase::Throw);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing Enhanced Input Component"));
	}
}

