#include "SQG/API/ConditionUtils.h"

namespace SQG
{
	RE::TESConditionItem* CreateCondition(void* inParameter, const REX::EnumSet<RE::FUNCTION_DATA::FunctionID, std::uint16_t>& inFunction, const RE::CONDITION_ITEM_DATA::OpCode inOpCode, const RE::CONDITION_ITEM_DATA::GlobalOrFloat inComparisonValue)
	{
		auto* result = new RE::TESConditionItem();
		result->data.dataID = std::numeric_limits<std::uint32_t>::max();
		result->data.functionData.function = inFunction;
		result->data.functionData.params[0] = inParameter;
		result->data.flags.opCode = inOpCode;
		result->data.comparisonValue = inComparisonValue;
		result->next = nullptr;
		return result;
	}

	bool CheckCondition(RE::TESObjectREFR* inCaller, const std::list<RE::TESConditionItem*>& inConditions)
	{
		RE::TESCondition condition;
		RE::TESConditionItem** conditionItemHolder = &condition.head;
		for(const auto* conditionItem : inConditions)
		{
			*conditionItemHolder = new RE::TESConditionItem();
			(*conditionItemHolder)->data = conditionItem->data;
			conditionItemHolder = &((*conditionItemHolder)->next);
		}
		*conditionItemHolder = nullptr;

		return condition(inCaller, inCaller);
	}
}
