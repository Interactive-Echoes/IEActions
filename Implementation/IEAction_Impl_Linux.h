// SPDX-License-Identifier: GPL-2.0-only
// Copyright © Interactive Echoes. All rights reserved.
// Author: mozahzah

#pragma once

#include "IEActions.h"

#if defined (__linux__)
#include "alsa/mixer.h"

class IEAction_Volume_Impl_Linux : public IEAction_Volume
{
public:
    IEAction_Volume_Impl_Linux();
    ~IEAction_Volume_Impl_Linux();

public:
    float GetVolume() const override;
    void SetVolume(float Volume) override;

private:
    snd_mixer_elem_t* m_MasterMixerElement;
    snd_mixer_t* m_MixerHandle;
    snd_mixer_selem_id_t* m_MixerSelemID;
    const char* m_CardName = "default";
    const char* m_SelemName = "Master";
};

class IEAction_Mute_Impl_Linux : public IEAction_Mute
{
public:
    IEAction_Mute_Impl_Linux();
    ~IEAction_Mute_Impl_Linux();

public:
    bool GetMute() const override;
    void SetMute(bool bMute) override;
   
private:
    snd_mixer_elem_t* m_MasterMixerElement;
    snd_mixer_t* m_MixerHandle;
    snd_mixer_selem_id_t* m_MixerSelemID;
    const char* m_CardName = "default";
    const char* m_SelemName = "Master";
};

class IEAction_ConsoleCommand_Impl_Linux : public IEAction_ConsoleCommand
{
public:
    void ExecuteConsoleCommand(const std::string& ConsoleCommand, float CommandParameterValue = 0.0f) override;
};

class IEAction_OpenFile_Impl_Linux : public IEAction_OpenFile
{
public:
    void OpenFile(const std::string& FilePath) override;
};
#endif