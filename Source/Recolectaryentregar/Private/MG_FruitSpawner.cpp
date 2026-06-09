#include "MG_FruitSpawner.h"
#include "EngineUtils.h"

AMG_FruitSpawner::AMG_FruitSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
}

void AMG_FruitSpawner::BeginPlay()
{
    Super::BeginPlay();

    if (!HasAuthority()) return;

    ScheduleNextSpawn(EFruitType::Banana);
    ScheduleNextSpawn(EFruitType::Apple);
    ScheduleNextSpawn(EFruitType::Strawberry);
}

void AMG_FruitSpawner::ScheduleNextSpawn(EFruitType Type)
{
    float MinTime = 1.f;
    float MaxTime = 5.f;
    FTimerHandle* Handle = &BananaTimer;

    switch (Type)
    {
        case EFruitType::Banana:
            MinTime = 1.f; MaxTime = 5.f;
            Handle = &BananaTimer;
            break;
        case EFruitType::Apple:
            MinTime = 5.f; MaxTime = 20.f;
            Handle = &AppleTimer;
            break;
        case EFruitType::Strawberry:
            MinTime = 10.f; MaxTime = 60.f;
            Handle = &StrawberryTimer;
            break;
    }

    float Delay = FMath::RandRange(MinTime, MaxTime);

    GetWorldTimerManager().SetTimer(*Handle, [this, Type]()
    {
        SpawnFruit(Type);
        ScheduleNextSpawn(Type);
    }, Delay, false);
}

void AMG_FruitSpawner::SpawnFruit(EFruitType Type)
{
    if (CountFruitsInWorld() >= MaxFruits) return;

    TSubclassOf<AMG_Collectable> ClassToSpawn = nullptr;
    switch (Type)
    {
        case EFruitType::Banana:     ClassToSpawn = BananaClass;     break;
        case EFruitType::Apple:      ClassToSpawn = AppleClass;      break;
        case EFruitType::Strawberry: ClassToSpawn = StrawberryClass; break;
    }

    if (!ClassToSpawn) return;

    // Posición aleatoria dentro del radio
    FVector Origin = GetActorLocation();
    float RandAngle = FMath::RandRange(0.f, 360.f);
    float RandDist  = FMath::RandRange(0.f, SpawnRadius);
    FVector Offset  = FVector(
        FMath::Cos(FMath::DegreesToRadians(RandAngle)) * RandDist,
        FMath::Sin(FMath::DegreesToRadians(RandAngle)) * RandDist,
        0.f
    );

    FVector SpawnLocation = Origin + Offset;
    FRotator SpawnRotation = FRotator::ZeroRotator;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AMG_Collectable* Fruit = GetWorld()->SpawnActor<AMG_Collectable>(
        ClassToSpawn, SpawnLocation, SpawnRotation, Params
    );

    if (Fruit)
    {
        Fruit->FruitType = Type;
    }
}

int32 AMG_FruitSpawner::CountFruitsInWorld() const
{
    int32 Count = 0;
    for (TActorIterator<AMG_Collectable> It(GetWorld()); It; ++It)
    {
        if (!It->bIsPickedUp) Count++;
    }
    return Count;
}