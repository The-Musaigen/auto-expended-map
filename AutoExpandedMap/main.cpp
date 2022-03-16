#include <main.h>

hook_smart_t<switch_to_new_screen_t> hook_switch_to_new_screen;

void __fastcall OnSwitchToNewScreen(void* manager, void* edx86, char page) {
    if (page == kMapPage) {
        // Read the minimal zoom value
        // Allowes to use any other map plugins/scripts, that removes the limit
        float minimal_zoom = memwrapper::read_memory<float>(kMovMinimalZoom);

        // Installing that value
        memwrapper::write_memory<float>(kMapZoom, minimal_zoom);
    }

    return hook_switch_to_new_screen->call(manager, page);
}

BOOL APIENTRY DllMain(_In_ HMODULE hModule, _In_ DWORD dwReasonForCall,
                      _In_ LPVOID lpvReserved) {

    if (dwReasonForCall == DLL_PROCESS_ATTACH) {
        using std::make_unique;

        // Don't interrupt us about thread events
        DisableThreadLibraryCalls(hModule);

        // Installing hook
        hook_switch_to_new_screen = make_unique<hook_t<switch_to_new_screen_t>>(
            kSwitchToNewScreen, OnSwitchToNewScreen);
        hook_switch_to_new_screen->install();
    }

    return TRUE;
}