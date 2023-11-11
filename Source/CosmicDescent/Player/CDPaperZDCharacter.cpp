// Fill out your copyright notice in the Description page of Project Settings.


#include "CDPaperZDCharacter.h"
#include "Components/CapsuleComponent.h"

ACDPaperZDCharacter::ACDPaperZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ACDPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACDPaperZDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCharacter();
	UpdateAnimation();
}

void ACDPaperZDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACDPaperZDCharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACDPaperZDCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACDPaperZDCharacter::MoveRight);
}

void ACDPaperZDCharacter::UpdateCharacter()
{
	if (!bFlipOnInputVelocity)
		return;

	if ((GetVelocity().Y > 0.0f && !bFacingRight) || (GetVelocity().Y < 0.0f && bFacingRight))
	{
		bFacingRight = !bFacingRight;
		FVector CurrentScale = GetSprite()->GetRelativeScale3D();
		CurrentScale.X = -CurrentScale.X;
		GetSprite()->SetRelativeScale3D(CurrentScale);
	}
}

void ACDPaperZDCharacter::UpdateAnimation()
{
	UPaperFlipbook* CurrentAnimation = IdleAnimation;

	if (GetCharacterMovement()->IsFalling() || GetCapsuleComponent()->IsSimulatingPhysics())
		CurrentAnimation = JumpAnimation;
	else if (!GetInputVelocity().IsZero())
		CurrentAnimation = RunAnimation;
	else if (!GetVelocity().IsZero())
		CurrentAnimation = SlideAnimation;

	if (GetSprite()->GetFlipbook() != CurrentAnimation)
		GetSprite()->SetFlipbook(CurrentAnimation);
}

FVector ACDPaperZDCharacter::GetInputVelocity() const
{
	return InputVelocity;
}

void ACDPaperZDCharacter::MoveForward(float Amount)
{
	InputVelocity.Y = Amount;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ACDPaperZDCharacter::MoveRight(float Amount)
{
	InputVelocity.X = Amount;
	AddMovementInput(GetActorRightVector(), Amount);
}