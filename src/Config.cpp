/*
obs-ndi
Copyright (C) 2016-2018 Stéphane Lepin <steph  name of author

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; If not, see <https://www.gnu.org/licenses/>
*/

#include "Config.h"
#include "obs-ndi.h"

#include <obs-frontend-api.h>
#include <util/config-file.h>

#define SECTION_NAME "NDIPlugin"
#define PARAM_ENABLE "MainOutputEnabled"
#define PARAM_NAME "MainOutputName"

Config* Config::_instance = nullptr;

Config::Config() :
    OutputEnabled(false),
    OutputName("OBS")
{
    config_t* obs_config = obs_frontend_get_global_config();
    if (obs_config) {
        config_set_default_bool(obs_config,
            SECTION_NAME, PARAM_ENABLE, OutputEnabled);
        config_set_default_string(obs_config,
            SECTION_NAME, PARAM_NAME, OutputName.toUtf8().constData());
    }
}

void Config::Load() {
    config_t* obs_config = obs_frontend_get_global_config();
    if (obs_config) {
        OutputEnabled = config_get_bool(obs_config, SECTION_NAME, PARAM_ENABLE);
        OutputName = config_get_string(obs_config, SECTION_NAME, PARAM_NAME);
    }
}

void Config::Save() {
    config_t* obs_config = obs_frontend_get_global_config();
    if (obs_config) {
        config_set_bool(obs_config,
            SECTION_NAME, PARAM_ENABLE, OutputEnabled);
        config_set_string(obs_config,
            SECTION_NAME, PARAM_NAME, OutputName.toUtf8().constData());
        config_save(obs_config);
    }
}

Config* Config::Current() {
    if (!_instance) {
        _instance = new Config();
    }
    return _instance;
}
