// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "DrawDebugHelpers.h"



void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControllerTank = GetPlayerController();
    
    if(!ControllerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("player controller not possiset"))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("begin play from controller start from %s"), *(ControllerTank->GetName()))
    }
    
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
    AimTowredsCrossHairLocation();
}

ATank* ATankPlayerController::GetPlayerController() const
{
    return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowredsCrossHairLocation()
{
    FVector HitLocation;
    
    if(GetSightRayHitLocation(HitLocation))
    {
        GetPlayerController()->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector OutHitResult) const
{
    /// find the crosshair position in pixel coordinates
    int32 ViewPortX, ViewPortY;
    GetViewportSize(ViewPortX, ViewPortY);
    
    auto ScreenLocation = FVector2D(ViewPortX * CrossHairXLocation, ViewPortY * CrossHairYLocation);
    FVector LookDirection;
    
    if(GetPlayerAimPosition(ScreenLocation, LookDirection))
    {
        GetLookVectorHitLocation(LookDirection, OutHitResult);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Aim Location can not aim"));
    }
    
    
    
    return true;
}


bool ATankPlayerController::GetPlayerAimPosition(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector WorldLocation(0);
    return DeprojectScreenPositionToWorld(
                                   ScreenLocation.X,
                                   ScreenLocation.Y,
                                   WorldLocation,
                                   LookDirection
                                   );
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
    FHitResult HitResult;
    auto LineTraceStart = PlayerCameraManager->GetCameraLocation();
    auto LineTraceEnd = LineTraceStart + (LookDirection * LineTraceRange);
    bool AimTargetSuccess = GetWorld()->LineTraceSingleByChannel(
                                                                 HitResult,
                                                                 LineTraceStart,
                                                                 LineTraceEnd,
                                                                 ECollisionChannel::ECC_Visibility);
    if(AimTargetSuccess)
    {
        OutHitLocation = HitResult.Location;
        UE_LOG(LogTemp, Warning, TEXT("LineTraceEnd: %s"), *LineTraceEnd.ToString());
        DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor(255.f,0.f,0.f), false, -1, 0, 12.33);
        return true;
    }
    else
    {
//        OutHitLocation = FVector(0);
        return false;
    }
}
