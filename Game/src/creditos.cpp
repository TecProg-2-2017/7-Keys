/*
 *  File: creditos.cpp
 *
 *  Description:  Implementation of Creditos class
 */

#include <ijengine/util/button.h>
#include <core/font.h>
#include <core/environment.h>
#include <iostream>

#include "creditos.h"

using namespace std;

// Constructor method that loads credit's screen (loads as a level)
// Recieves a string as param, that defines level creditos to be loaded
Creditos::Creditos() : Level("creditos") {
  Environment *environment = Environment::get_instance();

  double w = environment->canvas->w();
  double h = environment->canvas->h();

  set_dimensions(w, h);

  Button *back = new Button(this, "back", "res/interface/menuCreditos/voltar.png",
      "res/interface/menuCreditos/Svoltar.png");

  back->align_to(this, Object::RIGHT, Object::RIGHT);
  back->set_y(520);

  back->add_observer(this);
  add_child(back);
}

Creditos::~Creditos() {
}

// Creates the credits screen
void Creditos::draw_self() {
  Environment *environment = Environment::get_instance();
  environment->canvas->clear(Color::WHITE);

  shared_ptr<Texture> image = environment->resources_manager\
                 ->get_texture("res/interface/menuCreditos/telaCreditos.png");

  environment->canvas->draw(image.get(), 1, 0);
}

// TODO: refactorate for better understanding
// This method makes credits be shown if the 'creditos' button is pressed in
// main screen or if the games finishes.
bool Creditos::on_message(Object *object,
                          MessageID id,
                          Parameters) {

  if (id != Button::clickedID) {
    return false;
  }

  Button *button = dynamic_cast <Button *>(object);

  if (not button) {
    return false;
  }

  if (button->id() == "back") {
    set_next("title");
  }

  finish();

  return true;
}
