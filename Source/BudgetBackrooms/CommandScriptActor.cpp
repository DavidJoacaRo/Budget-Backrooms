


#include "CommandScriptActor.h"

// Sets default values
ACommandScriptActor::ACommandScriptActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACommandScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACommandScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

