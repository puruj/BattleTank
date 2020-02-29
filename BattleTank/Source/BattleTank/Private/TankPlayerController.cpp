// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"

void  ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController doesn't possess tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void  ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {return;}
	FVector OutHitLocation; //Out Parameter
	if (GetSightRayHitLocation(OutHitLocation)) {
		GetControlledTank()->AimaAt(OutHitLocation);
	}
}
//Get world location of linetrace through crosshair, true if hits landscape
bool  ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	//find crosshair pos
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//Line trace aloong that direction, and check what is hit
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	

	return true;
}
bool  ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	return false; // Line trace did not succeed
}
bool  ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	//Set screen position of crosshair to world direction "De-Project"
	FVector CameraWorldLocation; //To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

}





