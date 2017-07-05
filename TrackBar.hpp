/*
 * TrackBar.hpp
 *
 *  Created on: 15.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy TrackBarBase dziedziczącej po sf::Drawable, HaveFocus i Pressable oraz definicja klasy TrackBar dziedziczącej po TrackBarBase
 *
 * \class TrackBarBase
 * \brief
 * Bazowa klasa TrackBar'a
 *
 * Klasa TrackBarBase zapewnia reprezentacje i funkcjonalność track bara do ustawiania wartości pomiędzy wartością minimalną a maksymalną.
 *
 * \class TrackBar
 * \brief
 * Generyczna klasa TrackBar'a
 *
 * Umożliwia tworzenie track bara dla różnych typów numerycznych.
 * Po ustwieniu wskaźnika na modyfikowaną zmienną, zmiana pozycji track bara automatycznie przepisze do niej swoją wartość.
 *
 */

#ifndef TRACKBAR_HPP_
#define TRACKBAR_HPP_

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <cmath>
#include "Conf.hpp"
#include "HaveName.hpp"
#include "Pressable.hpp"

class TrackBarBase : public sf::Drawable, public HaveName, public Pressable<void>{
public:
	TrackBarBase(std::string name="", double value=0.0, double max=100.0, double min=0.0);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	double getMax() const;
	void setMax(double max);
	double getMin() const;
	void setMin(double min);
	virtual double getValue() const;
	virtual void setValue(double value);
	virtual void moveValueABS(double shift);
	virtual void moveValue(float shift);
	virtual void update(sf::Vector2f mp, float diff, bool press);

protected:
	virtual void clampValue();

	double value;
	double min;
	double max;
};

template <typename T = double>
class TrackBar : public TrackBarBase{
public:
	TrackBar(std::string name="", double value=0.0, double max=100.0, double min=0.0, T* target=nullptr, T* targetMin=nullptr, T* targetMax=nullptr):
		TrackBarBase(name,value,max,min),
		target(target),
		targetMinimum(targetMin),
		targetMaximum(targetMax)
	{}

	TrackBar(std::string name="", T* target=nullptr, double max=100.0, double min=0.0, T* targetMin=nullptr, T* targetMax=nullptr):
		TrackBarBase(name, *target,max,min),
		target(target),
		targetMinimum(targetMin),
		targetMaximum(targetMax)
	{}


	void setTarget(T* target) {
		this->target = target;
	}

	void setTargetMaximum(T* targetMaximum) {
		this->targetMaximum = targetMaximum;
	}

	void setTargetMinimum(T* targetMinimum) {
		this->targetMinimum = targetMinimum;
	}

	void updateTarget(){
		if(target != nullptr){
			*target = value;
		}
		if(action){
			action();
		}
	}

	virtual void setValue(double value){
		TrackBarBase::setValue(value);
		updateTarget();
	}

	virtual void moveValueABS(double shift){
		TrackBarBase::moveValueABS(shift);
		updateTarget();
	}

	virtual void moveValue(float shift){
		TrackBarBase::moveValue(shift);
		updateTarget();
	}


private:
	virtual void clampValue(){
		TrackBarBase::clampValue();
		if(targetMaximum != nullptr && value > *targetMaximum){
			value = *targetMaximum;
		}
		if(targetMinimum != nullptr && value < *targetMinimum){
			value = *targetMinimum;
		}
	}


	T* target;
	T* targetMinimum;
	T* targetMaximum;

};





#endif /* TRACKBAR_HPP_ */
