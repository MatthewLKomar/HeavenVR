// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Base.h"
//#include "GroundAnimalBase.h"
//#include "BehaviorTree/BehaviorTree.h"
//
//AAIC_Base::AAIC_Base()
//{
//	//Initialize components
//	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
//	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
//}
//
//AGroundAnimalBase* AAIC_Base::GetControlledAnimal()
//{
//	return Animal;
//}
//
//// Called when the controller possesses a Pawn/Character
//void AAIC_Base::OnPossess(APawn* InPawn)
//{
//	Super::OnPossess(InPawn);
//	// Convert InPawn to EnemyCharacter
//	Animal = Cast<AGroundAnimalBase>(InPawn);
//
//	// Check if pointers are valid
//	if (Animal)// && Animal->EnemyBehaviorTree)
//	{
//		
//		//BlackboardComp->InitializeBlackboard(*Character->EnemyBehaviorTree->BlackboardAsset);
//
//		//TargetKeyID = BlackboardComp->GetKeyID("Target");
//
//		//BehaviorComp->StartTree(*Character->EnemyBehaviorTree);
//	}
//}
