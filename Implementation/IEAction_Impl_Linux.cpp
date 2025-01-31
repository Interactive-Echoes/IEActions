// SPDX-License-Identifier: GPL-2.0-only
// Copyright © Interactive Echoes. All rights reserved.
// Author: mozahzah

#include "Implementation/IEAction_Impl_Linux.h"
#include "IEAction_Impl_Linux.h"

#if defined (__linux__)
IEAction_Volume_Impl_Linux::IEAction_Volume_Impl_Linux() :
    m_IEMixerElement(IEMixerManager::Get().GetIEMixer("default").GetElement("Master")),
    m_MixerEventCallbackID(m_IEMixerElement.RegisterCallback(&IEAction_Volume_Impl_Linux::MixerEventCallback, IEMixerElementCallbackType::Volume, this))
{}

IEAction_Volume_Impl_Linux::~IEAction_Volume_Impl_Linux()
{
    m_IEMixerElement.UnregisterCallback(m_MixerEventCallbackID);
}

float IEAction_Volume_Impl_Linux::GetVolume() const
{
    return m_IEMixerElement.GetVolume().value_or(0.0f);
}

void IEAction_Volume_Impl_Linux::SetVolume(float Volume)
{
    m_IEMixerElement.SetVolume(Volume);
}

void IEAction_Volume_Impl_Linux::MixerEventCallback(const IEMixerElement& MixerElement, IEMixerElementCallbackType CallbackMask, void* UserData)
{
    if (IEAction_Volume_Impl_Linux* const LinuxVolumeAction = static_cast<IEAction_Volume_Impl_Linux*>(UserData))
    {
        for (const std::pair<uint32_t, std::pair<std::function<void(float, void*)>, void*>>& Element : LinuxVolumeAction->m_VolumeChangeCallbacks)
        {
            Element.second.first(MixerElement.GetVolume().value_or(-1.0f), Element.second.second);
        }
    }
}

IEAction_Mute_Impl_Linux::IEAction_Mute_Impl_Linux() :
    m_IEMixerElement(IEMixerManager::Get().GetIEMixer("default").GetElement("Master")),
    m_MixerEventCallbackID(m_IEMixerElement.RegisterCallback(&IEAction_Mute_Impl_Linux::MixerEventCallback, IEMixerElementCallbackType::Mute, this))
{}

IEAction_Mute_Impl_Linux::~IEAction_Mute_Impl_Linux()
{
    m_IEMixerElement.UnregisterCallback(m_MixerEventCallbackID);
}

bool IEAction_Mute_Impl_Linux::GetMute() const
{
    return m_IEMixerElement.GetMute().value_or(false);
}

void IEAction_Mute_Impl_Linux::SetMute(bool bMute)
{
    m_IEMixerElement.SetMute(bMute);
}

void IEAction_Mute_Impl_Linux::MixerEventCallback(const IEMixerElement& MixerElement, IEMixerElementCallbackType CallbackType, void* UserData)
{
    if (IEAction_Mute_Impl_Linux* const LinuxMuteAction = static_cast<IEAction_Mute_Impl_Linux*>(UserData))
    {
        for (const std::pair<uint32_t, std::pair<std::function<void(float, void*)>, void*>>& Element : LinuxMuteAction->m_MuteChangeCallbacks)
        {
            Element.second.first(MixerElement.GetMute().value_or(false), Element.second.second);
        }
    }
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
