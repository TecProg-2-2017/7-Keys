/*
+* File: extras.cpp
+*
+* Description: Implementation of Extras Class
*/

#include "extras.h"

#include <ijengine/util/button.h>
#include <core/font.h>
#include <core/environment.h>

#include <iostream>
using namespace std;

// Creates the entire Extras main screen, including buttons and such

Extras::Extras() : Level("extras") {
    Environment *env = Environment::get_instance();

    double w = env->canvas->w();
    double h = env->canvas->h();

    set_dimensions(w, h);

    Button *cutscene = new Button(this, "cutscene", "res/interface/menuExtras/cutscenes.png",
        "res/interface/menuExtras/Scutscenes.png");

    cutscene->align_to(this, Object::MIDDLE, Object::NONE);
    cutscene->set_y(200);

    Button *historia = new Button(this, "historia", "res/interface/menuExtras/historia.png",
        "res/interface/menuExtras/Shistoria.png");

    historia->align_to(this, Object::MIDDLE, Object::NONE);
    historia->set_y(cutscene->y() + cutscene->h()+20);

    Button *back = new Button(this, "back", "res/interface/menuExtras/voltar.png",
        "res/interface/menuExtras/Svoltar.png");

    back->align_to(this, Object::MIDDLE, Object::NONE);
    back->set_y(historia->y() + historia->h()+20);

    cutscene->add_observer(this);
    historia->add_observer(this);
    back->add_observer(this);

    add_child(cutscene);
    add_child(historia);
    add_child(back);
}

Extras::~Extras() {
}
// Loads the game ending image
void Extras::draw_self() {

    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);

    shared_ptr<Texture> image = env->resources_manager->get_texture("res/interface/menuExtras/menuExtras.png");
    env->canvas->draw(image.get(), 1, 0);
}

// Defines which was the button clicked on the extras screen
bool Extras::on_message(Object *object, MessageID id, Parameters) {

    if (id != Button::clickedID) {
        return false;
        // Returns false if the Object clicked hasn't an Button ID
    }

    Button *button = dynamic_cast <Button *>(object);

    if (not button) {
        return false;
        // Returns false if the clicked object is not a "Button"
    }

    if (button->id() == "back") {
        set_next("title");
    }

    finish();

    return true;
    // Returns true if the object clicked is of the "Button" type
}
