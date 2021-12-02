#if defined(DM_PLATFORM_ANDROID)

#pragma once

#include <dmsdk/sdk.h>

namespace dmFacebook {

void Initialize_Ext();

void StartSDK();
void SetAutoLogAppEventsEnabled(bool is_enabled);
void SetIsDebugEnabled(bool is_enabled);

} // namespace

#endif // platform