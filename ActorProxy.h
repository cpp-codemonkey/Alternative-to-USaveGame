#pragma once
#include "Rotator.h"
#include "Vector.h"

THIRD_PARTY_INCLUDES_START
#include <UE4Serialization.hpp>
THIRD_PARTY_INCLUDES_END

/**
 * @brief A proxy class that represents an actor to be spawned into a level. Used by quests.
 */
struct ActorProxy
{
	/**
	 * @brief The location at which the actor is to be spawned.
	 */
	FVector Location;
	
	/**
	 * @brief The rotation of the spawned actor.
	 */
	FRotator Rotation;
	
	/**
	 * @brief The class to spawn.
	 */
	int ActorClass;
	
	/**
	 * @brief The actual object spawned.
	 */
	AActor* ActorObj;
private:
	friend class cereal::access;

	template <typename A>
	void serialize(A& ar)
	{
		ar(Location);
		ar(Rotation);
		ar(ActorClass);
	}
};
