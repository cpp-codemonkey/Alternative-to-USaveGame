#include "QuestManager.h"

#include "Quest1.h"
#include "Quest2.h"

QuestManager& QuestManager::instance()
{
	static QuestManager Manager;
	return Manager;
}

void QuestManager::AddQuest(QuestPtr const& NewQuest)
{
	Quests.push_back(NewQuest);
}

void QuestManager::SpawnActors(UWorld* W)
{
	for (auto Q : Quests)
	{
		Q->SpawnActors(W);
	}
}

void QuestManager::DeleteActors()
{
	for (auto Q : Quests)
	{
		Q->DeleteActors();
	}
}

void QuestManager::DeleteQuests()
{
	Quests.clear();
}

void QuestManager::Print() const
{
	for (auto Q : Quests)
	{
		Q->Print();
	}
}

size_t QuestManager::NoOfQuests() const
{
	return Quests.size();
}

QuestManager::QuestManager()
{
	AddQuest(QuestPtr(new Quest1));
	AddQuest(QuestPtr(new Quest2));
}
