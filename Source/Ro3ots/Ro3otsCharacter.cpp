// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ro3otsCharacter.h"

#include "AttackSystem.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ARo3otsCharacter

ARo3otsCharacter::ARo3otsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ARo3otsCharacter::BeginPlay()
{
	Super::BeginPlay();

}


void ARo3otsCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	attackTimer += DeltaSeconds;

	AttackSelectedEnemy(targetActor);

	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	TArray<FHitResult> HitArray;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), TraceStart, TraceEnd, TraceRadius, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitArray, true, FLinearColor::Green, FLinearColor::Red, 0);


	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugSphere(GetWorld(), TraceStart, TraceRadius, 18.0f, FColor::Green, false, -1, 0, 1);
	
	if (Hit)
	{
		for(const FHitResult HitResult : HitArray)
		{
			if (HitResult.GetActor()->ActorHasTag("Enemy"))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, FString::Printf(TEXT("Hit : %s"), *HitResult.GetActor()->GetName()));
				IAttackSystem::Execute_InRangeEnemy(this->GetController(), HitResult.GetActor(), true);

			}
		}
	}


	if (attackTimer >= (1 / AttackSpeed) && isInRangeToAttack == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I'm in range and I probably can attack!"));
		canAttack = true;
	} else
	{
		canAttack = false;
	}

}

void ARo3otsCharacter::AttackSelectedEnemy(AActor* Enemy)
{
	if (canAttack && Enemy != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I can attack!"));
		IAttackSystem::Execute_AttackEnemy(this, Enemy, AttackDamage, true);
		attackTimer = 0.0f;
		canAttack = false;
	}
}
