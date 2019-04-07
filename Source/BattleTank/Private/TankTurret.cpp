// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Elevate(float RelativeSpeed)
{
    //    UE_LOG(LogTemp, Warning, TEXT("Aming At: %f"), DegreesPerSecond)
    
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Yaw + ElevationChange;
    auto RotateAmount = FMath::Clamp<float>(RelativeSpeed, MainElevationDegrees, MaxElevationDegrees);
    
    SetRelativeRotation(FRotator(0, RawNewElevation, 0));
    
}
