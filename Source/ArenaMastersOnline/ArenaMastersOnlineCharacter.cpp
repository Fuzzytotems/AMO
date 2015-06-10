// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ArenaMastersOnline.h"
#include "ArenaMastersOnlineCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AArenaMastersOnlineCharacter

AArenaMastersOnlineCharacter::AArenaMastersOnlineCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	InitStats();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AArenaMastersOnlineCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &AArenaMastersOnlineCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AArenaMastersOnlineCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AArenaMastersOnlineCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AArenaMastersOnlineCharacter::LookUpAtRate);
	InputComponent->BindAxis("CastSpell", this, &AArenaMastersOnlineCharacter::CastSpell);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AArenaMastersOnlineCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AArenaMastersOnlineCharacter::TouchStopped);
}


void AArenaMastersOnlineCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AArenaMastersOnlineCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AArenaMastersOnlineCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AArenaMastersOnlineCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AArenaMastersOnlineCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AArenaMastersOnlineCharacter::MoveRight(float Value)
{
  	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AArenaMastersOnlineCharacter::InitStats()
{
	baseMaxHealth = 10000;
	baseMaxResource = 10000;
	currentHealth = baseMaxHealth;
	maxHealth = baseMaxHealth;
	currentResource = baseMaxResource;
	maxResource = baseMaxResource;
}

void AArenaMastersOnlineCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}

void AArenaMastersOnlineCharacter::TickRegen(float DeltaSeconds)
{

}

void AArenaMastersOnlineCharacter::CastSpell(float Value)
{
	FHitResult MouseTrace;
	FCollisionQueryParams TraceParams;
	FVector WorldPosition;
	FVector WorldDirection;
	APlayerController* MyController = Cast<APlayerController>(this->Controller);
	FColor LineColor;

	TraceParams.bTraceComplex = true;
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	TraceParams.AddIgnoredActor(this);

	FHitResult* SentHitResult;

	MyController->DeprojectMousePositionToWorld(WorldPosition, WorldDirection);
	//GetWorld()->LineTraceSingle(MouseTrace, WorldPosition, WorldPosition + (WorldDirection * 50000), ECC_Visibility, TraceParams);
	GetWorld()->LineTraceSingleByChannel(MouseTrace, WorldPosition, WorldPosition + (WorldDirection * 50000), ECC_Visibility, TraceParams);

	if (MouseTrace.ImpactPoint != FVector(0, 0, 0))
	{
		GetWorld()->LineTraceSingleByChannel(MouseTrace, this->GetActorLocation(), MouseTrace.ImpactPoint, ECC_Visibility, TraceParams);
	}
	else
	{
		GetWorld()->LineTraceSingleByChannel(MouseTrace, this->GetActorLocation(), MouseTrace.TraceEnd, ECC_Visibility, TraceParams);
	}

	FVector TraceEnd = WorldPosition + (WorldDirection * 20000);

	SentHitResult = &MouseTrace;

	if (MouseTrace.ImpactPoint == FVector(0, 0, 0))
	{
		MouseTrace.ImpactPoint = MouseTrace.TraceEnd;
	}

	//DrawDebugLine(this->GetWorld(), SentHitResult->TraceStart, SentHitResult->ImpactPoint, LineColor, true, 10.f);

	//if (Role == ROLE_Authority)
	//{
	//	ClientCastSpell(SpellIndex, *SentHitResult);
	//}
	//else
	//{
	//	ServerCastSpell(SpellIndex, *SentHitResult);
	//}

	spellbook->CastSpell(Value, Target, MouseTrace);
}

//void AArenaMastersOnlineCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//}