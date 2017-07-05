/*
 * HaveAction.hpp
 *
 *  Created on: 06.05.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja bazowej generycznej klasy HaveAction
 *
 * \class HaveAction
 * \brief
 * Bazowa klasa obiektu z ustawialną akcją typu std::function<void(T)>
 *
 * Jest to generyczna klasa bazowa w której podawany parametr T odpowiada za wewnętrzną instancję klasy std::function<void (T)>.
 *
 * \struct HaveActionHelper
 * \brief
 * Struktura pomocnicza dla argumentów typów != void
 *
 * \struct HaveActionHelper<void>
 * \brief
 * Struktura pomocnicza dla argumentu typu == void
 *
 */

#ifndef HAVEACTION_HPP_
#define HAVEACTION_HPP_

#include <functional>

template<typename T>
struct HaveActionHelper
{
    using function_type = std::function<void (T)>;
};

template <>
struct HaveActionHelper<void>
{
    using function_type = std::function<void ()>;
};


template <typename T>
class HaveAction {
public:
    using function_type = typename HaveActionHelper<T>::function_type;

	void setAction(function_type& a){action = a;}
	virtual void doAction(){}

	virtual ~HaveAction(){}

protected:
	function_type action;

};

#endif /* HAVEACTION_HPP_ */
