#ifndef SUDOKUSOLVER_CORE_OBSERVABLE_HPP_INCLUDED
#define SUDOKUSOLVER_CORE_OBSERVABLE_HPP_INCLUDED

#include<vector>
#include<algorithm>
#include<functional>

namespace SudokuSolver { namespace Core {

template<typename T>
class Observable {
public:    
    bool addObserver(T& observer);
    bool removeObserver(T& observer);

    void notifyObservers(std::function<void(T&)> func);

protected:
    Observable();
    virtual ~Observable();
    Observable(const Observable<T>& rhs);
    Observable& operator=(const Observable<T>& rhs);

    std::vector<T*> _observers;
};

}}

template<typename T>
SudokuSolver::Core::Observable<T>::Observable()
    : _observers()
{

}

template<typename T>
SudokuSolver::Core::Observable<T>::Observable(const SudokuSolver::Core::Observable<T>& rhs)
    : _observers()
{
    //_observers not copied here by design, copies should not inherit observers
    *this = rhs;
}

template<typename T>
SudokuSolver::Core::Observable<T>::~Observable()
{

}

template<typename T>
SudokuSolver::Core::Observable<T>& SudokuSolver::Core::Observable<T>::operator=(const SudokuSolver::Core::Observable<T>& rhs)
{
    //_observers not copied here by design, copies should not inherit observers
    return *this;
}

template<typename T>
bool SudokuSolver::Core::Observable<T>::addObserver(T& observer)
{
    auto element = std::find(_observers.begin(), _observers.end(), &observer);

    if(element == _observers.end())
    {
        _observers.push_back(&observer);
    }

    return (element == _observers.end());
}

template<typename T>
bool SudokuSolver::Core::Observable<T>::removeObserver(T& observer)
{
    auto element = std::find(_observers.begin(), _observers.end(), &observer);

    if(element != _observers.end())
    {
        _observers.erase(element);
    }

    return (element != _observers.end());
}

template<typename T>
void SudokuSolver::Core::Observable<T>::notifyObservers(std::function<void(T&)> func)
{
    for(T* observer : _observers)
    {
        func(*observer);
    }
}

#endif //SUDOKUSOLVER_CORE_OBSERVABLE_HPP_INCLUDED
