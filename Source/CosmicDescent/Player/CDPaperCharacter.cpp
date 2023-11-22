// Fill out your copyright notice in the Description page of Project Settings.


#include "CDPaperCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

ACDPaperCharacter::ACDPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ACDPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACDPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCharacter();
	UpdateAnimation();
}

void ACDPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACDPaperCharacter::Jump);
	PlayerInputComponent->BindAction("Slide", IE_Pressed, this, &ACDPaperCharacter::Slide);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACDPaperCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACDPaperCharacter::MoveRight);
}

void ACDPaperCharacter::UpdateCharacter()
{
	if (!bFlipOnVelocity)
		return;

	if ((GetRelativeVelocity().Y > 0.0f && !bFacingRight)
		|| (GetRelativeVelocity().Y < 0.0f && bFacingRight))
	{
		bFacingRight = !bFacingRight;
		FVector CurrentScale = GetSprite()->GetRelativeScale3D();
		CurrentScale.X = -CurrentScale.X;
		GetSprite()->SetRelativeScale3D(CurrentScale);
	}
}

void ACDPaperCharacter::UpdateAnimation()
{
	UPaperFlipbook* CurrentAnimation = IdleAnimation;

	if (GetCapsuleComponent()->IsSimulatingPhysics() || GetCharacterMovement()->IsFalling())
		CurrentAnimation = JumpAnimation;
	else if (IsSliding())
		CurrentAnimation = SlideAnimation;
	else if (!GetInputVelocity().IsZero())
		CurrentAnimation = RunAnimation;
	else if (!GetVelocity().IsZero())
		CurrentAnimation = SlideAnimation;

	if (GetSprite()->GetFlipbook() != CurrentAnimation)
		GetSprite()->SetFlipbook(CurrentAnimation);
}

FVector ACDPaperCharacter::GetInputVelocity() const
{
	return InputVelocity;
}

FVector ACDPaperCharacter::GetRelativeVelocity() const
{
	return GetActorRotation().UnrotateVector(GetVelocity()).GetSafeNormal();
}

void ACDPaperCharacter::Slide()
{
	if (GetCharacterMovement()->IsFalling() || GetInputVelocity().IsZero() || IsSliding())
		return;

	StartSliding();
}

bool ACDPaperCharacter::IsSliding()
{
	return bIsSliding;
}

void ACDPaperCharacter::StartSliding()
{
	bIsSliding = true;
	Controller->SetIgnoreMoveInput(true);
	DefaultDeleration = GetCharacterMovement()->BrakingDecelerationWalking;
	GetCharacterMovement()->BrakingDecelerationWalking = SlideDeleration;
	LaunchCharacter(GetVelocity() / SlideMultiplier, false, false);
	GetWorld()->GetTimerManager().SetTimer(SlideTimer, this, &ACDPaperCharacter::StopSliding, SlideDuration, false);
}

void ACDPaperCharacter::StopSliding()
{
	bIsSliding = false;
	Controller->SetIgnoreMoveInput(false);
	GetCharacterMovement()->BrakingDecelerationWalking = DefaultDeleration;
	GetWorld()->GetTimerManager().ClearTimer(SlideTimer);
}

void ACDPaperCharacter::MoveForward(float Amount)
{
	InputVelocity.X = Amount;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ACDPaperCharacter::MoveRight(float Amount)
{
	InputVelocity.Y = Amount;
	AddMovementInput(GetActorRightVector(), Amount);
}