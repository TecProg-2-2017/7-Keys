/*
 *  File: boss.cpp
 *
 *  Description:  Implementation of Boss class
 */

#include <core/animation.h>
#include <iostream>

#include "boss.h"
#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

using namespace std;

// Boss's constructor method
Boss::Boss(Object *parent,
           ObjectID id,
           double x, double y,// Used for xis positioning
           int mass,          // range:
           bool walkable,     // If false, the boss cannot walk
           int dir)           // Direction the object is facing
    : Object(parent, id, x, y), m_damage(0.9), m_animation (new Animation("res/sprites/boss_running.png",
    	0, 0, 90, 90, 6, 120, true)), m_direction((Direction) dir), m_last(0) {

    this->set_mass(mass);
    this->set_w(70);
    this->set_h(70);
    this->set_walkable(walkable);
    this->set_summoned(false);
    this->set_created(false);

    update_vision();
}

// Boss's destructor method
Boss::~Boss() {
}

// This method returns the class's m_direction value
Boss::Direction Boss::direction() {
  return m_direction;
}

// For updating the vision of the boss
void Boss::update_vision() {
}

// Set method for direction
// Recieves direction as param
void Boss::set_direction(Direction direction) {
  m_direction = direction;
}

//  Show boss's animation
void Boss::draw_self() {
  m_animation->draw(x(), y());
}

// Defines boss's movementation
void Boss::walk() {
  double speed = 1.3;

  if (player_posx < this->x()) {
    set_x(x() - speed);
  }
  else {
    set_x(x() + speed);
  }

  if (player_posy < this->y()) {
    set_y(y() - speed);
  }
  else {
    set_y(y() + speed);
  }

  if (player_posx > this->x() - 100 && player_posx < this->x() + 100 && player_posy < this->y()) {
    set_direction(Boss::UP);
  }
  else if (player_posx > this->x() - 100 && player_posx < this->x() + 100 && player_posy > this->y()) {
    set_direction(Boss::DOWN);
  }
  else if (player_posx < this->x()) {
    set_direction(Boss::LEFT);
  }
  else {
    set_direction(Boss::RIGHT);
  }
}

// Updates boss's direction
// Recieves elapsed as param. Range: bigger than 0
void Boss::update_direction(unsigned long elapsed) {
  m_animation->set_row(this->direction());
}

// Gets player's X axis position
// Recieves pos_x as param, which must be within the screen
void Boss::get_playerx(int pos_x) {
  player_posx = pos_x;
}

// Gets player's Y axis position
// Recieves pos_y as param, which must be within the screen
void Boss::get_playery(int pos_y) {
  player_posy = pos_y;
}

// Returns the damage dealt in a boss's attack
double Boss::damage() {
  return m_damage;
}

// Updates boss's stats
// Recieves elapsed as param, which must be bigger than zero
void Boss::update_self(unsigned long elapsed) {
  set_x(this->x());
  set_y(this->y());

  update_direction(elapsed);
  m_animation->update(elapsed);
  walk();
}

// Set boss's position
// Recieves x and y as params, which must be within the screen
void Boss::set_position(double x, double y) {
  set_x(x);
  set_y(y);
}

// Sets if the boss has been summoned in-level
// Recieves t as param; true  = stands for summoned
//                      false = stands for not summoned
void Boss::set_summoned(bool t) {
  m_summoned = t;
}

// Sets if the boss has been created in-level
// Recieves t as param; true  = stands for created
//                      false = stands for not created
void Boss::set_created(bool t) {
  m_created = t;
}
