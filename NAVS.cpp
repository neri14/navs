
#include "XPLMDataAccess.h"
#include "XPLMDefs.h"
#include "XPLMUtilities.h"
#include "XPLMProcessing.h"

#include <string.h>

#ifndef XPLM303
    #error This plugin is prepared for XPLM303 SDK
#endif

XPLMDataRef navs_dataref_avionics_state = NULL;
bool navs_last_avionics_state = false;


float flightLoopCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon);

PLUGIN_API int XPluginStart(char * outName, char * outSig, char * outDesc)
{
    strcpy(outName, "NAVS");
    strcpy(outSig, "it.rokosz.xplane.navs");
    strcpy(outDesc, "Neri AVionics Suite");

    XPLMRegisterFlightLoopCallback(flightLoopCallback, -1.0, NULL);

    navs_dataref_avionics_state = XPLMFindDataRef("sim/cockpit/electrical/avionics_on");

    return 1.0;
}

PLUGIN_API int  XPluginEnable(void) { return 1; }

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API void	XPluginStop(void)
{
    XPLMUnregisterFlightLoopCallback(flightLoopCallback, NULL);
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam) { }

float flightLoopCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void* inRefcon)
{
    bool curr = static_cast<bool>(XPLMGetDatai(navs_dataref_avionics_state));
    if (curr != navs_last_avionics_state) {
        navs_last_avionics_state = curr;

        XPLMSpeakString(curr ? "Avionics on" : "Avionics off");
    }
    return 1.0;
}