// SPDX-License-Identifier: GPL-2.0-only
// Copyright © Interactive Echoes. All rights reserved.
// Author: mozahzah

#include "Implementation/IEAction_Impl_Linux.h"

#if defined (__linux__)
IEAction_Volume_Impl_Linux::IEAction_Volume_Impl_Linux()
{
    snd_mixer_open(&m_MixerHandle, 0);
    snd_mixer_attach(m_MixerHandle, m_CardName);
    snd_mixer_selem_register(m_MixerHandle, NULL, NULL);
    snd_mixer_load(m_MixerHandle);

    snd_mixer_selem_id_malloc(&m_MixerSelemID);
    snd_mixer_selem_id_set_index(m_MixerSelemID, 0);
    snd_mixer_selem_id_set_name(m_MixerSelemID, m_SelemName);
    m_MasterMixerElement = snd_mixer_find_selem(m_MixerHandle, m_MixerSelemID);
}

IEAction_Volume_Impl_Linux::~IEAction_Volume_Impl_Linux()
{
    snd_mixer_close(m_MixerHandle);
}

float IEAction_Volume_Impl_Linux::GetVolume() const
{
    long Volume = 0;
    snd_mixer_selem_get_playback_volume(m_MasterMixerElement, SND_MIXER_SCHN_FRONT_LEFT, &Volume);
    return Volume;
}

void IEAction_Volume_Impl_Linux::SetVolume(float Volume)
{
    long Min = 0, Max = 0;
    snd_mixer_selem_get_playback_volume_range(m_MasterMixerElement, &Min, &Max);
    snd_mixer_selem_set_playback_volume_all(m_MasterMixerElement, Volume * Max / 100);
}

IEAction_Mute_Impl_Linux::IEAction_Mute_Impl_Linux()
{
    snd_mixer_open(&m_MixerHandle, 0);
    snd_mixer_attach(m_MixerHandle, m_CardName);
    snd_mixer_selem_register(m_MixerHandle, NULL, NULL);
    snd_mixer_load(m_MixerHandle);

    snd_mixer_selem_id_malloc(&m_MixerSelemID);
    snd_mixer_selem_id_set_index(m_MixerSelemID, 0);
    snd_mixer_selem_id_set_name(m_MixerSelemID, m_SelemName);
    m_MasterMixerElement = snd_mixer_find_selem(m_MixerHandle, m_MixerSelemID);
}

IEAction_Mute_Impl_Linux::~IEAction_Mute_Impl_Linux()
{
    snd_mixer_close(m_MixerHandle);
}

bool IEAction_Mute_Impl_Linux::GetMute() const
{
    int Mute = 0;
    snd_mixer_selem_get_playback_switch(m_MasterMixerElement, SND_MIXER_SCHN_FRONT_LEFT, &Mute);
    return Mute != 0;
}

void IEAction_Mute_Impl_Linux::SetMute(bool bMute)
{
    snd_mixer_selem_set_playback_switch_all(m_MasterMixerElement, bMute);
}

void IEAction_ConsoleCommand_Impl_Linux::ExecuteConsoleCommand(const std::string& ConsoleCommand, float CommandParameterValue)
{
    std::string FinalConsoleCommand = ConsoleCommand;

    const size_t ValuePosition = FinalConsoleCommand.find("{V}");
    if (ValuePosition != std::string::npos)
    {
        const std::string ValueStr = std::to_string(CommandParameterValue);
        FinalConsoleCommand.replace(ValuePosition, 3, ValueStr);
    }

    system(FinalConsoleCommand.c_str());
}

void IEAction_OpenFile_Impl_Linux::OpenFile(const std::string& FilePath)
{
    std::string OpenFileCommand = "open \"" + FilePath + "\"";
    int result = system(OpenFileCommand.c_str());
}
#endif
