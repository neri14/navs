#include <string>

#include <XPLMDataAccess.h>
#include <XPLMDefs.h>
#include <XPLMUtilities.h>
#include <XPLMProcessing.h>

#include "sim/data.h"

#ifndef XPLM303
    #error This plugin is prepared for XPLM303 SDK
#endif

namespace navs {
    namespace constant {
        namespace dataref_name {
            const std::string avionics_on("sim/cockpit/electrical/avionics_on");
        }

        namespace plugin {
            const std::string name("NAVS");
            const std::string signature("it.rokosz.xplane.navs");
            const std::string description("Neri AVionics Suite");
        }

        const int xplane_plugin_data_buffer_size(256);
        const float flight_loop_cb_interval(-5.0); // -5.0 - every 5 flight loops
    }

    namespace dataref {
        XPLMDataRef avionics_on = NULL;
    }

    sim::data data;

    float flight_loop_cb(float in_elapsed_since_last_call, float in_elapsed_time_since_last_flight_loop, int in_counter, void* in_refcon);

    PLUGIN_API int XPluginStart(char* out_name, char* out_sig, char* out_desc)
    {
        // set plugin data
        strcpy_s(out_name, constant::xplane_plugin_data_buffer_size, constant::plugin::name.c_str());
        strcpy_s(out_sig, constant::xplane_plugin_data_buffer_size, constant::plugin::signature.c_str());
        strcpy_s(out_desc, constant::xplane_plugin_data_buffer_size, constant::plugin::description.c_str());

        // register for flight loop callbacks
        XPLMRegisterFlightLoopCallback(flight_loop_cb, constant::flight_loop_cb_interval, NULL);

        // find datarefs
        dataref::avionics_on = XPLMFindDataRef(constant::dataref_name::avionics_on.c_str());

        // start success
        return 1;
    }

    PLUGIN_API int  XPluginEnable(void) { return 1; /* 1 - enable success */ }
    PLUGIN_API void XPluginDisable(void) { }
    PLUGIN_API void	XPluginStop(void)
    {
        // cleanup after yourself
        XPLMUnregisterFlightLoopCallback(flight_loop_cb, NULL);
    }
    PLUGIN_API void XPluginReceiveMessage(XPLMPluginID from, int msg, void* param) { }

    float flight_loop_cb(float time_since_last_call, float time_since_last_loop, int counter, void* refcon)
    {
        data.avionics_on = static_cast<bool>(XPLMGetDatai(dataref::avionics_on));

        if (data.has_changed()) {
            //TODO: forward to handlers

            //FIXME: debug test - to be removed
            if (data.avionics_on.has_changed()) {
                XPLMSpeakString(data.avionics_on ? "Avionics on" : "Avionics off");
            }

            //cleanup data flags after handling
            data.clear_changed();
        }

        return constant::flight_loop_cb_interval;
    }
}