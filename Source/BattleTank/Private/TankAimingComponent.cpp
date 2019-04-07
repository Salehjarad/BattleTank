// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrelComponent.h"
#include "Classes/Kismet/GameplayStatics.h"


UTankAimingComponent::UTankAimingComponent()
{
//    bWantsBeginPlay = true;
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelLocation(UTankBarrelComponent* SetBarrel)
{
    Barrel = SetBarrel;
}

void UTankAimingComponent::SetTurrentlLocation(UTankTurret* SetTurret)
{
    Turret = SetTurret;
}

void UTankAimingComponent::AimingAtFromTank(FVector HitResult, float LaunchVelocity)
{
    if(!Barrel) { return; }
    
    FVector OutLaunchVelocity(0);
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    
    if(UGameplayStatics::SuggestProjectileVelocity(
                                                   this,
                                                   OutLaunchVelocity,
                                                   StartLocation,
                                                   HitResult,
                                                   LaunchVelocity,
                                                   false,
                                                   0,
                                                   0,
                                                   ESuggestProjVelocityTraceOption::DoNotTrace
                                                   )
    
    )
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowared(AimDirection);
    }
    else
    {
        auto Time = GetWorld()->GetTimeSeconds();
//        UE_LOG(LogTemp, Warning, TEXT("%f Aming solution not found"), Time)
    }
}


void UTankAimingComponent::MoveBarrelTowared(FVector AimDirection)
{
    auto BarrelRotation = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotation;
    
    Turret->Elevate(DeltaRotator.Yaw);
    Barrel->Elevate(DeltaRotator.Pitch);
}
