/*
 *  File: 7keys.cpp
 *
 *  Description:  Implementation of SevenKeys class
 */

#include <ijengine/core/environment.h>
#include <ijengine/core/level.h>
#include <ijengine/util/frontend.h>
#include <cstring>

#include "7keys.h"
#include "titlescreen.h"
#include "stage.h"
#include "options.h"
#include "creditos.h"
#include "extras.h"

// Sets game song when starting the Game
SevenKeys::SevenKeys() : Game("fone") {
  AudioManagerMusic * music2 = new AudioManagerMusic();

  music2 -> play("res/sounds/musicaMenu.wav", -1);

  lives = 5;
  sanity = 100;
}

// TODO: refactorate
// Method for loading levels
// Recieves a string as param, for defining the level to be loaded.
Level * SevenKeys::load_level(const string& id) {
  if (id == "fone") {
    return new FrontEnd("logo", "logo", "res/images/fone.png");
  }
  if (id == "logo") {
    return new FrontEnd("logo", "tecnologias", "res/images/manateam.png");
  }
  else if (id == "tecnologias") {
    return new FrontEnd("tecnologias", "classificacao",
                        "res/images/tecnologias.png");
  }
  else if (id == "classificacao") {
    return new FrontEnd("classificacao", "title",
                        "res/images/classificacao_indicativa.png");
  }
  else if (id == "title") {
    return new TitleScreen();
  }
  else if (id == "options") {
    return new Options();
  }
  else if (strstr(id.c_str(), "trans")) {
    Environment *environment = Environment::get_instance();
    shared_ptr <Font> font = environment->resources_manager\
                                      ->get_font("res/fonts/TakaoExGothic.ttf");

    environment->canvas->set_font(font);

    double w = environment->canvas->w();
    double h = environment->canvas->h();

    string ant = id;

    Level *lvl = new Level(id, id);
    lvl->set_dimensions(w, h);

    char novo[256];

    sprintf(novo, "%s",id.c_str());
    novo[0] = 's';
    novo[1] = 't';
    novo[2] = 'a';
    novo[3] = 'g';
    novo[4] = 'e';

    string num_id = id.substr(5,5);
    char num_id2[10];

    sprintf(num_id2, "%s", num_id.c_str());

    int novo_id = atoi(num_id2);
    char path[256];

    if(novo_id < 6) {
      sprintf(path, "res/interface/transicao/Fase%d.png", novo_id);
    }
    else {
      sprintf(path, "res/interface/transicao/Bonus.png");
    }

    char music_path[256];

    if(novo_id < 5) {
        sprintf(music_path, "res/sounds/Fase%d.wav", novo_id);
    }
    else {
      sprintf(music_path, "res/sounds/Fase5.wav");
    }

    environment->music->play(music_path, -1);
    environment->canvas->draw(id, w/2, h/2 ,Color::RED);

    cout << novo << endl;

    return new FrontEnd(id, novo, path);
  }

  else if(strstr(id.c_str(), "death")) {
    Environment *environment = Environment::get_instance();
    environment->sfx->play("res/sounds/pregameover.wav",1);

    shared_ptr <Font> font = environment->resources_manager\
                                      ->get_font("res/fonts/TakaoExGothic.ttf");

    environment->canvas->set_font(font);

    double w = environment->canvas->w();
    double h = environment->canvas->h();
    string ant = id;
    Level *lvl = new Level(id, id);

    lvl->set_dimensions(w, h);

    char novo[256];

    sprintf(novo, "%s",id.c_str());
    novo[0] = 's';
    novo[1] = 't';
    novo[2] = 'a';
    novo[3] = 'g';
    novo[4] = 'e';

    lives -= 1;

    return new FrontEnd(id, novo, "res/images/transition.png");
  }
  else if(id == "gameover") {
    Environment *environment = Environment::get_instance();
    environment->sfx->play("res/sounds/gameOver.wav",1);

    double w = environment->canvas->w();
    double h = environment->canvas->h();

    Level *lvl = new Level(id, id);
    lvl->set_dimensions(w, h);
    return new FrontEnd(id, "title", "res/interface/transicao/gameOver.png");
  }
  else if (strstr(id.c_str(), "stage")) {
    return new Stage(id, lives, &sanity);
  }
  else if (id == "creditos") {
    return new Creditos();
  }
  else if (id == "extras") {
    return new Extras();
  }

  return nullptr;
}
