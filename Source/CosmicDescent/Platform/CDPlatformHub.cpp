// Fill out your copyright notice in the Description page of Project Settings.


#include "CDPlatformHub.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CDPlatform.h"
#include "../Player/CDPaperCharacter.h"
#include "../AI/CDAICharacter.h"

ACDPlatformHub::ACDPlatformHub()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(GetRootComponent());
}

void ACDPlatformHub::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACDPlatformHub::OnOverlap);

	PlatformRotation = GetActorRotation();
	PlatformLocation = GetActorLocation();

	SpawnPlatform();
}

void ACDPlatformHub::SpawnPlatform()
{
	int32 Random;

	do 
		Random = FMath::FRandRange(0.0f, PlatformPayload.Num() - 0.001f);
	while (PlatformPayload[Random].PlatformDirection == PlatformDirection || PlatformPayload[Random].PlatformDirection == PlatformAnyDirection);

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(PlatformPayload[Random].PlatformClass, PlatformLocation, PlatformRotation);
	PlatformArray.Add(SpawnedActor);
	PlatformAnyDirection = PlatformPayload[Random].PlatformDirection;

	if (PlatformPayload[Random].PlatformDirection != ECDPlatformDirection::None)
		PlatformDirection = PlatformPayload[Random].PlatformDirection;

	FVector Origin;
	FVector BoxExtent;
	SpawnedActor->GetActorBounds(false, Origin, BoxExtent);
	PlatformLocation.Z -= BoxExtent.Z * 2;

	BoxComponent->SetBoxExtent(BoxExtent);
	BoxComponent->SetWorldLocation(SpawnedActor->GetActorLocation());
}

void ACDPlatformHub::DeletePlatform()
{
	PlatformArray[0]->Destroy();
	PlatformArray.RemoveAt(0);
}

void ACDPlatformHub::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACDPaperCharacter>(OtherActor))
	{
		SpawnPlatform();

		if (PlatformArray.Num() > PlatformCount)
			DeletePlatform();

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, "Overlap " + OverlappedComp->GetName());
	}
	else if (Cast<ACDAICharacter>(OtherActor))
	{
		AActor* Player = UGameplayStatics::GetActorOfClass(GetWorld(), APaperCharacter::StaticClass());		
		AActor* AI = UGameplayStatics::GetActorOfClass(GetWorld(), ACDAICharacter::StaticClass());
		AI->SetActorLocation(Player->GetActorLocation());
	}
}

