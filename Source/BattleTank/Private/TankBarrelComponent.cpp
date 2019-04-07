// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrelComponent.h"


void UTankBarrelComponent::Elevate(float RelativeSpeed)
{
//    UE_LOG(LogTemp, Warning, TEXT("Aming At: %f"), DegreesPerSecond)
    
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    
    SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MainElevationDegrees, MaxElevationDegrees), 0, 0));

}
