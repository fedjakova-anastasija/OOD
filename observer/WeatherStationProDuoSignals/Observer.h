#pragma once
#include <map>
#include <set>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, int priority = 0) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority = 0) override
	{
		RemoveObserver(observer);
		m_observers.insert(std::pair<int, ObserverType*>(priority, &observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observers = m_observers;
		for (auto& observer : observers)
		{
			observer.second->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		auto pos = std::find_if(m_observers.begin(), m_observers.end(), [&](auto pair) -> bool { return pair.second == &observer; });

		if (pos != m_observers.end())
		{
			m_observers.erase(pos);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::multimap<int, ObserverType*> m_observers;
};
