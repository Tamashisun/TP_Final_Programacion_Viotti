#include "MG_Character.h"
#include "MG_Collectable.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AMG_Character::AMG_Character()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
}

void AMG_Character::BeginPlay()
{
    Super::BeginPlay();

    // Agregar Mapping Context
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            if (DefaultMappingContext)
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    // Bindear overlap
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(
        this, &AMG_Character::OnOverlapBegin
    );
}

void AMG_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
            EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMG_Character::DoMove);

        if (LookAction)
            EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMG_Character::DoLook);

        if (JumpAction)
        {
            EIC->BindAction(JumpAction, ETriggerEvent::Started,   this, &AMG_Character::DoJumpStart);
            EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMG_Character::DoJumpEnd);
        }
    }
}

// ── Input Handlers ────────────────────────────────────────────────────────────

void AMG_Character::DoMove(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    // Movimiento relativo al mundo (camara fija top-down)
    const FVector ForwardDir = FVector(1.f, 0.f, 0.f); // eje X mundo -> W/S
    const FVector RightDir   = FVector(0.f, 1.f, 0.f); // eje Y mundo -> A/D

    AddMovementInput(ForwardDir, MovementVector.Y);
    AddMovementInput(RightDir,   MovementVector.X);
}

void AMG_Character::DoLook(const FInputActionValue& Value)
{
    FVector2D LookVector = Value.Get<FVector2D>();
    AddControllerYawInput(LookVector.X);
    AddControllerPitchInput(LookVector.Y);
}

void AMG_Character::DoJumpStart()
{
    Jump();
}

void AMG_Character::DoJumpEnd()
{
    StopJumping();
}

// ── Replicacion ───────────────────────────────────────────────────────────────

void AMG_Character::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMG_Character, bIsCarrying);
    DOREPLIFETIME(AMG_Character, CarriedPointValue);
}

void AMG_Character::OnRep_IsCarrying()
{
    UE_LOG(LogTemp, Warning, TEXT("IsCarrying changed: %s"),
        bIsCarrying ? TEXT("Carrying") : TEXT("Empty"));
}

// ── RPCs ──────────────────────────────────────────────────────────────────────

void AMG_Character::Server_PickupObject_Implementation()
{
    if (HasAuthority())
    {
        bIsCarrying = true;
        Multicast_PlayPickupEffect();
    }
}

bool AMG_Character::Server_PickupObject_Validate()
{
    return true;
}

void AMG_Character::Server_DeliverObject_Implementation()
{
    if (HasAuthority())
    {
        bIsCarrying = false;
        CarriedPointValue = 0;
    }
}

bool AMG_Character::Server_DeliverObject_Validate()
{
    return true;
}

void AMG_Character::Multicast_PlayPickupEffect_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("Pickup effect played on all clients"));
}

// ── Overlap ───────────────────────────────────────────────────────────────────

void AMG_Character::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!HasAuthority()) return;
    if (bIsCarrying) return;

    AMG_Collectable* Collectable = Cast<AMG_Collectable>(OtherActor);
    if (Collectable && !Collectable->bIsPickedUp)
    {
        bIsCarrying = true; // Set inmediato para bloquear overlaps simultáneos
        CarriedPointValue = Collectable->PointValue;
        Multicast_PlayPickupEffect();
        Collectable->PickUp();
    }
}
