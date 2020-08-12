// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CerealDemoCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include <fstream>
#include <string>

THIRD_PARTY_INCLUDES_START
#include <UE4Serialization.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
THIRD_PARTY_INCLUDES_END

#include "Quest1.h"
#include "Quest2.h"
#include "QuestManager.h"

//#define USEXMLARCHIVE
#define USEBINARYARCHIVE
//#define USEJSONARCHIVE

std::string const BinFilePath("C:\\Users\\Brian_2\\Documents\\Dev\\UE4 Projects\\CerealDemo\\Saved\\SaveGames\\game.sav");
std::string const XMLFilePath("C:\\Users\\Brian_2\\Documents\\Dev\\UE4 Projects\\CerealDemo\\Saved\\SaveGames\\game.xml");
std::string const JSONFilePath("C:\\Users\\Brian_2\\Documents\\Dev\\UE4 Projects\\CerealDemo\\Saved\\SaveGames\\game.json");

//////////////////////////////////////////////////////////////////////////
// ACerealDemoCharacter

ACerealDemoCharacter::ACerealDemoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACerealDemoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACerealDemoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACerealDemoCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACerealDemoCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACerealDemoCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACerealDemoCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACerealDemoCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ACerealDemoCharacter::OnResetVR);

	// extra input
	PlayerInputComponent->BindAction("SaveGame", IE_Pressed, this, &ACerealDemoCharacter::OnSaveGame);
	PlayerInputComponent->BindAction("LoadGame", IE_Pressed, this, &ACerealDemoCharacter::OnLoadGame);
	PlayerInputComponent->BindAction("DeleteActors", IE_Pressed, this, &ACerealDemoCharacter::OnDeleteActors);
}

void ACerealDemoCharacter::OnSaveGame()
{
#ifdef USEXMLARCHIVE
	std::ofstream os(XMLFilePath.c_str());
	cereal::XMLOutputArchive oarchive(os);
#endif
#ifdef USEJSONARCHIVE
	std::ofstream os(JSONFilePath.c_str());
	cereal::JSONOutputArchive oarchive(os);
#endif
#ifdef USEBINARYARCHIVE
	std::ofstream os(BinFilePath.c_str(), std::ios::binary);
	cereal::BinaryOutputArchive oarchive(os);
#endif
	UE_LOG(LogTemp, Warning, TEXT("Before Save:"));
	QuestManager::instance().Print();
	UE_LOG(LogTemp, Warning, TEXT("Position Vector before save:"));
	PrintVector(Position);
	oarchive(QuestManager::instance(), Position);
}

void ACerealDemoCharacter::OnLoadGame()
{
	if (UWorld* const W = GetWorld())
	{
#ifdef USEXMLARCHIVE
		std::ifstream is(XMLFilePath.c_str());
		cereal::XMLInputArchive iarchive(is);
#endif
#ifdef USEJSONARCHIVE
		std::ifstream is(JSONFilePath.c_str());
		cereal::JSONInputArchive iarchive(is);
#endif
#ifdef USEBINARYARCHIVE
		std::ifstream is(BinFilePath.c_str(), std::ios::binary);
		cereal::BinaryInputArchive iarchive(is);
#endif
		QuestManager::instance().DeleteActors();
		QuestManager::instance().DeleteQuests();
		Position = FVector::ZeroVector;
		UE_LOG(LogTemp, Warning, TEXT("Before Load:"));
		QuestManager::instance().Print();
		UE_LOG(LogTemp, Warning, TEXT("Position Vector before load:"));
		PrintVector(Position);
		iarchive(QuestManager::instance(), Position);
		QuestManager::instance().SpawnActors(W);
		UE_LOG(LogTemp, Warning, TEXT("After load:"));
		QuestManager::instance().Print();
		UE_LOG(LogTemp, Warning, TEXT("Position Vector after load:"));
		PrintVector(Position);
	}
}

void ACerealDemoCharacter::OnDeleteActors()
{
	QuestManager::instance().DeleteActors();
	Position = FVector::ZeroVector;
}

void ACerealDemoCharacter::PrintVector(FVector const& v)
{
	UE_LOG(LogTemp, Warning, TEXT("FVector:"));
	UE_LOG(LogTemp, Warning, TEXT("X: %f"), v.X);
	UE_LOG(LogTemp, Warning, TEXT("Y: %f"), v.Y);
	UE_LOG(LogTemp, Warning, TEXT("Z: %f"), v.Z);
}


void ACerealDemoCharacter::BeginPlay()
{
	Super::BeginPlay();
	QuestManager::instance().SpawnActors(GetWorld());
}

void ACerealDemoCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACerealDemoCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ACerealDemoCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ACerealDemoCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACerealDemoCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACerealDemoCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACerealDemoCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
