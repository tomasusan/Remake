#pragma once

class RemakeUtils
{
public:
	template <typename T>
	static T* GetRemakePlayerComponent(AActor* PlayerPawn)
	{
		if(!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};