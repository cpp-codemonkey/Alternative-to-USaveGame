#pragma once
#include "Quest.h"

THIRD_PARTY_INCLUDES_START
#include <cereal/types/base_class.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
THIRD_PARTY_INCLUDES_END

class Quest2 : public Quest
{
public:
	Quest2();

	virtual void Reset() override;
	virtual void Print() const override;
private:
	bool RatsDead = true;
	int NoOfCheeses = 10;

	friend class cereal::access;

	template <typename A>
	void serialize(A& ar)
	{
		ar(cereal::base_class<Quest>(this));
		ar(RatsDead, NoOfCheeses);
	}
};

CEREAL_REGISTER_TYPE(Quest2)
