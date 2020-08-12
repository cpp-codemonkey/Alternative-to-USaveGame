#pragma once
#include "Quest.h"

THIRD_PARTY_INCLUDES_START
#include <cereal/types/vector.hpp>
THIRD_PARTY_INCLUDES_END

/**
 * @brief A class to manage quests.
 *
 * This is a Meyer Singleton so that only one QuestManager can ever exist. Obtain the one and only
 * QuestManager like so - auto& m = QuestManager::instance();
 */
class QuestManager
{
public:
	/**
	 * @brief Copy constructor is deleted to prevent copying.
	 */
	QuestManager(QuestManager&);
	
	/**
	 * @brief Assignment operator is deleted so you can't assign the one and only QuestManager to another instance.
	 * @return Not applicable.
	 */
	QuestManager operator=(QuestManager&);
	
	/**
	 * @brief This function is the only way to get a QuestManager.
	 * @return A reference to the one and only QuestManager.
	 */
	static QuestManager& instance();
	
	/**
	 * @brief Add a quest to the manager.
	 * @param NewQuest The quest to add to the manager.
	 */
	void AddQuest(QuestPtr const& NewQuest);
	
	/**
	 * @brief Spawns actors into the current level.
	 * @param W The world into which to spawn the actors.
	 */
	void SpawnActors(UWorld* W);

	/**
	 * @brief Deletes all spawned actors from the quests.
	 */
	void DeleteActors();
	
	/**
	 * @brief Deletes all quests from the manager.
	 */
	void DeleteQuests();
	
	/**
	 * @brief Prints out all quests to the UE4 log window.
	 */
	void Print() const;

	/**
	 * @brief Get the number of quests.
	 * @return The number of quests in the manager.
	 */
	size_t NoOfQuests() const;
private:
	/**
	 * @brief Private constructor so that users of QuestManager have to use instance().
	 */
	QuestManager();

	/**
	 * @brief The quests the QuestManager manages.
	 */
	std::vector<QuestPtr> Quests;

	friend class cereal::access;

	template <typename A>
	void serialize(A& ar)
	{
		ar(Quests);
		
	}
};
