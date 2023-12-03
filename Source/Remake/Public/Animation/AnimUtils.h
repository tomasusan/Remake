#pragma once

class AnimUtils
{
public:
	template<typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation) {
		if (!Animation) return nullptr;

		const auto AnimNotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : AnimNotifyEvents) {
			if (const auto AnimNotify = Cast<T>(NotifyEvent.Notify)) {
				return AnimNotify;
			}
		}
		return nullptr;
	}
};