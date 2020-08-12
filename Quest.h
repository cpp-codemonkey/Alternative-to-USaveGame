#pragma once
#include <memory>
#include <vector>

#include "ActorProxy.h"

class Quest;
typedef std::shared_ptr<Quest> QuestPtr;

enum EClassId{cidCone, cidSphere};

/**
 * @brief Parent class of all quest classes. Contains a list of actor proxies for spawning actors into a level.
 */
class Quest
{
public:
	/**
	 * @brief Spawn the actors that are in the ActorProxies vector.
	 * @param W The level to spawn the actors into. The created actors objects are added to the
	 * ActorObj field of the relevant proxy.
	 */
	void SpawnActors(UWorld* W);

	/**
	 * @brief Delete any spawned actors.
	 */
	void DeleteActors();
	
	/**
	 * @brief Adds a proxy to the quest.
	 * @param Proxy The new proxy to add.
	 */
	void AddActorProxy(ActorProxy const& Proxy);
	
	/**
	 * @brief Removes all the actor proxies.
	 */
	virtual void Reset();
	
	/**
	 * @brief Necessary virtual destructor - does nothing.
	 */
	virtual ~Quest();
	
	/**
	 * @brief Prints out the name of the class.
	 */
	virtual void Print() const;
private:
	/**
	 * @brief A vector of actor proxy objects. Used by SpawnActors.
	 */
	std::vector<ActorProxy> ActorProxies;

	friend class cereal::access;

	template <typename A>
	void serialize(A& ar)
	{
		ar(ActorProxies);
		
	}
};
