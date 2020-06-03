/* 
This Blueprint is used with the ground AI to mark a series of way points in your level.
These WayPoints are then used by the AI as target locations.
*/

#include "AI_WayPoint.h"
#include <string>

// Sets default values
AAI_WayPoint::AAI_WayPoint()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Root->SetupAttachment(GetRootComponent());

	PathName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PathName"));
	PathName->SetupAttachment(Root);
	PathName->SetText(WayPointGroupName);
	PathName->SetVisibility(TextVisible, true);

	ID = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ID"));
	ID->SetupAttachment(PathName);
	ID->SetText(FText::FromString(std::to_string(WayPointID).c_str()));
	//^^It's nasty because we're converting an int->string->fstring->ftext
	
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(Root);
	
}

// Called when the game starts or when spawned
void AAI_WayPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_WayPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAI_WayPoint::SetWayPointInfo()
{
	PathName->SetText(WayPointGroupName);
	ID->SetText(FText::FromString(FString::FromInt(WayPointID)));
}

