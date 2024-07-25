// SPDX-License-Identifier: GPL-2.0-only
// Copyright © 2024 Immortal Echoes. All rights reserved.
// Author: mozahzah

#pragma once

#include "IEActions.h"

#if defined (_WIN32)
#include <atlbase.h> 
#include <endpointvolume.h>
#include <mmdeviceapi.h>

class IEAction_Volume_Impl_Win : public IEAction_Volume
{
public:
    IEAction_Volume_Impl_Win();

public:
    float GetVolume() const override;
    void SetVolume(float Volume) override;
    void RegisterVolumeChangeCallback(const std::function<void(float)>& Callback) override;

private:
    IAudioEndpointVolume* GetMainAudioEndpointVolume();

private:
    CComPtr<IAudioEndpointVolume> m_AudioEndpointVolume;
    std::function<void(float)> m_OnVolumeChangeCallback;
};

class IEAction_Mute_Impl_Win : public IEAction_Mute
{
public:
    IEAction_Mute_Impl_Win();

public:
    bool GetMute() const override;
    void SetMute(bool bMute) override;
    void RegisterMuteChangeCallback(const std::function<void(bool)>& Callback) override;
   
private:
    IAudioEndpointVolume* GetMainAudioEndpointVolume();

private:
    CComPtr<IAudioEndpointVolume> m_AudioEndpointVolume;
    std::function<void(bool)> m_OnMuteChangeCallback;
};

class IEAction_OpenFile_Impl_Win : public IEAction_OpenFile
{
public:
    void OpenFile(const std::string& FilePath) override;
};
#endif