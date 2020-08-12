#pragma once
#include "Quest.h"

THIRD_PARTY_INCLUDES_START
#include <cereal/types/base_class.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
THIRD_PARTY_INCLUDES_END

class Quest1 : public Quest
{
public:
	Quest1();

	virtual void Reset() override;
	virtual void Print() const override;
private:
	int NoOfBeers = 10;
	int NoOfLipsticks = 20;
	int NoOfCaviars = 30;

	friend class cereal::access;

	template <typename A>
	void serialize(A& ar)
	{
		ar(cereal::base_class<Quest>(this));
		ar(NoOfBeers, NoOfLipsticks, NoOfCaviars);
	}
};

CEREAL_REGISTER_TYPE(Quest1)
