// Alec Larin

#include "GameCodeBasePawn.h"
#include "Components/SphereComponent.h"
#include "../Components/MovementComponent/GCPawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"

AGameCodeBasePawn::AGameCodeBasePawn()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionComponent->SetSphereRadius(CollisionSphereRadius);
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = CollisionComponent;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UGCPawnMovementComponent>(TEXT("Pawn movement component"));
	MovementComponent->SetUpdatedComponent(CollisionComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

#if	WITH_EDITORONLY_DATA
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(RootComponent);
#endif
}

void AGameCodeBasePawn::BeginPlay()
{
	Super::BeginPlay();
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CurrentViewActor = CameraManager->GetViewTarget();
	CameraManager->OnBlendComplete().AddUFunction(this, FName("OnBlendComplete"));
}

void AGameCodeBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameCodeBasePawn::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	InputForward = MovementVector.Y;
	InputRight = MovementVector.X;

	if (MovementVector != FVector2D::ZeroVector)
	{
		if (MovementComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Movement: %s"), *MovementVector.ToString());
			MovementComponent->AddInputVector(CurrentViewActor->GetActorForwardVector() * MovementVector.Y);
			MovementComponent->AddInputVector(CurrentViewActor->GetActorRightVector() * MovementVector.X);
		}
	}
}

void AGameCodeBasePawn::StopMoving(const FInputActionValue& Value)
{
	InputForward = 0.0f;
	InputRight = 0.0f;
}

void AGameCodeBasePawn::Look(const FInputActionValue& Value) 
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("LookVector: %s"), *LookVector.ToString());

	if (LookVector != FVector2D::ZeroVector) 
	{
		if (MovementComponent)
		{
			AddControllerYawInput(LookVector.X);
			AddControllerPitchInput(LookVector.Y);
		}
	}
}

void AGameCodeBasePawn::Jump(const FInputActionValue& Value)
{
	checkf(MovementComponent->IsA<UGCPawnMovementComponent>(), TEXT("AGameCodeBasePawn::Jump() Jump can work only with UGCPawnMovementComponent"));
	UGCPawnMovementComponent* GameCodeMovementComponent = StaticCast<UGCPawnMovementComponent*>(MovementComponent);
	GameCodeMovementComponent->JumpStart();
}

void AGameCodeBasePawn::OnBlendComplete()
{
	CurrentViewActor = GetController()->GetViewTarget();
}

